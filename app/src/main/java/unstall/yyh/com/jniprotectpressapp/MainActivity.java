package unstall.yyh.com.jniprotectpressapp;

import android.content.Intent;
import android.support.annotation.MainThread;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;


/**
 * 类功能描述：</br>
 *  NDK项目实战—高仿360手机助手之卸载监听
 * 博客地址：http://blog.csdn.net/androidstarjack
 * 公众号：终端研发部
 * @author yuyahao
 * @version 1.0 </p> 修改时间：2017/9/8/008.</br> 修改备注：</br>
 */
public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        WatchDog watchDog = new WatchDog();
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(watchDog.stringFromJNI());
        startService(new Intent(MainActivity.this,ProcessPtotectService.class));
    }


}
