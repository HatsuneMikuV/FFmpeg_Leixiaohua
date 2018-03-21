//
//  simplest_rgb24_colorbar.c
//  simplest_rgb24_colorbar
//
//  Created by angle on 21/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

//add
#include <stdlib.h>
#include <string.h>

/**
 * Generate RGB24 colorbar.
 * @param width    Width of Output RGB file.
 * @param height   Height of Output RGB file.
 * @param url_out  Location of Output RGB file.
 */
int simplest_rgb24_colorbar(int width, int height,char *url_out){
    
    unsigned char *data=NULL;
    int barwidth;
    char filename[100]={0};
    FILE *fp=NULL;
    int i=0,j=0;
    
    data=(unsigned char *)malloc(width*height*3);
    barwidth=width/8;
    
    if((fp=fopen(url_out,"wb+"))==NULL){
        printf("Error: Cannot create file!");
        return 0;
    }
    
    for(j=0;j<height;j++){
        for(i=0;i<width;i++){
            int barnum=i/barwidth;
            switch(barnum){
                case 0:{
                    data[(j*width+i)*3+0]=255;
                    data[(j*width+i)*3+1]=255;
                    data[(j*width+i)*3+2]=255;
                    break;
                }
                case 1:{
                    data[(j*width+i)*3+0]=255;
                    data[(j*width+i)*3+1]=255;
                    data[(j*width+i)*3+2]=0;
                    break;
                }
                case 2:{
                    data[(j*width+i)*3+0]=0;
                    data[(j*width+i)*3+1]=255;
                    data[(j*width+i)*3+2]=255;
                    break;
                }
                case 3:{
                    data[(j*width+i)*3+0]=0;
                    data[(j*width+i)*3+1]=255;
                    data[(j*width+i)*3+2]=0;
                    break;
                }
                case 4:{
                    data[(j*width+i)*3+0]=255;
                    data[(j*width+i)*3+1]=0;
                    data[(j*width+i)*3+2]=255;
                    break;
                }
                case 5:{
                    data[(j*width+i)*3+0]=255;
                    data[(j*width+i)*3+1]=0;
                    data[(j*width+i)*3+2]=0;
                    break;
                }
                case 6:{
                    data[(j*width+i)*3+0]=0;
                    data[(j*width+i)*3+1]=0;
                    data[(j*width+i)*3+2]=255;
                    
                    break;
                }
                case 7:{
                    data[(j*width+i)*3+0]=0;
                    data[(j*width+i)*3+1]=0;
                    data[(j*width+i)*3+2]=0;
                    break;
                }
            }
            
        }
    }
    fwrite(data,width*height*3,1,fp);
    fclose(fp);
    free(data);
    
    return 1;
}
