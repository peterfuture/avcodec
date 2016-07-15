#include "codec_av.h"
#include "encoder.h"

extern "C" {
#include <x264.h>
}

#include "log_print.h"
#define TAG "X264 Encoder"

struct x264_context {
    x264_param_t para;;
    x264_t *handle;
    x264_picture_t in;
    x264_picture_t out;

};

static int x264_video_encoder_open(struct video_encoder *encoder)
{
    struct x264_context *x264 = (struct x264_context *)malloc(sizeof(struct x264_context));
    x264_param_t *x264_para = &x264->para;
    struct codec_para *codec_para = &encoder->para;

    // 0. building encoder parameters.
    x264_param_default_preset(x264_para, "ultrafast", "zerolatency");

    x264_para->i_width = codec_para->width;
    x264_para->i_height = codec_para->height;
    x264_para->i_threads = 1;
    x264_para->b_repeat_headers = 1;
    x264_para->b_intra_refresh = 1;

    x264_para->rc.i_rc_method = X264_RC_CQP;
    x264_para->rc.i_qp_constant = 24;
    x264_para->rc.i_qp_min = 24;
    x264_para->rc.i_qp_max = 24;
    //x264_param_default(&opt);
    x264_param_apply_profile(x264_para, "baseline");

    // 1. Prepare the output buffer and target file
    x264_picture_alloc(&x264->in,  X264_CSP_NV12, x264_para->i_width, x264_para->i_height);
    x264_picture_alloc(&x264->out, X264_CSP_NV12, x264_para->i_width, x264_para->i_height);

    // 2. Building the encoder handler
    x264->handle = x264_encoder_open(x264_para);
    x264_encoder_parameters(x264->handle, x264_para);

    encoder->priv = (void *)x264;
    log_print(TAG, "X264 Encoder Open\n");
    return 0;
}

static int x264_video_encoder_encode(struct video_encoder *encoder, struct codec_packet *pkt, struct codec_frame *frame)
{
    struct x264_context *x264 = (struct x264_context *)encoder->priv;
    x264_param_t *x264_para = &x264->para;
    int width = x264_para->i_width;
    int height = x264_para->i_height;
    memcpy(x264->in.img.plane[0], frame->data, width * height);
    memcpy(x264->in.img.plane[1], frame->data + width * height - 1, width * height / 2);

    if (frame->key == 1) {
        x264->in.i_type = X264_TYPE_IDR;
    } else {
        x264->in.i_type = X264_TYPE_P;
    }

    int nals;
    x264_nal_t *nal_pointer;
    int ret = x264_encoder_encode(x264->handle, &nal_pointer, &nals, &x264->in, &x264->out);
    if (ret <= 0) {
        return ret;
    }

    int outLength = 0;
    for (int i = 0; i < nals; i++) {
        if (nal_pointer[i].i_type != 6) {
            x264_nal_t* nal = &nal_pointer[i];
            memcpy(&pkt->data[outLength], nal->p_payload, nal->i_payload);
            outLength += nal->i_payload;
        }
    }

    // setup pkt
    pkt->size = outLength;
    pkt->format = CODEC_MEDIA_FORMAT_H264;
    pkt->pts = -1;
    pkt->key = frame->key;

    return outLength;
}

static int x264_video_encoder_get_info(struct video_encoder *encoder)
{
    return 0;
}

static int x264_video_encoder_set_info(struct video_encoder *encoder)
{
    return 0;
}

static int x264_video_encoder_close(struct video_encoder *encoder)
{
    return 0;
}

struct video_encoder ve_x264_ops = {};
void ve_x264_ops_setup()
{
    ve_x264_ops.name = "X264 Encoder";
    ve_x264_ops.media_format = CODEC_MEDIA_FORMAT_H264;
    ve_x264_ops.open = x264_video_encoder_open;
    ve_x264_ops.encode = x264_video_encoder_encode;
    ve_x264_ops.get_info = x264_video_encoder_get_info;
    ve_x264_ops.set_info = x264_video_encoder_set_info;
    ve_x264_ops.close = x264_video_encoder_close;
}