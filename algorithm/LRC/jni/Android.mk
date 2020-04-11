LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := LRC
LOCAL_SRC_FILES := LRC.c

include $(BUILD_SHARED_LIBRARY)
