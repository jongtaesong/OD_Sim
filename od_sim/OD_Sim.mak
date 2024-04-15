
############# Target type (Debug/Release) ##################
############################################################
CPPCompileDebug=-g
CPPCompileRelease=-O
LinkDebug=-g
LinkRelease=-O

ConfigurationCPPCompileSwitches=   -I. -I. -I$(OMROOT) -I$(OMROOT)/LangCpp  $(INST_FLAGS)  -I$(OMROOT)/LangCpp/oxf $(INCLUDE_PATH) $(INST_INCLUDES) -DUSE_IOSTREAM $(CPPCompileDebug) -c   

#########################################
###### Predefined macros ################
RM=/bin/rm -rf
MD=/bin/mkdir -p
INCLUDE_QUALIFIER=-I
DEFINE_QUALIFIER=-D
CC=gcc -DUSE_IOSTREAM
LIB_CMD=ar
LINK_CMD=$(CC)
LIB_FLAGS=rvu
LINK_FLAGS=-lpthread -lstdc++ -lrt $(LinkDebug)  

#########################################
####### Context macros ##################

FLAGSFILE=
RULESFILE=
OMROOT="./Share"
RHPROOT="."

CPP_EXT=.cpp
H_EXT=.h
OBJ_EXT=.o
EXE_EXT=
LIB_EXT=.a

INSTRUMENTATION=None

TIME_MODEL=RealTime

TARGET_TYPE=Executable

TARGET_NAME=OD_Sim

all : $(TARGET_NAME)$(EXE_EXT) OD_Sim.mak

TARGET_MAIN=MainDefaultComponent

LIBS=

INCLUDE_PATH= \
  $(INCLUDE_QUALIFIER)$(OMROOT)/LangCpp/osconfig/Linux

ADDITIONAL_OBJS=

OBJS= \
  Application.o \
  ODSim.o \
  Packet.o \
  Serializer.o \
  Device.o \
  PriorityPacketQueue.o \
  ODSimElement.o \
  PacketQueue.o \
  AppStats.o \
  SwitchCxl.o \
  SwitchOptics.o \
  ODNetConfig.o \
  VOQueue.o \
  PriorityVOQueue.o \
  FlexODSim.o \
  ConnMap.o \
  Default.o




#########################################
####### Predefined macros ###############
$(OBJS) :  $(INST_LIBS) $(OXF_LIBS)

OBJ_DIR=

ifeq ($(OBJ_DIR),)
CREATE_OBJ_DIR=
CLEAN_OBJ_DIR=
else
CREATE_OBJ_DIR= $(MD) $(OBJ_DIR)
CLEAN_OBJ_DIR=  $(RM) $(OBJ_DIR)
endif


ifeq ($(INSTRUMENTATION),Animation)

INST_FLAGS=-DOMANIMATOR
INST_INCLUDES=-I$(OMROOT)/LangCpp/aom -I$(OMROOT)/LangCpp/tom
INST_LIBS= $(OMROOT)/LangCpp/lib/linuxaomanim$(LIB_EXT)
OXF_LIBS=$(OMROOT)/LangCpp/lib/linuxoxfinst$(LIB_EXT) $(OMROOT)/LangCpp/lib/linuxomcomappl$(LIB_EXT) $(OMROOT)/LangCpp/lib/linuxoxsiminst$(LIB_EXT)
SOCK_LIB=

else
ifeq ($(INSTRUMENTATION),Tracing)

INST_FLAGS=-DOMTRACER
INST_INCLUDES=-I$(OMROOT)/LangCpp/aom -I$(OMROOT)/LangCpp/tom
INST_LIBS=$(OMROOT)/LangCpp/lib/linuxtomtrace$(LIB_EXT) $(OMROOT)/LangCpp/lib/linuxaomtrace$(LIB_EXT)
OXF_LIBS= $(OMROOT)/LangCpp/lib/linuxoxfinst$(LIB_EXT) $(OMROOT)/LangCpp/lib/linuxomcomappl$(LIB_EXT) $(OMROOT)/LangCpp/lib/linuxoxsiminst$(LIB_EXT)
SOCK_LIB=

else
ifeq ($(INSTRUMENTATION),None)

INST_FLAGS=
INST_INCLUDES=
INST_LIBS=
OXF_LIBS=$(OMROOT)/LangCpp/lib/linuxoxf$(LIB_EXT) $(OMROOT)/LangCpp/lib/linuxoxsim$(LIB_EXT)
SOCK_LIB=

else
	@echo An invalid Instrumentation $(INSTRUMENTATION) is specified.
	exit
endif
endif
endif

.SUFFIXES: $(CPP_EXT)



#####################################################################
##################### Context dependencies and commands #############






Application.o : Application.cpp Application.h    Default.h Serializer.h PacketQueue.h AppStats.h SwitchCxl.h Device.h SwitchOptics.h ConnMap.h Packet.h ODSimElement.h 
	@echo Compiling Application.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o Application.o Application.cpp




ODSim.o : ODSim.cpp ODSim.h    Default.h Application.h Device.h SwitchCxl.h FlexODSim.h ODNetConfig.h 
	@echo Compiling ODSim.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o ODSim.o ODSim.cpp




Packet.o : Packet.cpp Packet.h    Default.h 
	@echo Compiling Packet.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o Packet.o Packet.cpp




Serializer.o : Serializer.cpp Serializer.h    Default.h Packet.h 
	@echo Compiling Serializer.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o Serializer.o Serializer.cpp




