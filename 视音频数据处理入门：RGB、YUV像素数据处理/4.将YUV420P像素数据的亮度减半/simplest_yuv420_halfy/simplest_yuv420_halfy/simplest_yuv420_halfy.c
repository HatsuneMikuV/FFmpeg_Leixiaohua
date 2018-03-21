//
//  simplest_yuv420_halfy.c
//  simplest_yuv420_halfy
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
    memset   ( p , 0 , len);
    strcpy ( p, string_1);
    strcat ( p, string_2);
    
    return p;
}

/**
 * Halve Y value of YUV420P file
 * @param url     Location of Input YUV file.
 * @param w       Width of Input YUV file.
 * @param h       Height of Input YUV file.
 * @param outUrl Location of outPut YUV file.
 * @return 1-successed, 0-failed
 */
int simplest_yuv420_halfy(char *url, int w, int h,int num, char *outUrl){
    FILE *fp=fopen(url,"rb+");
    
    FILE *fp1=fopen(splicingString_f(outUrl, "output_half.yuv"),"wb+");
    
    unsigned char *pic=(unsigned char *)malloc(w*h*3/2);
    
    if (fp != NULL && fp1 != NULL) {

        for(int i=0;i<num;i++){
            fread(pic,1,w*h*3/2,fp);
            //Half
            for(int j=0;j<w*h;j++){
                unsigned char temp=pic[j]/2;
                //printf("%d,\n",temp);
                pic[j]=temp;
            }
            fwrite(pic,1,w*h*3/2,fp1);
        }
        
        free(pic);
        fclose(fp);
        fclose(fp1);
        
        fp = NULL;
        fp1 = NULL;
        
        return 1;
    }else {
        return 0;
    }
}
