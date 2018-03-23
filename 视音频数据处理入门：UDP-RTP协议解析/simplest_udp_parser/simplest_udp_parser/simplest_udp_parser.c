//
//  simplest_udp_parser.c
//  simplest_udp_parser
//
//  Created by angle on 23/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

//add
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include <unistd.h>

/*
 * [memo] FFmpeg stream Command:
 * ffmpeg -re -i sintel.ts -f mpegts udp://127.0.0.1:8880
 * ffmpeg -re -i sintel.ts -f rtp_mpegts udp://127.0.0.1:8880
 */

typedef struct RTP_FIXED_HEADER{
    /* byte 0 */
    unsigned char csrc_len:4;       /* expect 0 */
    unsigned char extension:1;      /* expect 1 */
    unsigned char padding:1;        /* expect 0 */
    unsigned char version:2;        /* expect 2 */
    /* byte 1 */
    unsigned char payload:7;
    unsigned char marker:1;        /* expect 1 */
    /* bytes 2, 3 */
    unsigned short seq_no;
    /* bytes 4-7 */
    unsigned  long timestamp;
    /* bytes 8-11 */
    unsigned long ssrc;            /* stream number is used here. */
} RTP_FIXED_HEADER;

typedef struct MPEGTS_FIXED_HEADER {
    unsigned sync_byte: 8;
    unsigned transport_error_indicator: 1;
    unsigned payload_unit_start_indicator: 1;
    unsigned transport_priority: 1;
    unsigned PID: 13;
    unsigned scrambling_control: 2;
    unsigned adaptation_field_exist: 2;
    unsigned continuity_counter: 4;
} MPEGTS_FIXED_HEADER;




int simplest_udp_parser(int port, char *outUrl)
{
    int cnt=0;
    
    //FILE *myout=fopen("output_log.txt","wb+");
    FILE *myout=stdout;
    
    FILE *fp1=fopen(outUrl,"wb+");
    
    int serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(serSocket == -1){
        printf("socket error !");
        return 0;
    }
    
    struct sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(port);
    serAddr.sin_addr.s_addr = INADDR_ANY;
    if(bind(serSocket, (struct sockaddr *)&serAddr, sizeof(serAddr)) == SO_ERROR){
        printf("bind error !");
        close(serSocket);
        return 0;
    }
    
    struct sockaddr_in remoteAddr;
    int nAddrLen = sizeof(remoteAddr);
    
    //How to parse?
    int parse_rtp=1;
    int parse_mpegts=1;
    
    printf("Listening on port %d\n",port);
    
    char recvData[10000];
    while (1){
        
        int pktsize = recvfrom(serSocket, recvData, 10000, 0, (struct sockaddr *)&remoteAddr, &nAddrLen);
        if (pktsize > 0){
            //printf("Addr:%s\r\n",inet_ntoa(remoteAddr.sin_addr));
            //printf("packet size:%d\r\n",pktsize);
            //Parse RTP
            //
            if(parse_rtp!=0){
                char payload_str[10]={0};
                RTP_FIXED_HEADER rtp_header;
                int rtp_header_size=sizeof(RTP_FIXED_HEADER);
                //RTP Header
                memcpy((void *)&rtp_header,recvData,rtp_header_size);
                
                //RFC3551
                char payload=rtp_header.payload;
                switch(payload){
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18: sprintf(payload_str,"Audio");break;
                    case 31: sprintf(payload_str,"H.261");break;
                    case 32: sprintf(payload_str,"MPV");break;
                    case 33: sprintf(payload_str,"MP2T");break;
                    case 34: sprintf(payload_str,"H.263");break;
                    case 96: sprintf(payload_str,"H.264");break;
                    default:sprintf(payload_str,"other");break;
                }
                
                unsigned int timestamp=ntohl(rtp_header.timestamp);
                unsigned int seq_no=ntohs(rtp_header.seq_no);
                
                fprintf(myout,"[RTP Pkt] %5d| %5s| %10u| %5d| %5d|\n",cnt,payload_str,timestamp,seq_no,pktsize);
                
                //RTP Data
                char *rtp_data=recvData+rtp_header_size;
                int rtp_data_size=pktsize-rtp_header_size;
                fwrite(rtp_data,rtp_data_size,1,fp1);
                
                //Parse MPEGTS
                if(parse_mpegts!=0&&payload==33){
                    for(int i=0;i<rtp_data_size;i=i+188){
                        if(rtp_data[i]!=0x47)
                            break;
                        //MPEGTS Header
                        //memcpy((void *)&mpegts_header,rtp_data+i,sizeof(MPEGTS_FIXED_HEADER));
                        fprintf(myout,"   [MPEGTS Pkt]\n");
                    }
                }
                
            }else{
                fprintf(myout,"[UDP Pkt] %5d| %5d|\n",cnt,pktsize);
                fwrite(recvData,pktsize,1,fp1);
            }
            
            cnt++;
        }
    }
    fclose(fp1);
    
    return 0;
}

