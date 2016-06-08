#ifndef CODEC_AV_H
#define CODEC_AV_H

enum AV_TYPE{
    CODEC_AV_TYPE_UNKOWN = -1,
    CODEC_AV_TYPE_AUDIO = 0,
    CODEC_AV_TYPE_VIDEO = 1
};

struct codec_packet
{
    int type;
    size_t size;
    int64_t pts;
    int key;
    uint8_t *data;
};

struct codec_frame
{
    int type;
    size_t size;
    int64_t pts;
    int key;
    uint8_t *data;
};

#endif
