//
//  main.c
//  simplest_udp_parser
//
//  Created by angle on 23/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

int simplest_udp_parser(int port, char *outUrl);



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    //资源文件路径，此地址要更换为自己的电脑路径
    char *outUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：UDP-RTP协议解析/results/output_dump.ts";
    
    simplest_udp_parser(8880, outUrl);

    
    return 0;
}
