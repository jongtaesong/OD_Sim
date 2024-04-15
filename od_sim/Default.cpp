/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Default
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/Default.cpp
*********************************************************************/

//## auto_generated
#include "Default.h"
//## auto_generated
#include "Application.h"
//## auto_generated
#include "AppStats.h"
//## auto_generated
#include "ConnMap.h"
//## auto_generated
#include "Device.h"
//## auto_generated
#include "FlexODSim.h"
//## auto_generated
#include "ODNetConfig.h"
//## auto_generated
#include "ODSim.h"
//## auto_generated
#include "ODSimElement.h"
//## auto_generated
#include "Packet.h"
//## auto_generated
#include "PacketQueue.h"
//## auto_generated
#include "PriorityPacketQueue.h"
//## auto_generated
#include "PriorityVOQueue.h"
//## auto_generated
#include "Serializer.h"
//## auto_generated
#include "SwitchCxl.h"
//## auto_generated
#include "SwitchOptics.h"
//## auto_generated
#include "VOQueue.h"
//## package Default


//## attribute DEBUG
int DEBUG(0);

//## attribute IsFlowControlled_
int IsFlowControlled_;

//## attribute IsThrottled
int IsThrottled;

//## attribute RespLinkCheck__
int RespLinkCheck__;

//## attribute StrictPriority
int StrictPriority;

//## attribute delay_statistics
int delay_statistics[1000];

//## attribute sim_result
FILE * sim_result;

//## attribute sim_result2
FILE * sim_result2;

//## attribute sim_result3
FILE * sim_result3;

//## operation debug(char*,char*,int,char*,int,char*)
void debug(char* name, char* st1, int n1, char* st2, int n2, char* fn) {
    //#[ operation debug(char*,char*,int,char*,int,char*)
    printf("%s: %s:%d, %s:%d, function:%s\n", name, st1, n1, st2, n2, fn);
    //#]
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/Default.cpp
*********************************************************************/
