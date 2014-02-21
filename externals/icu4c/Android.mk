LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifneq ($(OSMAND_BUILDING_NEON_LIBRARY),true)
    LOCAL_MODULE := osmand_icu4c
else
    LOCAL_MODULE := osmand_icu4c_neon
    LOCAL_ARM_NEON := true
endif

LOCAL_EXPORT_C_INCLUDES := \
    $(LOCAL_PATH)/public_include

ifneq ($(OSMAND_USE_PREBUILT),true)
    LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/upstream.patched/source/common \
        $(LOCAL_PATH)/upstream.patched/source/i18n

    common_SRC_FILES := $(wildcard $(LOCAL_PATH)/upstream.patched/source/common/*.c*)
    i18n_SRC_FILES := $(wildcard $(LOCAL_PATH)/upstream.patched/source/i18n/*.c*)

    LOCAL_SRC_FILES := \
        $(common_SRC_FILES:$(LOCAL_PATH)/%=%) \
        $(i18n_SRC_FILES:$(LOCAL_PATH)/%=%)

    include $(BUILD_STATIC_LIBRARY)
else
    LOCAL_SRC_FILES := \
        $(OSMAND_ANDROID_PREBUILT_ROOT)/$(TARGET_ARCH_ABI)/lib$(LOCAL_MODULE).a
    include $(PREBUILT_STATIC_LIBRARY)
endif
