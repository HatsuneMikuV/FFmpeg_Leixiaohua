//
//  main.c
//  SendH264
//
//  Created by angle on 27/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>
#include "librtmp_send264.h"


FILE *fp_send1;

//读文件的回调函数
//we use this callback function to read data from buffer
int read_buffer1(unsigned char *buf, int buf_size ){
    if(!feof(fp_send1)){
        int true_size = (int)fread(buf,1,buf_size,fp_send1);
        return true_size;
    }else{
        return -1;
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    char *inUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/最简单的基于librtmp的示例/resources/cuc_ieschool.h264";
    
    fp_send1 = fopen(inUrl, "rb");
    
    if (!fp_send1) {
        printf("resources open file failed.\n");
        return 0;
    }
    
    //初始化并连接到服务器
    int result = RTMP264_Connect("rtmp://localhost/rtmplive/livestream");
    if (result == 1) {
        printf("RTMP264_Connect file successed.\n");
    }else {
        printf("RTMP264_Connect file failed.\n");
    }
    //发送
    result = RTMP264_Send(read_buffer1);
    if (result == 1) {
        printf("RTMP264_Send file successed.\n");
    }else {
        printf("RTMP264_Send file failed.\n");
    }
    //断开连接并释放相关资源
    RTMP264_Close();
    
    return 0;
}
