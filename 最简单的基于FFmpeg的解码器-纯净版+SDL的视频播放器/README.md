# FFmpeg_Leixiaohua
向我们的雷神--雷霄骅，致敬


#### 本篇的目的是将雷神的贡献，以mac+xcode+C的环境，将组合式项目Demo，单一实现，方便于学习。
#### 如有任何问题，请邮件(anglemiku_v@163.com)联系或者QQ(479069761)联系，欢迎纠正！！！


* 只需要使用libavcodec的纯净解码器+SDL的视频播放


##### ffmpeg  如果未安装，请先安装

* 安装方法
    *  brew install ffmpeg
    * ->Build Settings -> Library Search Paths  地址更换为自己电脑地址（报错的情况下）
    
##### SDL2  如果未安装，请先安装

* 安装方法
    *  brew install SDL2
    * ->Build Settings -> Library Search Paths  地址更换为自己电脑地址（报错的情况下）
    
    
* 关键函数和作用如下：
    *  avcodec_register_all()：注册所有的编解码器。
    *  avcodec_find_decoder()：查找解码器。
    *  avcodec_alloc_context3()：为AVCodecContext分配内存。
    *  avcodec_open2()：打开解码器。
    *  avcodec_decode_video2()：解码一帧数据。

    *  av_parser_init()：初始化AVCodecParserContext。
    *  av_parser_parse2()：解析获得一个Packet。

    *  AVFrame：存储一帧解码后的像素数据
    *  AVPacket：存储一帧（一般情况下）压缩编码数据

