//
//  simplest_yuv420_split.c
//  simplest_yuv420_split
//
//  Created by angle on 20/03/2018.
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
 Split Y, U, V planes in YUV420P file.

 @param inputUrl Location of Input YUV file.
 @param w Width of Input YUV file.
 @param h Height of Input YUV file.
 @param num Number of frames to process.
 @param outUrl Location of outPut YUV file.
 @return 1-successed, 0-failed
 */
int simplest_yuv420_split(char *inputUrl, int w, int h,int num, char *outUrl){
    
    FILE *fp=fopen(inputUrl,"rb+");
    
    FILE *fp1=fopen(splicingString_f(outUrl, "output_420_y.y"),"wb+");
    FILE *fp2=fopen(splicingString_f(outUrl, "output_420_u.y"),"wb+");
    FILE *fp3=fopen(splicingString_f(outUrl, "output_420_v.y"),"wb+");
    
    unsigned char *pic=(unsigned char *)malloc(w*h*3/2);
    
    if (fp != NULL && fp1 != NULL && fp2 != NULL && fp3 != NULL) {
        
        for(int i=0;i<num;i++){
            
            fread(pic,1,w*h*3/2,fp);
            //Y
            fwrite(pic,1,w*h,fp1);
            //U
            fwrite(pic+w*h,1,w*h/4,fp2);
            //V
            fwrite(pic+w*h*5/4,1,w*h/4,fp3);
        }
        
        free(pic);
        fclose(fp);
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        
        fp = NULL;
        fp1 = NULL;
        fp2 = NULL;
        fp3 = NULL;
        
        return 1;
    }else {
        return 0;
    }
}



