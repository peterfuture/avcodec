/*API*/

#ifndef CODEC_API_H
#define CODEC_API_H

enum CODEC_MEDIA_TYPE{
    CODEC_MEDIA_TYPE_UNKOWN    = -1,
    CODEC_MEDIA_TYPE_AUDIO     = 0,
    CODEC_MEDIA_TYPE_VIDEO     = 1
};

enum CODEC_MEDIA_FORMAT{
    CODEC_MEDIA_FORMAT_UNKOWN    = -1,
    // VIDEO
    CODEC_MEDIA_FORMAT_H264      = 0,
    CODEC_MEDIA_FORMAT_H265      = 1,

    //AUDIO
    CODEC_MEDIA_FORMAT_FAAD      = 0X100
};

#define CODEC_ENCODER 0
#define CODEC_DECODER 1

struct codec_para
{
    int media_type;
    int media_format;
    int is_encoder;
};

struct codec_context {
    struct codec_para para;
    void *codec; // pointer to decoder&encoder context
};

struct codec_packet;
struct codec_frame;

void codec_register_all();

struct codec_context *codec_create_codec(struct codec_para *para);
int codec_decode_frame();
int codec_encode_frame();
int codec_get_parameter();
int codec_set_parameter();
int codec_destroy_codec(struct codec_context *handle);

#endif
