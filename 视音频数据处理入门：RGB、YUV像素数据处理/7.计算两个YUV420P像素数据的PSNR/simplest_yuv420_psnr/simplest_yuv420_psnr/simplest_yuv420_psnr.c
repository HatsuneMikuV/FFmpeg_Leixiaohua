//
//  simplest_yuv420_psnr.c
//  simplest_yuv420_psnr
//
//  Created by angle on 21/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

//add
#include <stdlib.h>
#include <math.h>

/**
 * Calculate PSNR between 2 YUV420P file
 * @param url1     Location of first Input YUV file.
 * @param url2     Location of another Input YUV file.
 * @param w        Width of Input YUV file.
 * @param h        Height of Input YUV file.
 * @param num      Number of PSNR.
 */
double simplest_yuv420_psnr(char *url1,char *url2,int w,int h,int num){
    FILE *fp1=fopen(url1,"rb+");
    FILE *fp2=fopen(url2,"rb+");
    unsigned char *pic1=(unsigned char *)malloc(w*h);
    unsigned char *pic2=(unsigned char *)malloc(w*h);
    
    double psnr = 0;
    
    if (fp1 != NULL && fp2 != NULL) {
        for(int i=0;i<num;i++){
            fread(pic1,1,w*h,fp1);
            fread(pic2,1,w*h,fp2);
            
            double mse_sum=0,mse=0;
            for(int j=0;j<w*h;j++){
                mse_sum+=pow((double)(pic1[j]-pic2[j]),2);
            }
            mse=mse_sum/(w*h);
            psnr=10*log10(255.0*255.0/mse);
            
            fseek(fp1,w*h/2,SEEK_CUR);
            fseek(fp2,w*h/2,SEEK_CUR);
            
        }
        
        free(pic1);
        free(pic2);
        fclose(fp1);
        fclose(fp2);
        fp1 = NULL;
        fp2 = NULL;
        return psnr;
    }
    return 0;
}
