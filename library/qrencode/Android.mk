LOCAL_PATH      := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := qrencode
LOCAL_SRC_FILES := qrencode

include $(BUILD_SHARED_LIBRARY)
