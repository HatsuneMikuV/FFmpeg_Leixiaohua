//
//  simplest_rgb24_split.c
//  simplest_rgb24_split
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
 * Split R, G, B planes in RGB24 file.
 * @param url  Location of Input RGB file.
 * @param w    Width of Input RGB file.
 * @param h    Height of Input RGB file.
 * @param outUrl Location of outPut YUV file.
 * @return 1-successed, 0-failed
 *
 */
int simplest_rgb24_split(char *url, int w, int h,int num, char *outUrl){
    FILE *fp=fopen(url,"rb+");
    FILE *fp1=fopen(splicingString_f(outUrl, "output_r.y"),"wb+");
    FILE *fp2=fopen(splicingString_f(outUrl, "output_g.y"),"wb+");
    FILE *fp3=fopen(splicingString_f(outUrl, "output_b.y"),"wb+");
    
    unsigned char *pic=(unsigned char *)malloc(w*h*3);
    
    if (fp != NULL && fp1 != NULL && fp2 != NULL && fp3 != NULL) {

    
        for(int i=0;i<num;i++){
            
            fread(pic,1,w*h*3,fp);
            
            for(int j=0;j<w*h*3;j=j+3){
                //R
                fwrite(pic+j,1,1,fp1);
                //G
                fwrite(pic+j+1,1,1,fp2);
                //B
                fwrite(pic+j+2,1,1,fp3);
            }
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
    }
    
    return 0;
}
