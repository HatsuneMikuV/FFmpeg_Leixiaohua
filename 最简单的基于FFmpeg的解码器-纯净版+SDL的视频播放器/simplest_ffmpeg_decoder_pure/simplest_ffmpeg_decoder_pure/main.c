//
//  main.c
//  simplest_ffmpeg_decoder_pure
//
//  Created by angle on 28/03/2018.
//  Copyright © 2018 angle. All rights reserved.
//

#include <stdio.h>

#include "avcodec.h"
#include "SDL.h"
#include "imgutils.h"
#include "swscale.h"


//test different codec
#define TEST_H264  1
#define TEST_HEVC  0


//Refresh Event
#define REFRESH_EVENT  (SDL_USEREVENT + 1)

#define BREAK_EVENT  (SDL_USEREVENT + 2)

const int bpp=12;

int screen_w=480,screen_h=272;
const int pixel_w=480,pixel_h=272;

unsigned char buffer[pixel_w*pixel_h*bpp/8];

int thread_exit=0;

int refresh_video(void *opaque){
    thread_exit=0;
    while (!thread_exit) {
        SDL_Event event;
        event.type = REFRESH_EVENT;
        SDL_PushEvent(&event);
        SDL_Delay(40);
    }
    thread_exit=0;
    //Break
    SDL_Event event;
    event.type = BREAK_EVENT;
    SDL_PushEvent(&event);
    
    return 0;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    AVCodec *pCodec;
    AVCodecContext *pCodecCtx= NULL;
    AVCodecParserContext *pCodecParserCtx=NULL;
    
    FILE *fp_in;
    FILE *fp_out;
    AVFrame    *pFrame,*pFrameYUV;
    
    unsigned char *out_buffer;
    const int in_buffer_size=4096;
    unsigned char in_buffer[in_buffer_size + FF_INPUT_BUFFER_PADDING_SIZE]={0};
    unsigned char *cur_ptr;
    int cur_size;
    AVPacket packet;
    int ret, got_picture;
    
    struct SwsContext *img_convert_ctx = NULL;

    
#if TEST_HEVC
    enum AVCodecID codec_id=AV_CODEC_ID_HEVC;
    char filepath_in[]="/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/最简单的基于FFmpeg的解码器-纯净版+SDL的视频播放器/res/bigbuckbunny_480x272.hevc";
#elif TEST_H264
    enum AVCodecID codec_id=AV_CODEC_ID_H264;
    char filepath_in[]="/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/最简单的基于FFmpeg的解码器-纯净版+SDL的视频播放器/res/bigbuckbunny_480x272.h264";
#else
    enum AVCodecID codec_id=AV_CODEC_ID_MPEG2VIDEO;
    char filepath_in[]="/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/最简单的基于FFmpeg的解码器-纯净版+SDL的视频播放器/res/bigbuckbunny_480x272.m2v";
#endif
    
    char filepath_out[]="/Users/angle/Desktop/FFmpeg/FFmpeg_Leixiaohua/最简单的基于FFmpeg的解码器-纯净版+SDL的视频播放器/res/bigbuckbunny_480x272.yuv";
    int first_time=1;
    
    
    //av_log_set_level(AV_LOG_DEBUG);
    
    avcodec_register_all();
    
    pCodec = avcodec_find_decoder(codec_id);
    if (!pCodec) {
        printf("Codec not found\n");
        return -1;
    }
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if (!pCodecCtx){
        printf("Could not allocate video codec context\n");
        return -1;
    }
    
    pCodecParserCtx=av_parser_init(codec_id);
    if (!pCodecParserCtx){
        printf("Could not allocate video parser context\n");
        return -1;
    }
    
    //if(pCodec->capabilities&CODEC_CAP_TRUNCATED)
    //    pCodecCtx->flags|= CODEC_FLAG_TRUNCATED;
    
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        printf("Could not open codec\n");
        return -1;
    }
    //Input File
    fp_in = fopen(filepath_in, "rb");
    if (!fp_in) {
        printf("Could not open input stream\n");
        return -1;
    }
    //Output File
    fp_out = fopen(filepath_out, "wb");
    if (!fp_out) {
        printf("Could not open output YUV file\n");
        return -1;
    }
    
    pFrame = av_frame_alloc();
    pFrameYUV=av_frame_alloc();
