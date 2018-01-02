LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := sha256
LOCAL_SRC_FILES := sha256.c

include $(BUILD_SHARED_LIBRARY)
