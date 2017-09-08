package unstall.yyh.com.jniprotectpressapp;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.Process;
import android.support.annotation.Nullable;
import android.util.Log;

import java.util.Timer;
import java.util.TimerTask;


/**
 * 类功能描述：</br>
 *  NDK项目实战—高仿360手机助手之卸载监听服务service类
 * 博客地址：http://blog.csdn.net/androidstarjack
 * 公众号：终端研发部
 * @author yuyahao
 * @version 1.0 </p> 修改时间：2017/9/8/008.</br> 修改备注：</br>
 */
public class ProcessPtotectService extends Service{
    private final String TAG = "yuyahao";
    //启动一个定时器
    private Timer timer;
    private int countNum;
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        WatchDog watchDog = new WatchDog();
        watchDog.doubleProtectService(Process.myUid());
        timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                Log.i(TAG,""+countNum++);
            }
        },0,2000);
    }

}
