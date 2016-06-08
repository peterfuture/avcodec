#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decoder.h"

int omx_decoder_init();

struct decoder_context *decoder_create()
{
    omx_decoder_init();
    return NULL;
}

void decoder_destroy()
{
    return;
}
