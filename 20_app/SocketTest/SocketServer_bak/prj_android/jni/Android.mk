LOCAL_PATH := $(call my-dir)

#清除编译系统全局变量
include $(CLEAR_VARS)

subdirs := $(LOCAL_PATH)/../compile.mk

include $(subdirs)
