#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codec_api.h"
#include "decoder.h"

struct codec_context *codec_create(struct codec_para *para)
{
    struct codec_context *handle = (struct codec_context *)malloc(sizeof(struct codec_context ));
    if(!handle)
        return NULL;

    struct decoder_context *decoder = decoder_create();

    return handle;
}

int codec_process()
{
    return 0;
}

void codec_destroy(struct codec_context *handle)
{
    if(!handle)
        return;
    free(handle);
    return;
}
