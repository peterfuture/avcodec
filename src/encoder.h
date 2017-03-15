#ifndef ENCODER_H
#define ENCODER_H

#include "codec_av.h"

struct video_encoder {
    const char *name;
    int media_format;
    struct codec_para para;

    int (*open)(struct video_encoder *encoder);
    int (*encode)(struct video_encoder *encoder, struct codec_packet * pkt,
                  struct codec_frame *frame);
    int (*get_info)(struct video_encoder *encoder);
    int (*set_info)(struct video_encoder *encoder);
    int (*close)(struct video_encoder *encoder);

    void *priv;
    struct video_encoder *next;
};

struct audio_encoder {
    const char *name;
    int media_format;
    struct codec_para para;

    int (*open)(struct audio_encoder *encoder);
    int (*encode)(struct audio_encoder *encoder, struct codec_packet * pkt,
                  struct codec_frame *frame);
    int (*get_info)(struct audio_encoder *encoder);
    int (*set_info)(struct audio_encoder *encoder);
    int (*close)(struct audio_encoder *encoder);

    void *priv;
    struct audio_encoder *next;
};


struct encoder_context {
    struct codec_para para;
    //struct video_encoder *encoder;
    void *encoder;
};

void encoder_register_all();

struct encoder_context *encoder_create(struct codec_para *para);
int encoder_encode(struct encoder_context *handle, struct codec_packet *pkt,
                   struct codec_frame *frame);
void encoder_destroy(struct encoder_context *handle);

#endif
