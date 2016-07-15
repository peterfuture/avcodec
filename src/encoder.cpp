//Encoder

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encoder.h"
#include "log_print.h"

#define TAG "ENCODER"

struct video_encoder *g_ve = NULL;

#define REGISTER_VIDEO_ENCODER(X,x)             \
{                                               \
    extern struct video_encoder ve_##x##_ops;   \
    void ve_##x##_ops_setup();                  \
    ve_##x##_ops_setup();                       \
    register_venc(&ve_##x##_ops);               \
}

static void register_venc(struct video_encoder * venc)
{
    struct video_encoder **p;
    p = &g_ve;
    while (*p != NULL) {
        p = &(*p)->next;
    }
    *p = venc;
    log_print(TAG, "[%s:%d] register venc, name:%s fmt:%d \n", __FUNCTION__, __LINE__, (*p)->name, (*p)->media_format);
    venc->next = NULL;
}

static struct video_encoder *video_encoder_select(int media_format)
{
    struct video_encoder *encoder = g_ve;
    if (!encoder) {
        goto fail;
    }
    while (encoder) {
        if (encoder->media_format == media_format) {
            log_print(TAG, "Find Match Video encoder:%s\n", encoder->name);
            return encoder;
        }
        encoder = encoder->next;
    }
fail:
    log_print(TAG, "No Match Video Encoder Found\n");
    return NULL;
}


struct audio_encoder *g_ae = NULL;

#define REGISTER_AUDIO_ENCODER(X,x)             \
{                                               \
    extern struct audio_encoder ae_##x##_ops;   \
    void ae_##x##_ops_setup();                  \
    ae_##x##_ops_setup();                       \
    register_aenc(&ae_##x##_ops);               \
}

static void register_aenc(struct audio_encoder * aenc)
{
    struct audio_encoder **p;
    p = &g_ae;
    while (*p != NULL) {
        p = &(*p)->next;
    }
    *p = aenc;
    log_print(TAG, "[%s:%d] register aenc, name:%s fmt:%d \n", __FUNCTION__, __LINE__, (*p)->name, (*p)->media_format);
    aenc->next = NULL;
}

static struct audio_encoder *audio_encoder_select(int media_format)
{
    struct audio_encoder *encoder = g_ae;
    if (!encoder) {
        goto fail;
    }
    while (encoder) {
        if (encoder->media_format == media_format) {
            log_print(TAG, "Find Match Audio encoder:%s\n", encoder->name);
            return encoder;
        }
        encoder = encoder->next;
    }
fail:
    log_print(TAG, "No Match Audio Encoder Found\n");
    return NULL;
}

void encoder_register_all()
{
    // video
    REGISTER_VIDEO_ENCODER(X264, x264);

    // audio
    REGISTER_AUDIO_ENCODER(FAAC, faac);
    return;
}

struct encoder_context *encoder_create(struct codec_para *para)
{
    struct encoder_context *handle = (struct encoder_context *)malloc(sizeof(struct encoder_context));
    if (!handle) {
        return NULL;
    }
    memset(handle, 0, sizeof(struct encoder_context));
    memcpy(&handle->para, para, sizeof(struct codec_para));

    void *encoder = NULL;
    if (para->media_type == CODEC_MEDIA_TYPE_VIDEO) {
        struct video_encoder *ve = NULL;
        ve = video_encoder_select(para->media_format);
        if (!ve) {
            free(handle);
            return NULL;
        }
        memcpy(&ve->para, para, sizeof(struct codec_para));
        if (ve->open(ve) < 0) {
            free(handle);
            return NULL;
        }
        handle->encoder = (void *)ve;

    } else if (para->media_type == CODEC_MEDIA_TYPE_AUDIO) {
        struct audio_encoder *ae = NULL;
        ae = audio_encoder_select(para->media_format);
        if (!ae) {
            free(handle);
            return NULL;
        }
        memcpy(&ae->para, para, sizeof(struct codec_para));
        if (ae->open(ae) < 0) {
            free(handle);
            return NULL;
        }
        handle->encoder = (void *)ae;
    }

    return handle;
}

int encoder_encode(struct encoder_context *handle, struct codec_packet *pkt, struct codec_frame *frame)
{
    if(handle->para.media_type == CODEC_MEDIA_TYPE_VIDEO) {
        struct video_encoder *encoder = (struct video_encoder *)handle->encoder;
        return encoder->encode(encoder, pkt, frame);
    }
    if(handle->para.media_type == CODEC_MEDIA_TYPE_AUDIO) {
        struct audio_encoder *encoder = (struct audio_encoder *)handle->encoder;
        return encoder->encode(encoder, pkt, frame);
    }

    return -1;
}

void encoder_destroy(struct encoder_context *handle)
{
    if(handle->para.media_type == CODEC_MEDIA_TYPE_VIDEO) {
        struct video_encoder *encoder = (struct video_encoder *)handle->encoder;
        encoder->close(encoder);
    }
    if(handle->para.media_type == CODEC_MEDIA_TYPE_AUDIO) {
        struct audio_encoder *encoder = (struct audio_encoder *)handle->encoder;
        encoder->close(encoder);
    
    }
    free(handle);
    return;
}
