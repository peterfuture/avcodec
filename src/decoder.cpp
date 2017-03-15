// Decoder

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decoder.h"
#include "log_print.h"

#define TAG "DECODER"

struct video_decoder *g_vd = NULL;

#define REGISTER_VIDEO_ENCODER(X,x)             \
{                                               \
    extern struct video_decoder vd_##x##_ops;   \
    void vd_##x##_ops_setup();                  \
    vd_##x##_ops_setup();                       \
    register_vdec(&vd_##x##_ops);               \
}

static void register_vdec(struct video_decoder * vdec)
{
    struct video_decoder **p;
    p = &g_vd;
    while (*p != NULL) {
        p = &(*p)->next;
    }
    *p = vdec;
    log_print(TAG, "[%s:%d] register vdec, name:%s fmt:%d \n", __FUNCTION__,
              __LINE__, (*p)->name, (*p)->media_format);
    vdec->next = NULL;
}

static struct video_decoder *video_decoder_select(int media_format)
{
    struct video_decoder *decoder = g_vd;
    if (!decoder) {
        goto fail;
    }
    while (decoder) {
        if (decoder->media_format == media_format) {
            log_print(TAG, "Find Match Video decoder:%s\n", decoder->name);
            return decoder;
        }
        decoder = decoder->next;
    }
fail:
    log_print(TAG, "No Match Video Decoder Found\n");
    return NULL;
}


struct audio_decoder *g_ad = NULL;

#define REGISTER_AUDIO_DECODER(X,x)             \
{                                               \
    extern struct audio_decoder ad_##x##_ops;   \
    void ad_##x##_ops_setup();                  \
    ad_##x##_ops_setup();                       \
    register_adec(&ad_##x##_ops);               \
}

static void register_adec(struct audio_decoder * adec)
{
    struct audio_decoder **p;
    p = &g_ad;
    while (*p != NULL) {
        p = &(*p)->next;
    }
    *p = adec;
    log_print(TAG, "[%s:%d] register aenc, name:%s fmt:%d \n", __FUNCTION__,
              __LINE__, (*p)->name, (*p)->media_format);
    adec->next = NULL;
}

static struct audio_decoder *audio_decoder_select(int media_format)
{
    struct audio_decoder *decoder = g_ad;
    if (!decoder) {
        goto fail;
    }
    while (decoder) {
        if (decoder->media_format == media_format) {
            log_print(TAG, "Find Match Audio decoder:%s\n", decoder->name);
            return decoder;
        }
        decoder = decoder->next;
    }
fail:
    log_print(TAG, "No Match Audio Encoder Found\n");
    return NULL;
}
void decoder_register_all()
{
#ifdef ENABLE_LINUX
#endif
#ifdef ENABLE_ANDROID
#endif
    return;
}

struct decoder_context *decoder_create(struct codec_para *para)
{
    struct decoder_context *handle = (struct decoder_context *)malloc(sizeof(
                                         struct decoder_context));
    if (!handle) {
        return NULL;
    }
    memset(handle, 0, sizeof(struct decoder_context));
    memcpy(&handle->para, para, sizeof(struct codec_para));

    if (para->media_type == CODEC_MEDIA_TYPE_VIDEO) {
        handle->decoder = (void *)video_decoder_select(para->media_format);
    }
    if (!handle->decoder) {
        free(handle);
        return NULL;
    }

    return handle;
}
int decoder_decode(struct decoder_context *handle, struct codec_frame *frame,
                   int *got_frame, struct codec_packet *pkt)
{
    if (handle->para.media_type == CODEC_MEDIA_TYPE_VIDEO) {
        struct video_decoder *decoder = (struct video_decoder *)handle->decoder;
        return decoder->decode(decoder, frame, got_frame, pkt);
    }

    return -1;
}
void decoder_destroy(struct decoder_context * handle)
{
    return;
}
