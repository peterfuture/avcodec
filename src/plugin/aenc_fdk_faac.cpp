/*
 * =====================================================================================
 *
 *    Filename   :  aenc_fdkaac.cpp
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
#include <fdk-aac/aacenc_lib.h>
}

#include "log_print.h"
#define TAG "FDK AAC Encoder"

struct fdkaac_context {
    HANDLE_AACENCODER        phAacEncoder;
    uint32_t                encModules;
    uint32_t                maxChannel;
};

static int fdkaac_audio_encoder_open(struct audio_encoder *encoder)
{
    struct fdkaac_context *context = (struct fdkaac_context *)malloc(sizeof(struct fdkaac_context));
    if(!context)
        return -1;
    memset(context, 0, sizeof(struct fdkaac_context));
    struct codec_para *para = &encoder->para;
    context->encModules = 0x01;
    context->maxChannel = 2; 

    AACENC_ERROR ErrorStatus = aacEncOpen(&context->phAacEncoder, 0, 0);
    if(ErrorStatus != AACENC_OK) {
        free(context);
        log_print(TAG, "FAAC Encoder Fail, ret:%d.\n", ErrorStatus );
        return -1;
    }
    aacEncoder_SetParam(context->phAacEncoder, AACENC_SAMPLERATE, para->samplerate);
    aacEncoder_SetParam(context->phAacEncoder, AACENC_CHANNELMODE, para->channels);
    ErrorStatus = aacEncEncode(context->phAacEncoder, NULL, NULL, NULL, NULL);
    AACENC_InfoStruct encInfo;
    ErrorStatus = aacEncInfo(context->phAacEncoder, &encInfo);
    encoder->priv = (void *)context;
    log_print(TAG, "FAAC Encoder Open. maxout:%d input channel:%d framesize:%d\n", (int)encInfo.maxOutBufBytes, (int)encInfo.inputChannels, encInfo.frameLength);
    return 0;
}

static int fdkaac_audio_encoder_encode(struct audio_encoder *encoder, struct codec_packet *pkt, struct codec_frame *frame)
{
    struct fdkaac_context *context = (struct fdkaac_context *)encoder->priv;
    struct codec_para *para = &encoder->para;
    
    AACENC_BufDesc in_buf   = { 0 }, out_buf = { 0 };
    AACENC_InArgs  in_args  = { 0 };
    AACENC_OutArgs out_args = { 0 };
    int in_buffer_identifier = IN_AUDIO_DATA;
    int in_buffer_size, in_buffer_element_size;
    int out_buffer_identifier = OUT_BITSTREAM_DATA;
    int out_buffer_size, out_buffer_element_size;
    void *in_ptr, *out_ptr;
    int ret;
    AACENC_ERROR err;
 
    log_print(TAG, "1-FAAC Encoder One Frame. In:%d Out:%d channels:%d samples:%d\n", frame->size, pkt->size, para->channels, frame->nb_samples);
    in_ptr                   = (void *)frame->data;
    in_buffer_size           = 2 * para->channels * frame->nb_samples;
    in_buffer_element_size   = 2;

    in_args.numInSamples     = para->channels * frame->nb_samples;
    in_buf.numBufs           = 1;
    in_buf.bufs              = &in_ptr;
    in_buf.bufferIdentifiers = &in_buffer_identifier;
    in_buf.bufSizes          = &in_buffer_size;
    in_buf.bufElSizes        = &in_buffer_element_size;

    out_ptr                   = pkt->data;
    out_buffer_size           = pkt->size;
    out_buffer_element_size   = 1;
    out_buf.numBufs           = 1;
    out_buf.bufs              = &out_ptr;
    out_buf.bufferIdentifiers = &out_buffer_identifier;
    out_buf.bufSizes          = &out_buffer_size;
    out_buf.bufElSizes        = &out_buffer_element_size;

    if ((err = aacEncEncode(context->phAacEncoder, &in_buf, &out_buf, &in_args,
                            &out_args)) != AACENC_OK) {
        log_print(TAG, "FAAC Encoder One Frame Fail. error:%d\n", err);
        if (!frame && err == AACENC_ENCODE_EOF)
            return 0;
        return -1;
    }

    if (!out_args.numOutBytes) {
        log_print(TAG, "FAAC Encoder One Frame. No pcm out\n");
        return 0;
    }
    pkt->size = out_args.numOutBytes; 
    log_print(TAG, "FAAC Encoder One Frame. In:%d Out:%d\n", frame->size, pkt->size);
    return out_args.numOutBytes;
}

static int fdkaac_audio_encoder_get_info(struct audio_encoder *encoder)
{
    return 0;
}

static int fdkaac_audio_encoder_set_info(struct audio_encoder *encoder)
{
    return 0;
}

static int fdkaac_audio_encoder_close(struct audio_encoder *encoder)
{
    struct fdkaac_context *context = (struct fdkaac_context *)encoder->priv;
    aacEncClose(&context->phAacEncoder);
    log_print(TAG, "FAAC Encoder Close\n");
    return 0;
}

struct audio_encoder ae_fdkaac_ops = {};
void ae_fdkaac_ops_setup()
{
    ae_fdkaac_ops.name = "FDK AAC Encoder";
    ae_fdkaac_ops.media_format = CODEC_MEDIA_FORMAT_AAC;
    ae_fdkaac_ops.open = fdkaac_audio_encoder_open;
    ae_fdkaac_ops.encode = fdkaac_audio_encoder_encode;
    ae_fdkaac_ops.get_info = fdkaac_audio_encoder_get_info;
    ae_fdkaac_ops.set_info = fdkaac_audio_encoder_set_info;
    ae_fdkaac_ops.close = fdkaac_audio_encoder_close;
}
