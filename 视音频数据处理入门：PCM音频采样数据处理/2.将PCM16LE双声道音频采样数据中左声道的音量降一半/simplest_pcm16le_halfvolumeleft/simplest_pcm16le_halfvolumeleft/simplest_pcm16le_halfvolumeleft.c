//
//  simplest_pcm16le_halfvolumeleft.c
//  simplest_pcm16le_halfvolumeleft
//
//  Created by angle on 22/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

//add
#include <stdlib.h>
#include <string.h>


/**
 * Halve volume of Left channel of 16LE PCM file
 * @param url  Location of PCM file.
 @param outUrl Location of outPut
 @return 1-successed, 0-failed
 */
int simplest_pcm16le_halfvolumeleft(char *url, char *outUrl){
    FILE *fp=fopen(url,"rb+");
    FILE *fp1=fopen(outUrl,"wb+");
    
    int cnt=0;
    
    unsigned char *sample=(unsigned char *)malloc(4);
    
    if (fp != NULL && fp1 != NULL) {
        while(!feof(fp)){
            short *samplenum=NULL;
            fread(sample,1,4,fp);
            
            samplenum=(short *)sample;
            *samplenum=*samplenum/2;
            //L
            fwrite(sample,1,2,fp1);
            //R
            fwrite(sample+2,1,2,fp1);
            
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
