/*API*/

#ifndef CODEC_API_H
#define CODEC_API_H

struct codec_para
{
    int type;
};

struct codec_context {
    int type;
};

struct codec_packet;
struct codec_frame;

struct codec_context *codec_create(struct codec_para *para);
int codec_process();
void codec_destroy(struct codec_context *handle);

#endif
