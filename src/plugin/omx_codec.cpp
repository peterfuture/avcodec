#ifdef ENABLE_ANDROID

#include <utils/Log.h>

#include <binder/ProcessState.h>
#include <media/stagefright/MetaData.h>
#include <media/stagefright/MediaBufferGroup.h>
#include <media/stagefright/MediaDefs.h>
#include <media/stagefright/OMXClient.h>
#include <media/stagefright/OMXCodec.h>
#include <utils/List.h>
#include <new>
#include <map>

#include "codec_av.h"

#define OMX_QCOM_COLOR_FormatYVU420SemiPlanar 0x7FA30C00
#define FF_INPUT_BUFFER_PADDING_SIZE 32
#define TAG "OMX_DECODER"

using namespace android;

struct TimeStamp {
    int64_t pts;
    int64_t reordered_opaque;
};

struct omx_codec_context {
    uint8_t *mExtradata;
    int mExtraDataSize;

    sp<MediaSource> *mMediaSource;
    List<struct codec_frame *> *mQueueIn, *mQueueOut;

    struct codec_frame *mLastFrame;
    bool mMediaSourceDone;


    OMXClient *mOMXClient;
    sp<MediaSource> *mDecoder;
    const char *mDecoderComponent;

    std::map<int64_t, TimeStamp> *mTsTimeStampMap;
};

int omx_decoder_init()
{
    ALOGE("Enter omxdecoder init\n");
    int ret = 0;
    struct omx_codec_context *codec = new omx_codec_context;
    sp<MetaData> meta, outFormat;
    meta = new MetaData;
    meta->setCString(kKeyMIMEType, MEDIA_MIMETYPE_VIDEO_AVC);
    meta->setInt32(kKeyWidth, 1024);
    meta->setInt32(kKeyHeight, 768);

    android::ProcessState::self()->startThreadPool();
    codec->mMediaSource = new sp<MediaSource>();
        
    //*codec->source   = new CustomSource(decoder, meta);
    codec->mQueueIn  = new List<struct codec_frame *>;
    codec->mQueueOut = new List<struct codec_frame *>;
    codec->mTsTimeStampMap = new std::map<int64_t, TimeStamp>;
    codec->mOMXClient  = new OMXClient;
    codec->mLastFrame = (struct codec_frame *)malloc(sizeof(struct codec_frame));

    if (codec->mOMXClient->connect() !=  OK) {
        ret = -1;
        goto fail;
    }

    ALOGE("Exit omxdecoder init\n");
    goto fail;
    return ret;

fail:
    if(codec->mExtraDataSize > 0)
        free(codec->mExtradata);
    free(codec->mLastFrame);
    delete codec->mQueueIn;
    delete codec->mQueueOut;
    delete codec->mTsTimeStampMap;
    delete codec->mOMXClient;
    return ret;
}

#endif