//
//  main.c
//  simplest_pcm16le_halfvolumeleft
//
//  Created by angle on 22/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>


/**
 * Halve volume of Left channel of 16LE PCM file
 * @param url  Location of PCM file.
 @param outUrl Location of outPut
 @return 1-successed, 0-failed
 */
int simplest_pcm16le_halfvolumeleft(char *url, char *outUrl);


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    //资源文件路径，此地址要更换为自己的电脑路径
    char *inUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：PCM音频采样数据处理/resources/NocturneNo2inEflat_44.1k_s16le.pcm";
    //输出资源路径，此地址要更换为自己的电脑路径
    char *outUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：PCM音频采样数据处理/2.将PCM16LE双声道音频采样数据中左声道的音量降一半/results/output_halfleft.pcm";
    
    //Test
    int result = simplest_pcm16le_halfvolumeleft(inUrl, outUrl);
    
    if (result == 1) {
        printf("Write file successed.\n");
    }else {
        printf("Write file failed.\n");
    }
    
    
    return 0;
}
