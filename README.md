### 如何保证你的app不被杀死，今天我们以学习jni为主来探究一下如何保证不被杀死


 
 ![进程守护流程图](http://upload-images.jianshu.io/upload_images/4614633-23d6e7dcd524e26c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 目前网络上的几种方式：

 - 1、提高优先级
 
    这个办法对普通应用而言，
应该只是降低了应用被杀死的概率，但是如果真的被系统回收了，还是无法让应用自动重新启动！
- 2、 设置onStartCommand

    - 让service.onStartCommand返回START_STICKY
	START_STICKY是service被kill掉后自动重启
	- 通过实验发现，如果在adb shell当中kill掉进程模拟应用被意外杀死的情况(或者用360手机卫士进行清理操作)，
	- 如果服务的onStartCommand返回START_STICKY，
	在进程管理器中会发现过一小会后被杀死的进程的确又会出现在任务管理器中，貌似这是一个可行的办法。
	- 但是如果在系统设置的App管理中选择强行关闭应用，
	这时候会发现即使onStartCommand返回了START_STICKY，应用还是没能重新启动起来！
	
	
- 3、android:persistent="true"
    
    网上还提出了设置这个属性的办法，通过实验发现即使设置了这个属性，应用程序被kill之后还是不能重新启动起来的！


	
- 4、让应用成为系统应用

	- 实验发现即使成为系统应用，被杀死之后也不能自动重新启动。
	- 但是如果对一个系统应用设置了persistent="true"，情况就不一样了
	。
    - 实验表明对一个设置了persistent属性的系统应用，即使kill掉会立刻重启。
	- 一个设置了persistent="true"的系统应用，
	android中具有core service优先级，这种优先级的应用对系统的low memory killer是免疫的！

- 5 、	集成多个推送，也就是我们常说的 ” ****全家桶**** “

- 6、真正办法 加入白名单  （100%进程守护）
###  应用优先级
- Android中的进程是托管的，当系统进程空间紧张的时候，会依照优先级自动进行进程的回收 Android将进程分为5个等级,它们按优先级顺序由高到低依次是：
    
    - 空进程 Empty process
    -  可见进程 Visible process
    -  服务进程 Service process
    -  后台进程 Background process
    -  前台进程 Foreground process
  


手机厂商不会允许这样的情况出现，Android系统在java层提出了双进程方案，大部分手机厂商也会针对于系统源码进行修改。导致大部分双进程不能真正开启起来容易修改
	
### 所谓道高一尺，魔高一丈
	
- linux内核下手
	 
		
- 手机厂商针对于Android系统源码容易修改，但是针对于Linux内核却无能为力
	jni双进程守护，就是一个矛与盾的进化过程
	
#### 终极解决方案:
	使用Jni,在 c端 fork进程，检测Service是否存活，若Service已被杀死，则进行重启Service. 
- 至于检测方式  
	
    可以轮询获取子进程PPid,若为1, 则说明子进程被Init进程所领养,已经成为了孤儿进程. 
	
   - jni 双进程需要面临的问题
     -  1  app主进程什么时候被杀死  如何监听
     - 2  因为我们的进程是fork出来的，fork出来的进程父进程是app进程号
    当app被kill掉时，子进程被孤儿init领养 变成了空进程。怎样在监听自己变成死亡进程的时候
     - 3  如何重启服务 am命令
  
### 重要的事情说三遍
-  注意今天我们讲的这种方式并不适合在项目中，我们学习这种方式是为了学习ndk开发。
-  注意今天我们讲的这种方式并不适合在项目中，我们学习这种方式是为了学习ndk开发。
-  注意今天我们讲的这种方式并不适合在项目中，我们学习这种方式是为了学习ndk开发。

    后期我将会撸一个适合用在项目中的例子，供大家参考。—— Socket系统服务来进行双进程守护，尽情期待吧


NDK双进程守护代码：


![jni类方法](http://upload-images.jianshu.io/upload_images/4614633-52db8edcd4c3d783.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![service类](http://upload-images.jianshu.io/upload_images/4614633-0968259625ac7b53.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![fork](http://upload-images.jianshu.io/upload_images/4614633-7526f9d8116b18c6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![轮训方法](http://upload-images.jianshu.io/upload_images/4614633-b92dbb8ff482621f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![头文件声明](http://upload-images.jianshu.io/upload_images/4614633-2bb63160a272a371.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

>GitHub下载链接:
>
>https://github.com/androidstarjack/JNIProtectPressApp
>


### 相信自己，没有做不到的，只有想不到的
 如果你觉得此文对您有所帮助，欢迎入群 QQ交流群 ：232203809 
微信公众号：终端研发部 

 
![技术+职场](http://upload-images.jianshu.io/upload_images/4614633-977d06f49c7ba7be.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

（欢迎关注学习和交流） 
 