//
//  main.c
//  simplest_yuv420_border
//
//  Created by angle on 21/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>


/**
 * Add border for YUV420P file
 * @param url     Location of Input YUV file.
 * @param w       Width of Input YUV file.
 * @param h       Height of Input YUV file.
 * @param border  Width of Border.
 * @param outUrl Location of outPut YUV file.
 * @return 1-successed, 0-failed
 */
int simplest_yuv420_border(char *url, int w, int h,int border,int num, char *outUrl);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    //资源文件路径，此地址要更换为自己的电脑路径
    char *inUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：RGB、YUV像素数据处理/resources/lena_256x256_yuv420p.yuv";
    //输出资源路径，此地址要更换为自己的电脑路径
    char *outUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：RGB、YUV像素数据处理/5.将YUV420P像素数据的周围加上边框/results/output_border.yuv";
    
    
    //Test
    int result = simplest_yuv420_border(inUrl, 256, 256, 20, 1, outUrl);
    
    if (result == 1) {
        printf("Write file successed.\n");
    }else {
        printf("Write file failed.\n");
    }
    
    return 0;
}
