### 该程序可以将H.264数据发布到RTMP流媒体服务器


* 整个程序包含3个接口函数：
    * RTMP264_Connect()：建立RTMP连接。
    * RTMP264_Send()：发送数据。
    * RTMP264_Close()：关闭RTMP连接。
    
##### 按照顺序调用上述3个接口函数就可以完成H.264码流的发送。

#### 结构图中关键函数的作用如下所列。

* RTMP264_Connect()中包含以下函数：
    * RTMP_Alloc()：为结构体“RTMP”分配内存。
    * RTMP_Init()：初始化结构体“RTMP”中的成员变量。
    * RTMP_SetupURL()：设置输入的RTMP连接的URL。
    * RTMP_EnableWrite()：发布流的时候必须要使用。如果不使用则代表接收流。
    * RTMP_Connect()：建立RTMP连接，创建一个RTMP协议规范中的NetConnection。
    * RTMP_ConnectStream()：创建一个RTMP协议规范中的NetStream。

* RTMP264_Send()中包含以下函数：
    * ReadFirstNaluFromBuf()：从内存中读取出第一个NAL单元。
    * ReadOneNaluFromBuf()：从内存中读取出一个NAL单元。
    * h264_decode_sps()：解码SPS，获取视频的宽，高，帧率信息。
    * SendH264Packet()：发送一个NAL单元。

* SendH264Packet()中包含以下函数：
    * SendVideoSpsPps()：如果是关键帧，则在发送该帧之前先发送SPS和PPS。
    * SendPacket()：组装一个RTMPPacket，调用RTMP_SendPacket()发送出去。
    * RTMP_SendPacket()：发送一个RTMP数据RTMPPacket。

* RTMP264_Close()中包含以下函数：
    * RTMP_Close()：关闭RTMP连接。
    * RTMP_Free()：释放结构体“RTMP”。

