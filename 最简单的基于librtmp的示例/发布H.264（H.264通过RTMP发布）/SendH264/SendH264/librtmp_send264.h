//
//  librtmp_send264.h
//  SendH264
//
//  Created by angle on 27/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#ifndef librtmp_send264_h
#define librtmp_send264_h

#include <stdio.h>

/**
 * 建立RTMP连接
 */
int RTMP264_Connect(const char* url);

/**
 * 发送数据
 */
int RTMP264_Send(int (*read_buffer)(unsigned char *buf, int buf_size));

/**
 * 关闭RTMP连接
 */
void RTMP264_Close(void);


#endif /* librtmp_send264_h */
