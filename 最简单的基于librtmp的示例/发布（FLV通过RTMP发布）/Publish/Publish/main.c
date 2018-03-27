//
//  main.c
//  Publish
//
//  Created by angle on 27/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>


int publish_using_packet(char *intUrl, char *sendUrl);
int publish_using_write(char *intUrl, char *sendUrl);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    char *intUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/最简单的基于librtmp的示例/resources/cuc_ieschool.flv";
    char *sendUrl = "rtmp://localhost/rtmplive/livestream";

    int result = publish_using_packet(intUrl, sendUrl);
    //int result = publish_using_write(intUrl, sendUrl);
    
    if (result == 0) {
        printf("Send file successed.\n");
    }else {
        printf("Send file failed.\n");
    }
    
    
    return 0;
}
