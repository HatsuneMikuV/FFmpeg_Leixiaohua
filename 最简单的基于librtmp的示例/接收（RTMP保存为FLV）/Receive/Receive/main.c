//
//  main.c
//  Receive
//
//  Created by angle on 24/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "amf.h"
#include "rtmp.h"
#include "log.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    //输出资源文件路径，此地址要更换为自己的电脑路径
    char *outUrl = "/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/最简单的基于librtmp的示例/接收（RTMP保存为FLV）/results/receive.flv";
    
    char *inUrl = "rtmp://live.hkstv.hk.lxdns.com/live/hks";
    
    int maxBufSize = 1024 * 1024 * 3;
    int nRead;
    //is live stream ?
    int bLiveStream = 1;
    
    
    int bufsize=1024*1024*10;
    char *buf=(char*)malloc(bufsize);
    memset(buf,0,bufsize);
    long countbufsize=0;
    
    FILE *fp=fopen(outUrl,"wb");
    if (!fp){
        RTMP_LogPrintf("Open File Error.\n");
        return -1;
    }
    
    /* set log level */
    //RTMP_LogLevel loglvl=RTMP_LOGDEBUG;
    //RTMP_LogSetLevel(loglvl);
    
    RTMP *rtmp=RTMP_Alloc();
    RTMP_Init(rtmp);
    //set connection timeout,default 30s
    rtmp->Link.timeout=10;
    // HKS's live URL
    if(!RTMP_SetupURL(rtmp, inUrl))
    {
        RTMP_Log(RTMP_LOGERROR,"SetupURL Err\n");
        RTMP_Free(rtmp);
        return -1;
    }
    if (bLiveStream == 1){
        rtmp->Link.lFlags|=RTMP_LF_LIVE;
    }
    
    //30 sec
    RTMP_SetBufferMS(rtmp, 30 * 1000);
    
    if(!RTMP_Connect(rtmp,NULL)){
        RTMP_Log(RTMP_LOGERROR,"Connect Err\n");
        RTMP_Free(rtmp);
        return -1;
    }
    
    if(!RTMP_ConnectStream(rtmp,0)){
        RTMP_Log(RTMP_LOGERROR,"ConnectStream Err\n");
        RTMP_Close(rtmp);
        RTMP_Free(rtmp);
        return -1;
    }
    while((nRead = RTMP_Read(rtmp,buf,bufsize))){
        fwrite(buf,1,nRead,fp);
        countbufsize += nRead;
        RTMP_LogPrintf("Receive: %5dByte, Total: %5.2fMB\n", nRead, countbufsize * 1.0/1024/1024);
        if (countbufsize > maxBufSize) break;
    }
    
    if(fp){
        fclose(fp);
        fp = NULL;
    }
    
    
    if(buf){
        free(buf);
    }
    
    if(rtmp){
        RTMP_Close(rtmp);
        RTMP_Free(rtmp);
        rtmp=NULL;
    }
    return 0;
    
}