Device.o : Device.cpp Device.h    Default.h Application.h PriorityPacketQueue.h Serializer.h SwitchCxl.h PriorityVOQueue.h ConnMap.h SwitchOptics.h Packet.h ODSimElement.h 
	@echo Compiling Device.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o Device.o Device.cpp




PriorityPacketQueue.o : PriorityPacketQueue.cpp PriorityPacketQueue.h    Default.h PacketQueue.h Packet.h ODSimElement.h 
	@echo Compiling PriorityPacketQueue.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o PriorityPacketQueue.o PriorityPacketQueue.cpp




ODSimElement.o : ODSimElement.cpp ODSimElement.h    Default.h 
	@echo Compiling ODSimElement.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o ODSimElement.o ODSimElement.cpp




PacketQueue.o : PacketQueue.cpp PacketQueue.h    Default.h Packet.h ODSimElement.h 
	@echo Compiling PacketQueue.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o PacketQueue.o PacketQueue.cpp




AppStats.o : AppStats.cpp AppStats.h    Default.h 
	@echo Compiling AppStats.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o AppStats.o AppStats.cpp




SwitchCxl.o : SwitchCxl.cpp SwitchCxl.h    Default.h Application.h Device.h ConnMap.h Serializer.h Packet.h ODSimElement.h 
	@echo Compiling SwitchCxl.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o SwitchCxl.o SwitchCxl.cpp




SwitchOptics.o : SwitchOptics.cpp SwitchOptics.h    Default.h Application.h Device.h ConnMap.h Packet.h ODSimElement.h 
	@echo Compiling SwitchOptics.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o SwitchOptics.o SwitchOptics.cpp




ODNetConfig.o : ODNetConfig.cpp ODNetConfig.h    Default.h 
	@echo Compiling ODNetConfig.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o ODNetConfig.o ODNetConfig.cpp




VOQueue.o : VOQueue.cpp VOQueue.h    Default.h PacketQueue.h Packet.h ODSimElement.h 
	@echo Compiling VOQueue.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o VOQueue.o VOQueue.cpp




PriorityVOQueue.o : PriorityVOQueue.cpp PriorityVOQueue.h    Default.h VOQueue.h Packet.h ODSimElement.h 
	@echo Compiling PriorityVOQueue.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o PriorityVOQueue.o PriorityVOQueue.cpp




FlexODSim.o : FlexODSim.cpp FlexODSim.h    Default.h Application.h Device.h SwitchOptics.h SwitchCxl.h ConnMap.h ODNetConfig.h 
	@echo Compiling FlexODSim.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o FlexODSim.o FlexODSim.cpp




ConnMap.o : ConnMap.cpp ConnMap.h    Default.h 
	@echo Compiling ConnMap.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o ConnMap.o ConnMap.cpp




Default.o : Default.cpp Default.h    Application.h ODSim.h Packet.h Serializer.h Device.h PriorityPacketQueue.h ODSimElement.h PacketQueue.h AppStats.h SwitchCxl.h SwitchOptics.h ODNetConfig.h VOQueue.h PriorityVOQueue.h FlexODSim.h ConnMap.h 
	@echo Compiling Default.cpp
	$(CREATE_OBJ_DIR)
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o Default.o Default.cpp







$(TARGET_MAIN)$(OBJ_EXT) : $(TARGET_MAIN)$(CPP_EXT) $(OBJS) 
		@$(CC) $(ConfigurationCPPCompileSwitches) -o  $(TARGET_MAIN)$(OBJ_EXT) $(TARGET_MAIN)$(CPP_EXT)

####################################################################################
#                    Predefined linking instructions                               #
# INST_LIBS is included twice to solve bi-directional dependency between libraries #
####################################################################################
$(TARGET_NAME)$(EXE_EXT): $(OBJS) $(ADDITIONAL_OBJS) $(TARGET_MAIN)$(OBJ_EXT) OD_Sim.mak 
	@echo Linking $(TARGET_NAME)$(EXE_EXT)
	@$(LINK_CMD)  $(TARGET_MAIN)$(OBJ_EXT) $(OBJS) $(ADDITIONAL_OBJS) \
	$(LIBS) \
	$(INST_LIBS) \
	$(OXF_LIBS) \
	$(INST_LIBS) \
	$(SOCK_LIB) \
	$(LINK_FLAGS) -o $(TARGET_NAME)$(EXE_EXT)

$(TARGET_NAME)$(LIB_EXT) : $(OBJS) $(ADDITIONAL_OBJS) OD_Sim.mak
	@echo Building library $@
	@$(LIB_CMD) $(LIB_FLAGS) $(TARGET_NAME)$(LIB_EXT) $(OBJS) $(ADDITIONAL_OBJS) $(LIBS)



clean:
	@echo Cleanup
	$(RM) Application.o
	$(RM) ODSim.o
	$(RM) Packet.o
	$(RM) Serializer.o
	$(RM) Device.o
	$(RM) PriorityPacketQueue.o
	$(RM) ODSimElement.o
	$(RM) PacketQueue.o
	$(RM) AppStats.o
	$(RM) SwitchCxl.o
	$(RM) SwitchOptics.o
	$(RM) ODNetConfig.o
	$(RM) VOQueue.o
	$(RM) PriorityVOQueue.o
	$(RM) FlexODSim.o
	$(RM) ConnMap.o
	$(RM) Default.o
	$(RM) $(TARGET_MAIN)$(OBJ_EXT) $(ADDITIONAL_OBJS)
	$(RM) $(TARGET_NAME)$(LIB_EXT)
	$(RM) $(TARGET_NAME)$(EXE_EXT)
	$(CLEAN_OBJ_DIR)
