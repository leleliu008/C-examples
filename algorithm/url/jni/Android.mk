LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := url
LOCAL_SRC_FILES := url.c

include $(BUILD_SHARED_LIBRARY)
