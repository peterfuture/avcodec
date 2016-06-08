LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:=                       \
        codec_api.cpp                   \
        decoder.cpp                     \
        encoder.cpp                     \

LOCAL_SRC_FILES+=                       \
        plugin/omx_codec.cpp            \

LOCAL_C_INCLUDES:=                      \
        $(TOP)/frameworks/av/include/media/stagefright/ \
        $(TOP)/frameworks/native/include/media/openmax/ \
	$(LOCAL_PATH)/include           \
        $(LOCAL_PATH)                   \
        
LOCAL_SHARED_LIBRARIES:=                \
        libbinder                       \
        libstagefright                  \
        libutils                        \
        libcutils                       \
        liblog                          \

LOCAL_SHARED_LIBRARIES += libstlport
include $(TOP)/external/stlport/libstlport.mk

LOCAL_MODULE:= libandroid_codec

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE    := omx_test
LOCAL_MODULE_TAGS := tests
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES+=                       \
        test/omx_test.cpp               \

LOCAL_C_INCLUDES:=                      \
	$(LOCAL_PATH)/include           \
        
LOCAL_SHARED_LIBRARIES:=                \
        libandroid_codec                \

LOCAL_SHARED_LIBRARIES+=                \
        liblog                          \

include $(BUILD_EXECUTABLE)
