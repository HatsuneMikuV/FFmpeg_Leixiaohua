//
//  simplest_pcm16le_to_pcm8.c
//  simplest_pcm16le_to_pcm8
//
//  Created by angle on 22/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

//add
#include <string.h>
#include <stdlib.h>

/**
 Splicing string    exp: splicingString_f("123","456")  out:"123456"
 
 @param string_1 string on the left
 @param string_2 string on the right
 @return new string
 */
char * splicingString_f (char *string_1, char *string_2) {
    
    size_t len = strlen(string_1) + strlen(string_2) + 1;
    
    char * p;
    p = (char * ) malloc (len);
    memset   ( p , 0 , len);
    strcpy ( p, string_1);
    strcat ( p, string_2);
    
    return p;
}


/**
 * Convert PCM-16 data to PCM-8 data.
 * @param url  Location of PCM file.
 * @param outUrl Location of outPut YUV file.
 * @return 1-successed, 0-failed
 */
int simplest_pcm16le_to_pcm8(char *url, char *outUrl){
    FILE *fp=fopen(url,"rb+");
    
    FILE *fp1=fopen(splicingString_f(outUrl,"output_8.pcm"),"wb+");
    
    int cnt=0;
    
    unsigned char *sample=(unsigned char *)malloc(4);
    
    if (fp != NULL && fp1 != NULL) {
        
   
        while(!feof(fp)){
            
            short *samplenum16=NULL;
            char samplenum8=0;
            unsigned char samplenum8_u=0;
            fread(sample,1,4,fp);
            //(-32768-32767)
            samplenum16=(short *)sample;
            samplenum8=(*samplenum16)>>8;
            //(0-255)
            samplenum8_u=samplenum8+128;
            //L
            fwrite(&samplenum8_u,1,1,fp1);
            
            samplenum16=(short *)(sample+2);
            samplenum8=(*samplenum16)>>8;
            samplenum8_u=samplenum8+128;
            //R
            fwrite(&samplenum8_u,1,1,fp1);
            cnt++;
        }
        printf("Sample Cnt:%d\n",cnt);
        
        free(sample);
        fclose(fp);
        fclose(fp1);
    
        fp1 = NULL;
        fp = NULL;
        return 1;
         }
    return 0;
}
