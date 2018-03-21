//
//  main.c
//  simplest_rgb24_colorbar
//
//  Created by angle on 21/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

/**
 * Generate RGB24 colorbar.
 * @param width    Width of Output RGB file.
 * @param height   Height of Output RGB file.
 * @param url_out  Location of Output RGB file.
 */
int simplest_rgb24_colorbar(int width, int height,char *url_out);


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    //输出资源路径，此地址要更换为自己的电脑路径
    char *outUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/视音频数据处理入门：RGB、YUV像素数据处理/11.生成RGB24格式的彩条测试图/results/colorbar_640x360.rgb";
    
    //Test
    int result = simplest_rgb24_colorbar(640, 360, outUrl);
    
    if (result == 1) {
        printf("Write file successed.\n");
    }else {
        printf("Write file failed.\n");
    }
    
    return 0;
}
