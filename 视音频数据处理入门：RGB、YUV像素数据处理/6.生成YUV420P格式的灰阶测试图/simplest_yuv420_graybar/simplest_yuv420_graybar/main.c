//
//  main.c
//  simplest_yuv420_graybar
//
//  Created by angle on 21/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

/**
 * Generate YUV420P gray scale bar.
 * @param width    Width of Output YUV file.
 * @param height   Height of Output YUV file.
 * @param ymin     Max value of Y
 * @param ymax     Min value of Y
 * @param barnum   Number of bars
 * @param url_out  Location of Output YUV file.
 */
int simplest_yuv420_graybar(int width, int height,int ymin,int ymax,int barnum,char *url_out);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    //输出资源路径，此地址要更换为自己的电脑路径
    char *outUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：RGB、YUV像素数据处理/6.生成YUV420P格式的灰阶测试图/results/graybar_640x360.yuv";
    
    //Test
    int result = simplest_yuv420_graybar(640, 360,0,255,10,outUrl);
    
    if (result == 1) {
        printf("Write file successed.\n");
    }else {
        printf("Write file failed.\n");
    }

    
    return 0;
}
