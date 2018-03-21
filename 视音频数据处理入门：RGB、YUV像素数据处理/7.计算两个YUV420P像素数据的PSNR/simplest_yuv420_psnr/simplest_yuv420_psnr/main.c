//
//  main.c
//  simplest_yuv420_psnr
//
//  Created by angle on 21/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>


/**
 * Calculate PSNR between 2 YUV420P file
 * @param url1     Location of first Input YUV file.
 * @param url2     Location of another Input YUV file.
 * @param w        Width of Input YUV file.
 * @param h        Height of Input YUV file.
 * @param num      Number of PSNR.
 */
double simplest_yuv420_psnr(char *url1,char *url2,int w,int h,int num);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    //资源文件路径，此地址要更换为自己的电脑路径
    char *inUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：RGB、YUV像素数据处理/resources/lena_256x256_yuv420p.yuv";
    //输出资源路径，此地址要更换为自己的电脑路径
    char *outUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：RGB、YUV像素数据处理/resources/lena_distort_256x256_yuv420p.yuv";
    
    
    //Test
    double PSNR = simplest_yuv420_psnr(inUrl, outUrl, 256, 255, 1);
    
    printf("PSNR:%f\n",PSNR);
    
    
    return 0;
}
