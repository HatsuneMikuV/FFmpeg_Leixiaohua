//
//  main.c
//  simplest_pcm16le_cut_singlechannel
//
//  Created by angle on 22/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>


/**
 * Cut a 16LE PCM single channel file.
 * @param url        Location of PCM file.
 * @param start_num  start point
 * @param dur_num    how much point to cut
 * @param outUrl Location of outPut YUV file.
 * @return 1-successed, 0-failed
 */
int simplest_pcm16le_cut_singlechannel(char *url,int start_num,int dur_num, char *outUrl);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    
    //资源文件路径，此地址要更换为自己的电脑路径
    char *inUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：PCM音频采样数据处理/resources/drum.pcm";
    //输出资源路径，此地址要更换为自己的电脑路径
    char *outUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：PCM音频采样数据处理/5.从PCM16LE单声道音频采样数据中截取一部分数据/results/";
    
    //Test
    int result = simplest_pcm16le_cut_singlechannel(inUrl, 2360, 120, outUrl);
    
    if (result == 1) {
        printf("Write file successed.\n");
    }else {
        printf("Write file failed.\n");
    }
    
    return 0;
}
