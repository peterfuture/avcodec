#include "codec_api.h"

int main(int argc, char **argv)
{
    codec_register_all();
    // decoder test
    struct codec_para para;
    para.media_format = CODEC_MEDIA_FORMAT_H264;
    para.is_encoder = 0;
    para.media_type = CODEC_MEDIA_TYPE_VIDEO;
    para.width = 1280;
    para.height = 720;
    struct codec_context *codec = codec_create_codec(&para);
    codec_destroy_codec(codec);
    
    // encoder test
    memset(&para, 0, sizeof(struct codec_para));
    para.media_format = CODEC_MEDIA_FORMAT_H264;
    para.is_encoder = 0;
    para.media_type = CODEC_MEDIA_TYPE_VIDEO;
    para.width = 1280;
    para.height = 720;
    para.is_encoder = 1;
    codec = codec_create_codec(&para);
    struct codec_packet pkt;
    pkt.data = (uint8_t *)malloc(1280*720*4);
    struct codec_frame frame;
    frame.key = 1;
    frame.data = (uint8_t *)malloc(1280*720*4);
    codec_encode_frame(codec, &pkt, &frame);
    codec_destroy_codec(codec);
    return 0; 
}