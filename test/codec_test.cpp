#include "codec_api.h"

int main(int argc, char **argv)
{
    struct codec_para para;
    struct codec_context *handle = codec_create_codec(&para);
    codec_destroy_codec(handle);
    return 0; 
}