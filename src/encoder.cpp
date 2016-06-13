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

void encoder_register_all()
{
    REGISTER_VIDEO_ENCODER(X264, x264)
	return;
}

static struct video_encoder *video_encoder_select(int media_format)
{
	struct video_encoder *encoder = g_ve;
	if(!encoder) {
        goto fail;
    }
	while(encoder) {
		if(encoder->media_format == media_format) {
			log_print(TAG, "Find Match Video encoder:%s\n", encoder->name);
			return encoder;
		}
		encoder = encoder->next;
	}
fail:
	log_print(TAG, "No Match Video Encoder Found\n");
	return NULL;
}

struct encoder_context *encoder_create(struct codec_para *para)
{
	struct encoder_context *handle = (struct encoder_context *)malloc(sizeof(struct encoder_context));
	if(!handle)
		return NULL;
	memset(handle, 0, sizeof(struct encoder_context));
	memcpy(&handle->para, para, sizeof(struct codec_para));

    struct video_encoder *encoder = NULL;
	if(para->media_type == CODEC_MEDIA_TYPE_VIDEO)
		encoder = video_encoder_select(para->media_format);
	if(!encoder) {
		free(handle);
		return NULL;
	}
    handle->encoder = encoder;
    memcpy(&encoder->para, para, sizeof(struct codec_para));
    if(encoder->open(encoder) < 0) {
        free(handle);
        return NULL;
    }
	return handle;
}

int encoder_encode(struct encoder_context *handle, struct codec_packet *pkt, struct codec_frame *frame)
{
    struct video_encoder *encoder = handle->encoder;
    return encoder->encode(encoder, pkt, frame);
}

void encoder_destroy(struct encoder_context *handle)
{
	struct video_encoder *encoder = handle->encoder;
	encoder->close(encoder);
	free(handle);
	return;
}