#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codec_api.h"
#include "decoder.h"
#include "encoder.h"
#include "log_print.h"

#define TAG "CODEC-API"

void codec_register_all()
{
    decoder_register_all();
    //encoder_register_all();
}

struct codec_context *codec_create_codec(struct codec_para *para)
{
    struct codec_context *handle = (struct codec_context *)malloc(sizeof(struct codec_context ));
    if(!handle)
        return NULL;
    memset(handle, 0, sizeof(struct codec_context));
    memcpy(&handle->para, para, sizeof(struct codec_para));
    if(para->is_encoder == 0) {
        struct decoder_context *decoder = decoder_create(para);
        if(!decoder)
            return NULL;
        handle->codec = (void *)decoder;
    }
    
    log_print(TAG, "Codec create ok\n");
    return handle;
}

int codec_decode_frame()
{
    return 0;
}

int codec_encode_frame()
{
    return 0;
}

int codec_get_parameter()
{
    return 0;
}

int codec_set_parameter()
{
    return 0;
}

int codec_destroy_codec(struct codec_context *handle)
{
    if(!handle)
        return 0;
    free(handle);
    return 0;
}
