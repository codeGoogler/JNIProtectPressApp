package unstall.yyh.com.jniprotectpressapp;


/**
 * 类功能描述：</br>
 *  NDK项目实战—高仿360手机助手之卸载监听
 * 博客地址：http://blog.csdn.net/androidstarjack
 * 公众号：终端研发部
 * @author yuyahao
 * @version 1.0 </p> 修改时间：2017/9/8/008.</br> 修改备注：</br>
 */
public class WatchDog {
    {
        System.loadLibrary("native-lib");
    }
    public native void doubleProtectService(int userId);
    public native String stringFromJNI();

    void start(){

    }
}