//    out_buffer=(unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,  screen_w, screen_h,1));
//    av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize,out_buffer,
//                         AV_PIX_FMT_YUV420P,screen_w, screen_h,1);
//    av_init_packet(&packet);
//
//    img_convert_ctx = sws_getContext(screen_w, screen_h, pCodecCtx->pix_fmt,
//                                     screen_w, screen_h, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
    while (1) {
        
        cur_size = (int)fread(in_buffer, 1, in_buffer_size, fp_in);
        if (cur_size == 0)
            break;
        cur_ptr=in_buffer;
        
        while (cur_size>0){
            
            int len = av_parser_parse2(
                                       pCodecParserCtx, pCodecCtx,
                                       &packet.data, &packet.size,
                                       cur_ptr , cur_size ,
                                       AV_NOPTS_VALUE, AV_NOPTS_VALUE, AV_NOPTS_VALUE);
            
            cur_ptr += len;
            cur_size -= len;
            
            if(packet.size==0)
                continue;
            
            //Some Info from AVCodecParserContext
            printf("[Packet]Size:%6d\t",packet.size);
            switch(pCodecParserCtx->pict_type){
                case AV_PICTURE_TYPE_I: printf("Type:I\t");break;
                case AV_PICTURE_TYPE_P: printf("Type:P\t");break;
                case AV_PICTURE_TYPE_B: printf("Type:B\t");break;
                default: printf("Type:Other\t");break;
            }
            printf("Number:%4d\n",pCodecParserCtx->output_picture_number);
            
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
            if (ret < 0) {
                printf("Decode Error.\n");
                return ret;
            }
            if (got_picture) {
                if(first_time){
                    printf("\nCodec Full Name:%s\n",pCodecCtx->codec->long_name);
                    printf("width:%d\nheight:%d\n\n",pCodecCtx->width,pCodecCtx->height);
                    out_buffer=(unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,  pCodecCtx->width, pCodecCtx->height,1));
                    av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize,out_buffer,
                                         AV_PIX_FMT_YUV420P,pCodecCtx->width, pCodecCtx->height,1);
                    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                                                     pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
                    first_time=0;
                }
                sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
                          pFrameYUV->data, pFrameYUV->linesize);
                
                int y_size=pCodecCtx->width*pCodecCtx->height;
                fwrite(pFrameYUV->data[0],1,y_size,fp_out);    //Y
                fwrite(pFrameYUV->data[1],1,y_size/4,fp_out);  //U
                fwrite(pFrameYUV->data[2],1,y_size/4,fp_out);  //V
                
                printf("Succeed to decode 1 frame!\n");
            }
        }
        
    }
    
    //Flush Decoder
    packet.data = NULL;
    packet.size = 0;
    while(1){
        ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
        if (ret < 0) {
            printf("Decode Error.\n");
            return ret;
        }
        if (!got_picture){
            break;
        }else {
            sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
                      pFrameYUV->data, pFrameYUV->linesize);
            
            int y_size=pCodecCtx->width*pCodecCtx->height;
            fwrite(pFrameYUV->data[0],1,y_size,fp_out);    //Y
            fwrite(pFrameYUV->data[1],1,y_size/4,fp_out);  //U
            fwrite(pFrameYUV->data[2],1,y_size/4,fp_out);  //V
            
            printf("Flush Decoder: Succeed to decode 1 frame!\n");
        }
    }
    
    fclose(fp_in);
    fclose(fp_out);
    
    av_parser_close(pCodecParserCtx);
    
    av_frame_free(&pFrame);
    avcodec_close(pCodecCtx);
    av_free(pCodecCtx);
    
    //SDL----------------------------------
    if(SDL_Init(SDL_INIT_VIDEO)) {
        printf( "Could not initialize SDL - %s\n", SDL_GetError());
        return -1;
    }
    
    SDL_Window *screen;
    //SDL 2.0 Support for multiple windows
    screen = SDL_CreateWindow("Simplest Video Play SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              screen_w, screen_h,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    if(!screen) {
        printf("SDL: could not create window - exiting:%s\n",SDL_GetError());
        return -1;
    }
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
    
    Uint32 pixformat=0;
    
    //IYUV: Y + U + V  (3 planes)
    //YV12: Y + V + U  (3 planes)
    pixformat= SDL_PIXELFORMAT_IYUV;
    
    SDL_Texture* sdlTexture = SDL_CreateTexture(sdlRenderer,pixformat, SDL_TEXTUREACCESS_STREAMING,pixel_w,pixel_h);
    
    FILE *fp=NULL;
    fp=fopen(filepath_out,"rb+");
    
    if(fp==NULL){
        printf("cannot open this file\n");
        return -1;
    }
    
    SDL_Rect sdlRect;
    
    SDL_Thread *refresh_thread = SDL_CreateThread(refresh_video,NULL,NULL);
    SDL_Event event;
    while(1){
        //Wait
        SDL_WaitEvent(&event);
        if(event.type==REFRESH_EVENT){
            if (fread(buffer, 1, pixel_w*pixel_h*bpp/8, fp) != pixel_w*pixel_h*bpp/8){
                // Loop
                fseek(fp, 0, SEEK_SET);
                fread(buffer, 1, pixel_w*pixel_h*bpp/8, fp);
            }
            
            SDL_UpdateTexture( sdlTexture, NULL, buffer, pixel_w);
            
            //FIX: If window is resize
            sdlRect.x = 0;
            sdlRect.y = 0;
            sdlRect.w = screen_w;
            sdlRect.h = screen_h;
            
            SDL_RenderClear( sdlRenderer );
            SDL_RenderCopy( sdlRenderer, sdlTexture, NULL, &sdlRect);
            SDL_RenderPresent( sdlRenderer );
            
        }else if(event.type==SDL_WINDOWEVENT){
            //If Resize
            SDL_GetWindowSize(screen,&screen_w,&screen_h);
        }else if(event.type==SDL_QUIT){
            thread_exit=1;
        }else if(event.type==BREAK_EVENT){
            break;
        }
    }
    SDL_Quit();
    
    return 0;
}
