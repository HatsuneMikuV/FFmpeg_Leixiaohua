//
//  simplest_yuv444_split.c
//  simplest_yuv444_split
//
//  Created by angle on 21/03/2018.
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
    memset ( p , 0 , len);
    strcpy ( p, string_1);
    strcat ( p, string_2);
    
    return p;
}

/**
 * Split Y, U, V planes in YUV444P file.
 * @param url  Location of YUV file.
 * @param w    Width of Input YUV file.
 * @param h    Height of Input YUV file.
 * @param outUrl Location of outPut YUV file.
 * @param num  Number of frames to process.
 *
 */
int simplest_yuv444_split(char *url, int w, int h,int num, char *outUrl) {
    
    FILE *fp=fopen(url,"rb+");
    
    FILE *fp1=fopen(splicingString_f(outUrl, "output_444_y.y"),"wb+");
    FILE *fp2=fopen(splicingString_f(outUrl, "output_444_u.y"),"wb+");
    FILE *fp3=fopen(splicingString_f(outUrl, "output_444_v.y"),"wb+");
    
    unsigned char *pic=(unsigned char *)malloc(w*h*3);
    if (fp != NULL && fp1 != NULL && fp2 != NULL && fp3 != NULL) {

        for(int i=0;i<num;i++){
            fread(pic,1,w*h*3,fp);
            //Y
            fwrite(pic,1,w*h,fp1);
            //U
            fwrite(pic+w*h,1,w*h,fp2);
            //V
            fwrite(pic+w*h*2,1,w*h,fp3);
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
