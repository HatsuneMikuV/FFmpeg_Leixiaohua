### 该程序可以将RTMP流保存成本地FLV文件


* RTMP_Alloc()：为结构体“RTMP”分配内存。
* RTMP_Init()：初始化结构体“RTMP”中的成员变量。
* RTMP_SetupURL()：设置输入的RTMP连接的URL。
* RTMP_Connect()：建立RTMP连接，创建一个RTMP协议规范中的NetConnection。
* RTMP_ConnectStream()：创建一个RTMP协议规范中的NetStream。
* RTMP_Read()：从服务器读取数据。
* RTMP_Close()：关闭RTMP连接。
* RTMP_Free()：释放结构体“RTMP”
