//
//  main.c
//  simplest_aac_parser
//
//  Created by angle on 23/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

int simplest_aac_parser(char *url);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    //资源文件路径，此地址要更换为自己的电脑路径
    char *inUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：AAC音频码流解析/resources/nocturne.aac";

    simplest_aac_parser(inUrl);
    
    return 0;
}
