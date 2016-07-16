#include "codec_api.h"

int main(int argc, char **argv)
{
    codec_register_all();

    struct codec_packet pkt;
    struct codec_frame frame;

    // decoder test
    struct codec_para para;
    para.media_format = CODEC_MEDIA_FORMAT_H264;
    para.is_encoder = 0;
    para.media_type = CODEC_MEDIA_TYPE_VIDEO;
    para.width = 1280;
    para.height = 720;
    struct codec_context *codec = codec_create_codec(&para);
    codec_destroy_codec(codec);

    // video encoder test
    memset(&para, 0, sizeof(struct codec_para));
    para.media_format = CODEC_MEDIA_FORMAT_H264;
    para.is_encoder = 1;
    para.media_type = CODEC_MEDIA_TYPE_VIDEO;
    para.width = 1280;
    para.height = 720;
    codec = codec_create_codec(&para);
    pkt.data = (uint8_t *)malloc(1280 * 720 * 4);
    frame.key = 1;
    frame.data = (uint8_t *)malloc(1280 * 720 * 4);
    memset(frame.data, 256, 1000);
    codec_encode_frame(codec, &pkt, &frame);
    codec_destroy_codec(codec);
    free(pkt.data);
    free(frame.data);

    // audio Encoder test
    memset(&para, 0, sizeof(struct codec_para));
    para.media_format = CODEC_MEDIA_FORMAT_AAC;
    para.is_encoder = 1;
    para.media_type = CODEC_MEDIA_TYPE_AUDIO;
    para.samplerate = 44100;
    para.channels = 2;
    codec = codec_create_codec(&para);
    pkt.data = (uint8_t *)malloc(1280 * 720 * 4);
    pkt.size = 1280 * 720 * 4;
    frame.key = 1;
    frame.data = (uint8_t *)malloc(1280 * 720 * 4);
    frame.size = 44100*2;
    frame.nb_samples = 44100;
    codec_encode_frame(codec, &pkt, &frame);
    codec_destroy_codec(codec);
    free(pkt.data);
    free(frame.data);

    return 0;
}
