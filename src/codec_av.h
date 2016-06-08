#ifndef CODEC_AV_H
#define CODEC_AV_H

#include <stdint.h>
#include "codec_api.h"

struct codec_packet
{
    int format;
    size_t size;
    int64_t pts;
    int key;
    uint8_t *data;
};

struct codec_frame
{
    int format;
    size_t size;
    int64_t pts;
    int key;
    uint8_t *data;
};

#endif
