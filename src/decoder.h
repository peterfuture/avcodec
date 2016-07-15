#ifndef DECODER_H
#define DECODER_H

#include "codec_av.h"

struct video_decoder {

    const char *name;
    int media_format;

    int (*open)(struct video_decoder *decoder);
    int (*decode)(struct video_decoder *decoder, struct codec_packet * pkt, struct codec_frame *frame);
    int (*get_info)(struct video_decoder *decoder);
    int (*set_info)(struct video_decoder *decoder);
    int (*close)(struct video_decoder *decoder);

    void *priv;
    struct video_decoder *next;
};

struct decoder_context {
    struct codec_para para;
    void *decoder;
};

void decoder_register_all();

struct decoder_context *decoder_create(struct codec_para *para);
void decoder_destroy(struct decoder_context *handle);

#endif
