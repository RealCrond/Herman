LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE:= easytcpserver

LOCAL_C_INCLUDES     	:=   $(LOCAL_PATH)/../../../SocketServer \
							 $(LOCAL_PATH)/../../../../../10_common/include/EasyTcp
						  
#MODULE_SRC_CPPFILES	:= $(wildcard $(LOCAL_PATH)/../../../SocketServer/*.cpp)						
#LOCAL_SRC_FILES 		:= $(subst $(LOCAL_PATH)/,,$(MODULE_SRC_CPPFILES))

LOCAL_SRC_FILES 		:= $(LOCAL_PATH)/../../../SocketServer/SocketServer.cpp  \
						   $(LOCAL_PATH)/../../../SocketServer/CEasyTcpServer.cpp
			

LOCAL_LDFLAGS += -shared
			
LOCAL_ARM_MODE := arm			
include $(BUILD_EXECUTABLE)  