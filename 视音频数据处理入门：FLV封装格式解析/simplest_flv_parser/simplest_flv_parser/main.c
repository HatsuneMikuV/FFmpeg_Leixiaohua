//
//  main.c
//  simplest_flv_parser
//
//  Created by angle on 23/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>


/**
 * Analysis FLV file
 * @param url    Location of input FLV file.
 */

int simplest_flv_parser(char *url);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    //资源文件路径，此地址要更换为自己的电脑路径
    char *inUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：FLV封装格式解析/resources/cuc_ieschool.flv";
    
    simplest_flv_parser(inUrl);
    
    return 0;
}
