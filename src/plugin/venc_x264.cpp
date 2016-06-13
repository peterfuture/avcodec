#include "codec_av.h"
#include "encoder.h"

extern "C" {
    #include <x264.h>
}

struct x264_context {
    x264_param_t para;;
    x264_t *handle;
    x264_picture_t in;
    x264_picture_t out;

};

static int x264_encoder_open(struct video_encoder *encoder)
{
    return 0;
}

static int x264_encoder_encode(struct video_encoder *encoder, struct codec_packet *pkt, struct codec_frame *frame)
{
    return 0;
}

static int x264_encoder_get_info(struct video_encoder *encoder)
{
    return 0;
}

static int x264_encoder_set_info(struct video_encoder *encoder)
{
    return 0;
}

static int x264_encoder_close(struct video_encoder *encoder)
{
    return 0;
}

struct video_encoder ve_x264_ops = {};
void ve_x264_ops_setup()
{
    ve_x264_ops.name = "X264 Encoder";
    ve_x264_ops.media_format = CODEC_MEDIA_FORMAT_H264;
    ve_x264_ops.open = x264_encoder_open;
    ve_x264_ops.encode = x264_encoder_encode;
    ve_x264_ops.get_info = x264_encoder_get_info;
    ve_x264_ops.set_info = x264_encoder_set_info;
    ve_x264_ops.close = x264_encoder_close;
}