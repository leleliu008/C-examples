LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := aes
LOCAL_SRC_FILES := aes.c platform_util.c platform.c threading.c

include $(BUILD_SHARED_LIBRARY)
