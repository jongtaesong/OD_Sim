/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Default
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/Default.h
*********************************************************************/

#ifndef Default_H
#define Default_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]

//## auto_generated
#include <oxf/oxf.h>
//## auto_generated
#include <string>
//## auto_generated
#include <algorithm>
//## auto_generated
class AppStats;

//## auto_generated
class Application;

//## auto_generated
class ConnMap;

//## auto_generated
class Device;

//## auto_generated
class FlexODSim;

//## auto_generated
class ODNetConfig;

//## auto_generated
class ODSim;

//## auto_generated
class ODSimElement;

//## auto_generated
class Packet;

//## auto_generated
class PacketQueue;

//## auto_generated
class PriorityPacketQueue;

//## auto_generated
class PriorityVOQueue;

//## auto_generated
class Serializer;

//## auto_generated
class SwitchCxl;

//## auto_generated
class SwitchOptics;

//## auto_generated
class VOQueue;

//## package Default


//#[ type Tick
typedef unsigned long Tick
;
//#]

//## type ePacketType
enum ePacketType {
    ReadReq = 0,
    ReadResp = 1,
    WriteReq = 2,
    WriteResp = 3,
    NullPacketType = 4,
    LoadControl = 5,
    NumPacketType = 6
};

//#[ type tClock
typedef unsigned long Tick
;
//#]

//## type SimParam_struct
struct SimParam_struct {
    int th_high;		//## attribute th_high
    int th_low;		//## attribute th_low
    int th_mid;		//## attribute th_mid
    int delta_severe;		//## attribute delta_severe
    int delta_normal;		//## attribute delta_normal
    int window_size;		//## attribute window_size
    // Flit size in Byte
    int flit_size;		//## attribute flit_size
    int reqs_per_flit;		//## attribute reqs_per_flit
    int clocks_per_usec;		//## attribute clocks_per_usec
    int link_delay;		//## attribute link_delay
    int num_priority;		//## attribute num_priority
    int num_app;		//## attribute num_app
    int num_device;		//## attribute num_device
    int num_switch_cxl;		//## attribute num_switch_cxl
    int num_switch_optics;		//## attribute num_switch_optics
    int max_num_pkt_serialize;		//## attribute max_num_pkt_serialize
    int link_bw_mbps;		//## attribute link_bw_mbps
    int load_update_interval;		//## attribute load_update_interval
    int mem_bw_mbps;		//## attribute mem_bw_mbps
    int file_size;		//## attribute file_size
    int load;		//## attribute load
    int max_sim_clock;		//## attribute max_sim_clock
    int mem_clock_per_req;		//## attribute mem_clock_per_req
    int mem_clock_per_flit;		//## attribute mem_clock_per_flit
    int link_clock_per_flit;		//## attribute link_clock_per_flit
    int link_clock_per_req;		//## attribute link_clock_per_req
    int load_update_queue;		//## attribute load_update_queue
    int resp_link_check;		//## attribute resp_link_check
};

//## attribute DEBUG
extern int DEBUG;

//## attribute IsFlowControlled_
extern int IsFlowControlled_;

//## attribute IsThrottled
extern int IsThrottled;

//## attribute RespLinkCheck__
extern int RespLinkCheck__;

//## attribute RttDelayMax
static const int RttDelayMax(10000);

//## attribute StrictPriority
extern int StrictPriority;

//## attribute delay_statistics
extern int delay_statistics[1000];

//## attribute sim_result
extern FILE * sim_result;

//## attribute sim_result2
extern FILE * sim_result2;

//## attribute sim_result3
extern FILE * sim_result3;

//## operation debug(char*,char*,int,char*,int,char*)
void debug(char* name, char* st1, int n1, char* st2, int n2, char* fn);

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/Default.h
*********************************************************************/
