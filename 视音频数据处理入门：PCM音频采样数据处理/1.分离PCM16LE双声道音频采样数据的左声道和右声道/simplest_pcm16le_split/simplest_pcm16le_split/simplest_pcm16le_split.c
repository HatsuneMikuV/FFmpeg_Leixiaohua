//
//  simplest_pcm16le_split.c
//  simplest_pcm16le_split
//
//  Created by angle on 22/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

//add
#include <stdlib.h>
#include <string.h>

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
 * Split Left and Right channel of 16LE PCM file.
 * @param url  Location of PCM file.
 @param outUrl Location of outPut file.
 @return 1-successed, 0-failed
 *
 */
int simplest_pcm16le_split(char *url, char *outUrl){
    FILE *fp=fopen(url,"rb+");
    FILE *fp1=fopen(splicingString_f(outUrl,"output_l.pcm"),"wb+");
    FILE *fp2=fopen(splicingString_f(outUrl,"output_r.pcm"),"wb+");
    
    unsigned char *sample=(unsigned char *)malloc(4);
    
    if (fp != NULL && fp1 != NULL && fp2 != NULL) {
        while(!feof(fp)){
            fread(sample,1,4,fp);
            //L
            fwrite(sample,1,2,fp1);
            //R
            fwrite(sample+2,1,2,fp2);
        }
        
        free(sample);
        fclose(fp);
        fclose(fp1);
        fclose(fp2);
        fp = NULL;
        fp1 = NULL;
        fp2 = NULL;
        return 1;
    }
    return 0;
}
