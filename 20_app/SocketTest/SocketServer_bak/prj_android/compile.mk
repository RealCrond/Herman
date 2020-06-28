LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE:= easytcpserver.apk

LOCAL_C_INCLUDES     	:=   $(LOCAL_PATH)/../include \
							 $(LOCAL_PATH)/../../../../10_common/include/EasyTcp
						  
MODULE_SRC_CPPFILES	    := $(wildcard $(LOCAL_PATH)/../source/*.cpp)						
LOCAL_SRC_FILES 		:= $(subst $(LOCAL_PATH)/,,$(MODULE_SRC_CPPFILES))
LOCAL_SRC_FILES         := $(subst $(LOCAL_PATH)/,,$(MODULE_SRC_CPPFILES))\
		

#LOCAL_LDFLAGS += -shared
			
#LOCAL_ARM_MODE := arm			
include $(BUILD_EXECUTABLE)  