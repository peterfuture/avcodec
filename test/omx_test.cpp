#include "codec_api.h"

int main(int argc, char **argv)
{
    struct codec_para para;
    struct codec_context *handle = codec_create(&para);
    codec_destroy(handle);
    return 0; 
}