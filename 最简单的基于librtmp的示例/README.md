# FFmpeg_Leixiaohua
向我们的雷神--雷霄骅，致敬


#### 本篇的目的是将雷神的贡献，以mac+xcode+C的环境，将组合式项目Demo，单一实现，方便于学习。
#### 如有任何问题，请邮件(anglemiku_v@163.com)联系或者QQ(479069761)联系，欢迎纠正！！！


* 本工程包含了LibRTMP的使用示例，包含如下子工程：
    * 接收RTMP流媒体并在本地保存成FLV格式的文件。
    * 将FLV格式的视音频文件使用RTMP推送至RTMP流媒体服务器。
    *  将内存中的H.264数据推送至RTMP流媒体服务器。


##### librtmp如果未安装，请先安装

* 安装方法
    *  brew install rtmpdump
    * ->Build Settings -> Library Search Paths  地址更换为自己电脑地址（报错的情况下）

