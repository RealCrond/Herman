LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE:= easytcpserver

LOCAL_C_INCLUDES     :=   $(LOCAL_PATH)/../../SocketServer
						  
MODULE_SRC_CPPFILES	:= $(wildcard $(LOCAL_PATH)/../../../SocketServer/*.cpp)						
LOCAL_SRC_FILES 	:= $(subst $(LOCAL_PATH)/,,$(MODULE_SRC_CPPFILES))

#LOCAL_SRC_FILES 	:=   $(LOCAL_PATH)/../../../SocketServer/compiledemo.cpp  \
						$(LOCAL_PATH)/../../../SocketServer/easytcpserver.cpp 
						
LOCAL_LDFLAGS += -shared
#LOCAL_LDFLAGS += $(RELEASE_LIB)/libosp.so
	
LOCAL_ARM_MODE := arm				
include $(BUILD_EXECUTABLE) 