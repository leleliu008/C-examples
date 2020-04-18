LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := sha256
LOCAL_SRC_FILES := sha256.c platform_util.c threading.c

include $(BUILD_SHARED_LIBRARY)
