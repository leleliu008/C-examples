LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := BCC
LOCAL_SRC_FILES := BCC.c

include $(BUILD_SHARED_LIBRARY)
