LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := cJSON
LOCAL_SRC_FILES := cJSON.c

include $(BUILD_SHARED_LIBRARY)
