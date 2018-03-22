//
//  main.c
//  simplest_pcm16le_to_wave
//
//  Created by angle on 22/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

/**
 * Convert PCM16LE raw data to WAVE format
 * @param pcmpath      Input PCM file.
 * @param channels     Channel number of PCM file.
 * @param sample_rate  Sample rate of PCM file.
 * @param wavepath     Output WAVE file.
 */
int simplest_pcm16le_to_wave(const char *pcmpath,int channels,int sample_rate,const char *wavepath);


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    //资源文件路径，此地址要更换为自己的电脑路径
    char *inUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：PCM音频采样数据处理/resources/NocturneNo2inEflat_44.1k_s16le.pcm";
    //输出资源路径，此地址要更换为自己的电脑路径
    char *outUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：PCM音频采样数据处理/6.将PCM16LE双声道音频采样数据转换为WAVE格式音频数据/results/output_nocturne.wav";
    
    
    //Test
    int result = simplest_pcm16le_to_wave(inUrl,2,44100,outUrl);
    
    if (result == 1) {
        printf("Write file successed.\n");
    }else {
        printf("Write file failed.\n");
    }
    
    return 0;
}
