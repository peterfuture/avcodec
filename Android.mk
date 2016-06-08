LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:=                               \
        src/codec_api.cpp                       \
        src/decoder.cpp                         \
        src/encoder.cpp                         \

LOCAL_SRC_FILES+=                               \
        src/plugin/omx_codec.cpp                \

LOCAL_C_INCLUDES:=                              \
        $(TOP)/frameworks/av/include/media/stagefright/ \
        $(TOP)/frameworks/native/include/media/openmax/ \
	$(LOCAL_PATH)/include                   \
        $(LOCAL_PATH)/src/                      \
        
LOCAL_SHARED_LIBRARIES:=                        \
        libbinder                               \
        libstagefright                          \
        libutils                                \
        libcutils                               \
        liblog                                  \

LOCAL_SHARED_LIBRARIES += libstlport
include $(TOP)/external/stlport/libstlport.mk

LOCAL_CFLAGS += -DENABLE_ANDROID

LOCAL_MODULE:= libdtcodec

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE    := codec_test
LOCAL_MODULE_TAGS := tests
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES+=                       \
        test/codec_test.cpp             \

LOCAL_C_INCLUDES:=                      \
	$(LOCAL_PATH)/include           \
        
LOCAL_SHARED_LIBRARIES:=                \
        libdtcodec                      \

LOCAL_SHARED_LIBRARIES+=                \
        liblog                          \

include $(BUILD_EXECUTABLE)
