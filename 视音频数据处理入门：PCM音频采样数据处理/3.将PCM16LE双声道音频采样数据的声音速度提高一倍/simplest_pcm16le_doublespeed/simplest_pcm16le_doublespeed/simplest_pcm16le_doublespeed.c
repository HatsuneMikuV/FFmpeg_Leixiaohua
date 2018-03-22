//
//  simplest_pcm16le_doublespeed.c
//  simplest_pcm16le_doublespeed
//
//  Created by angle on 22/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

//add
#include <stdlib.h>
#include <string.h>


/**
 * Re-sample to double the speed of 16LE PCM file
 * @param url  Location of PCM file.
 @param outUrl Location of outPut file.
 @return 1-successed, 0-failed

 */
int simplest_pcm16le_doublespeed(char *url, char *outUrl){
    FILE *fp=fopen(url,"rb+");
    FILE *fp1=fopen(outUrl,"wb+");
    
    int cnt=0;
    
    unsigned char *sample=(unsigned char *)malloc(4);
    if (fp != NULL && fp1 != NULL) {
        
        while(!feof(fp)){
            
            fread(sample,1,4,fp);
            
            if(cnt%2!=0){
                //L
                fwrite(sample,1,2,fp1);
                //R
                fwrite(sample+2,1,2,fp1);
            }
            cnt++;
        }
        printf("Sample Cnt:%d\n",cnt);
        
        free(sample);
        fclose(fp);
        fclose(fp1);
        fp = NULL;
        fp1 = NULL;
        
        return 1;
    }
    return 0;
}
