LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := myLibName
LOCAL_SRC_FILES := test.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../ffmpeg
LOCAL_SHARED_LIBRARIES := ffmpeg
include $(BUILD_SHARED_LIBRARY)