//
// Created by david on 2017/9/6.
//

#ifndef SIGNALPROCESS_NATIVE_LIB_H
#define SIGNALPROCESS_NATIVE_LIB_H

#endif //SIGNALPROCESS_NATIVE_LIB_H
#include <sys/select.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/signal.h>
#include <android/log.h>
#define LOG_TAG "tuch"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
void create_child();
void child_start_monitor();