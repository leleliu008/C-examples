LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := aes
LOCAL_SRC_FILES := aes.c

include $(BUILD_SHARED_LIBRARY)
