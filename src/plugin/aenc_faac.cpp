/*
 * =====================================================================================
 *
 *    Filename   :  aenc_faac.cpp
 *    Description:
 *    Version    :  1.0
 *    Created    :  2016年07月15日 09时46分40秒
 *    Revision   :  none
 *    Compiler   :  gcc
 *    Author     :  peter-s
 *    Email      :  peter_future@outlook.com
 *    Company    :  dt
 *
 * =====================================================================================
 */

#include "codec_av.h"
#include "encoder.h"

extern "C" {
#include <faac.h>
}

#include "log_print.h"
#define TAG "FAAC Encoder"

static int faac_audio_encoder_open(struct audio_encoder *encoder)
{
    log_print(TAG, "FAAC Encoder Open\n");
    return 0;
}

static int faac_audio_encoder_encode(struct audio_encoder *encoder, struct codec_packet *pkt, struct codec_frame *frame)
{
    log_print(TAG, "FAAC Encoder One Frame\n");
    return 0;
}

static int faac_audio_encoder_get_info(struct audio_encoder *encoder)
{
    return 0;
}

static int faac_audio_encoder_set_info(struct audio_encoder *encoder)
{
    return 0;
}

static int faac_audio_encoder_close(struct audio_encoder *encoder)
{
    log_print(TAG, "FAAC Encoder Close\n");
    return 0;
}

struct audio_encoder ae_faac_ops = {};
void ae_faac_ops_setup()
{
    ae_faac_ops.name = "FAAC Encoder";
    ae_faac_ops.media_format = CODEC_MEDIA_FORMAT_AAC;
    ae_faac_ops.open = faac_audio_encoder_open;
    ae_faac_ops.encode = faac_audio_encoder_encode;
    ae_faac_ops.get_info = faac_audio_encoder_get_info;
    ae_faac_ops.set_info = faac_audio_encoder_set_info;
    ae_faac_ops.close = faac_audio_encoder_close;
}
