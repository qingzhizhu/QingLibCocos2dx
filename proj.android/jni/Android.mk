LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../QingLibCocos2dx/Classes/AppDelegate.cpp \
#                   ../../QingLibCocos2dx/Classes/HelloWorldScene.cpp
#                   
#LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../QingLibCocos2dx/Classes                   

include $(LOCAL_PATH)/Sources.mk
include $(LOCAL_PATH)/Includes.mk

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
