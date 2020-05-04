LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hmac
LOCAL_SRC_FILES := $(wildcard mbedtls/*.c)

include $(BUILD_SHARED_LIBRARY)
