
ComSur_PATH := ../ComSur

#*********************************************************************************************************
# Source list
#*********************************************************************************************************
LOCAL_SRCS +=  \
$(ComSur_PATH)/IES_IMDC.cpp \
$(ComSur_PATH)/IES_IMDI.cpp \
$(ComSur_PATH)/IES_IMDO.cpp \
$(ComSur_PATH)/IES_IMFlag.cpp \
$(ComSur_PATH)/IES_IMPub.cpp \
$(ComSur_PATH)/IES_IMRec.cpp \
$(ComSur_PATH)/IES_IMSam.cpp \
$(ComSur_PATH)/IES_IMSrc.cpp \
$(ComSur_PATH)/IES_IMInit.cpp \
$(ComSur_PATH)/IES_SCLmain.cpp \
$(ComSur_PATH)/IES_SCLother.cpp \
#*********************************************************************************************************
# Header file search path (eg. LOCAL_INC_PATH := -I"Your header files search path")
#*********************************************************************************************************
LOCAL_INC_PATH +=  \
-I "$(ComSur_PATH)/" 
