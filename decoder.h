#ifndef DECODER_H
#define DECODER_H

struct decoder_para
{
};

struct decoder_context 
{
};

struct decoder_context *decoder_create();
void decoder_destroy(struct decoder_context *handle);

#endif
