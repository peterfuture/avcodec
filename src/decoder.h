#ifndef DECODER_H
#define DECODER_H

#include "codec_av.h"

struct decoder_context 
{
    struct codec_para para;
};

struct video_decoder {
    
    const char *name;
    struct codec_para para;

    int (*open)(struct video_decoder *decoder);
    int (*decode)(struct video_decoder *decoder, struct codec_packet * pkt, struct codec_frame *frame);
    int (*get_info)(struct video_decoder *decoder);
    int (*set_info)(struct video_decoder *decoder);
    int (*close)(struct video_decoder *decoder);

    void *priv;
    struct vd_wrapper *next;
};

void decoder_register_all();

struct decoder_context *decoder_create(struct codec_para *para);
void decoder_destroy(struct decoder_context *handle);

#endif
