#include "codec_api.h"

int main(int argc, char **argv)
{
    codec_register_all();
    struct codec_para para;
    para.media_format = CODEC_MEDIA_FORMAT_H264;
    para.is_encoder = 0;
    para.media_type = CODEC_MEDIA_TYPE_VIDEO;
    struct codec_context *handle = codec_create_codec(&para);
    codec_destroy_codec(handle);
    return 0; 
}