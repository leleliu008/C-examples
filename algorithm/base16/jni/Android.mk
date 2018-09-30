LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := base16
LOCAL_SRC_FILES := base16.c

include $(BUILD_SHARED_LIBRARY)
