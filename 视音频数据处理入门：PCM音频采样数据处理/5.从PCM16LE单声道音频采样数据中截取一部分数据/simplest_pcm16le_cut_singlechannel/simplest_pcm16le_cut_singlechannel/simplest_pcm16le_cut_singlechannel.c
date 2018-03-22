//
//  simplest_pcm16le_cut_singlechannel.c
//  simplest_pcm16le_cut_singlechannel
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
 * Cut a 16LE PCM single channel file.
 * @param url        Location of PCM file.
 * @param start_num  start point
 * @param dur_num    how much point to cut
 * @param outUrl Location of outPut YUV file.
 * @return 1-successed, 0-failed
 */
int simplest_pcm16le_cut_singlechannel(char *url,int start_num,int dur_num, char *outUrl){
    FILE *fp=fopen(url,"rb+");
    
    FILE *fp1=fopen(splicingString_f(outUrl, "output_cut.pcm"),"wb+");
    FILE *fp_stat=fopen(splicingString_f(outUrl, "output_cut.txt"),"wb+");
    
    unsigned char *sample=(unsigned char *)malloc(2);
    
    if (fp != NULL && fp1 != NULL && fp_stat !=NULL) {
        
        int cnt=0;
        while(!feof(fp)){
            fread(sample,1,2,fp);
            if(cnt>start_num&&cnt<=(start_num+dur_num)){
                fwrite(sample,1,2,fp1);
                
                short samplenum=sample[1];
                samplenum=samplenum*256;
                samplenum=samplenum+sample[0];
                
                fprintf(fp_stat,"%6d,",samplenum);
                if(cnt%10==0)
                    fprintf(fp_stat,"\n",samplenum);
            }
            cnt++;
        }
        
        free(sample);
        fclose(fp);
        fclose(fp1);
        fclose(fp_stat);
        fp_stat = NULL;
        fp = NULL;
        fp1 = NULL;
    
        
        return 1;
    }
    return 0;
}
