#include <jni.h>
#include <string>
#include <signal.h>
extern "C" {
#include "native-lib.h"
}
int user_id;

extern "C"{
//子进程变成僵尸进程会调用这个方法
void sig_handler(int sino) {
//
    int status;
//    阻塞式函数
    LOGE("等待死亡信号");
    wait(&status);
    LOGE("创建进程");
    create_child();

}
JNIEXPORT void JNICALL
Java_unstall_yyh_com_jniprotectpressapp_WatchDog_doubleProtectService(JNIEnv *env,
                                                    jobject instance,jint userId) {
//    父进程
    user_id = userId;
    //为了防止子进程被弄成僵尸进程   不要    1
    struct  sigaction sa;
    sa.sa_flags=0;

    sa.sa_handler = sig_handler;
    sigaction(SIGCHLD, &sa, NULL);
    create_child();
}
JNIEXPORT jstring JNICALL
Java_unstall_yyh_com_jniprotectpressapp_WatchDog_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    LOGE("虽然我是错误的方法，但是我已经进来了");
    return env->NewStringUTF(hello.c_str());
}

void create_child() {
    pid_t pid = fork();
//
    if (pid < 0) {

    } else if (pid > 0) {
//父进程
    } else if (pid == 0){
        LOGE("子进程开启 ");
//        开启线程轮询
        child_start_monitor();
    }

}
//相当于java  run方法
void *thread_rt(void *data){
    pid_t pid;
    while ((pid = getppid()) != 1) {
        sleep(2);
        LOGE("循环 %d ",pid);
    }
//    父进程等于1  apk被干掉了
    LOGE("重启父进程");
    execlp("am", "am", "startservice", "--user", user_id,
           "com.dongnao.signalprocess/com.dongnao.signalprocess.ProcessService", (char*)NULL);
}

void child_start_monitor() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_rt, NULL);
}


}