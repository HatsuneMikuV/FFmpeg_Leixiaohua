### 该程序可以将本地FLV文件发布到RTMP流媒体服务器


* RTMP_Alloc()：为结构体“RTMP”分配内存。
* RTMP_Init()：初始化结构体“RTMP”中的成员变量。
* RTMP_SetupURL()：设置输入的RTMP连接的URL。
* RTMP_EnableWrite()：发布流的时候必须要使用。如果不使用则代表接收流。
* RTMP_Connect()：建立RTMP连接，创建一个RTMP协议规范中的NetConnection。
* RTMP_ConnectStream()：创建一个RTMP协议规范中的NetStream。
* Delay：发布流过程中的延时，保证按正常播放速度发送数据。
* RTMP_SendPacket()：发送一个RTMP数据RTMPPacket。
* RTMP_Close()：关闭RTMP连接。
* RTMP_Free()：释放结构体“RTMP”
