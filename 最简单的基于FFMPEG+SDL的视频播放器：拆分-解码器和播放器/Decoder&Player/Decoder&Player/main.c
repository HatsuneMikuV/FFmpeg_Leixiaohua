//
//  main.c
//  Decoder&Player
//
//  Created by angle on 28/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

/**
 解码器

 @param inUrl 输入资源路径
 @param outUrl 输出资源路径
 @return 0成功，其他失败
 */
int Decoder(char *inUrl, char *outUrl);

/**
 播放器
 
 @param inUrl 播放地址
 @return 0成功  其他失败
 */
int Player(char *inUrl);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    char *inUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/最简单的基于FFMPEG+SDL的视频播放器：拆分-解码器和播放器/res/Titanic.mkv";
    char *outUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/最简单的基于FFMPEG+SDL的视频播放器：拆分-解码器和播放器/res/Titanic.yuv";

    
    int result = Decoder(inUrl, outUrl);
    if (result == 0) {
        printf("Decoder Succeed\n");
    }else {
        printf("Decoder fail\n");
    }
    
    sleep(5);
    result = Player(outUrl);
    if (result == 0) {
        printf("Player Succeed\n");
    }else {
        printf("Player fail\n");
    }
    
    return 0;
}
