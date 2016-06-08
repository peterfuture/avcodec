// Decoder

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decoder.h"
#include "log_print.h"

#define TAG "DECODER"

struct video_decoder *g_vd = NULL;

void decoder_register_all()
{
#ifdef ENABLE_LINUX
#endif
#ifdef ENABLE_ANDROID
#endif
	return;
}

static struct video_decoder *video_decoder_select(int media_format)
{
	struct video_decoder *decoder = g_vd;
	if(!decoder)
		goto fail;
	while(!decoder) {
		if(decoder->media_format == media_format) {
			log_print(TAG, "Find Match Video Decoder \n", decoder->name);
			return decoder;
		}
		decoder = decoder->next;
	}
fail:
	log_print(TAG, "No Match Video Decoder Found\n");
	return NULL;
}

struct decoder_context *decoder_create(struct codec_para *para)
{
	struct decoder_context *handle = (struct decoder_context *)malloc(sizeof(struct decoder_context));
	if(!handle)
		return NULL;
	memset(handle, 0, sizeof(struct decoder_context));
	memcpy(&handle->para, para, sizeof(struct codec_para));

	if(para->media_type == CODEC_MEDIA_TYPE_VIDEO)
		handle->decoder = (void *)video_decoder_select(para->media_format);
	if(!handle->decoder) {
		free(handle);
		return NULL;
	}

	return handle;
}

void decoder_destroy()
{
	return;
}