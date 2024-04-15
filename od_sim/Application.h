/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Application
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/Application.h
*********************************************************************/

#ifndef Application_H
#define Application_H

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
#include <iterator>
//## link itsDevice
#include "Device.h"
//## auto_generated
#include <map>
//## auto_generated
#include <oxf/OMValueCompare.h>
//## link itsConnMap
#include "ConnMap.h"
//## class Application
#include "ODSimElement.h"
//## link itsSwitchCxl
#include "SwitchCxl.h"
//## link itsSwitchOptics
#include "SwitchOptics.h"
//## auto_generated
#include "Default.h"
//## link sim_stats
class AppStats;

//## operation find_cxl_switch(Packet)
class Packet;

//## link packet_queue
class PacketQueue;

//## link packet_serializer
class Serializer;

//## package Default

//## class Application
class Application : public ODSimElement {
    ////    Constructors and destructors    ////
    
public :

    //## operation Application(int,int,int,int,int,int,int,int,int,int,int,int)
    Application(int app_id_, int flt_size, int clk_per_us, int throttle_threshold_high, int throttle_threshold_mid, int throttle_threshold_low, int delta_severe, int delta_normal, int bw, int reqs_flit_, int wd_size, int lk_delay);
    
    ////    Additional operations    ////
    
    ////    Attributes    ////
    
    ////    Framework operations    ////
    
    ////    Framework    ////
    
    //## auto_generated
    Application();
    
    //## operation ~Application()
    virtual ~Application();
    
    //## operation generate_packet()
    void generate_packet();
    
    //## operation print_packets()
    void print_packets();
    
    //## operation process_clock(int)
    void process_clock(int clk);
    
    //## operation process_packet(int)
    void process_packet(int t_clk);
    
    //## operation receive_response(Packet,int)
    void receive_response(Packet* p_pkt, int clk);
    
    //## operation reinit_(int,int,int,int)
    void reinit_(int ld, int file_size_, int lk_delay, int w_size);
    
    //## operation schedule_packet(Packet)
    void schedule_packet(Packet*& p_pkt);
    
    //## operation update_throttle(Packet)
    void update_throttle(Packet* p_pkt);
    
    //## operation update_time_clock(int)
    void update_time_clock(int clock);
    
    //## auto_generated
    int getNum_pending_resp() const;
    
    //## auto_generated
    void setNum_pending_resp(int p_num_pending_resp);
    
    //## auto_generated
    int getPriority() const;
    
    //## auto_generated
    void setPriority(int p_priority);
    
    //## auto_generated
    int getThrottle_delta(int i1) const;
    
    //## auto_generated
    void setThrottle_delta(int i1, int p_throttle_delta);
    
    //## auto_generated
    int getThrottle_per_priority(int i1) const;
    
    //## auto_generated
    void setThrottle_per_priority(int i1, int p_throttle_per_priority);
    
    //## auto_generated
    int getTime_clock() const;
    
    //## auto_generated
    void setTime_clock(int p_time_clock);

protected :

    //## auto_generated
    void cleanUpRelations();
    
    int flit_clocks;		//## attribute flit_clocks
    
    int throttle_load_threshold[3];		//## attribute throttle_load_threshold
    
    int num_pending_resp;		//## attribute num_pending_resp
    
    int priority;		//## attribute priority
    
    int throttle_delta[3];		//## attribute throttle_delta
    
    int throttle_per_priority[3];		//## attribute throttle_per_priority
    
    int time_clock;		//## attribute time_clock

public :

    //## operation print_info()
    void print_info();
    
    //## auto_generated
    int getFlit_clocks() const;
    
    //## auto_generated
    void setFlit_clocks(int p_flit_clocks);
    
    //## auto_generated
    int getThrottle_load_threshold(int i1) const;
    
    //## auto_generated
    void setThrottle_load_threshold(int i1, int p_throttle_load_threshold);
    
    //## operation Application(int,SimParam_struct)
    Application(int idx, const SimParam_struct& s_p);
    
    //## operation createSerializer()
    void createSerializer();
    
    //## operation find_cxl_switch(Packet)
    SwitchCxl* find_cxl_switch(Packet * p_pkt);
    
    //## operation get_file_completion_time()
    int get_file_completion_time();
    
    //## operation initialize(int,int,int,int,int,int,int,int,int,int,int)
    void initialize(int f_size, int clk_per_us, int th_h, int th_m, int th_l, int d_sv, int d_norm, int bw, int req_flit, int w_size, int lk_delay);
    
    //## operation print_rtt_to_file(FILE *)
    void print_rtt_to_file(FILE * p_file);
    
    //## operation process_serializer_packet(int)
    void process_serializer_packet(int t_clk);
    
    //## operation reinit(SimParam_struct)
    void reinit(const SimParam_struct& s_pr);
    
    //## operation reset_stats()
    void reset_stats();
    
    //## operation set_connected_dev_index(int)
    void set_connected_dev_index(int dev_idx);
    
    //## operation write_file_completion_time(int,int,int)
    void write_file_completion_time(int return_ck, int cnt_q, int ser_q);
    
    //## operation write_stats_and_reset(int,int,int)
    void write_stats_and_reset(int app_id, int prio, int clk);
    
    //## auto_generated
    int getConnected_dev_index() const;
    
    //## auto_generated
    void setConnected_dev_index(int p_connected_dev_index);
    
    //## auto_generated
    int getNum_connected_dev() const;
    
    //## auto_generated
    void setNum_connected_dev(int p_num_connected_dev);
    
    //## auto_generated
    SimParam_struct getSim_param() const;
    
    //## auto_generated
    void setSim_param(SimParam_struct p_sim_param);
    
    //## auto_generated
    std::map<int, ConnMap*>::const_iterator getItsConnMap() const;
    
    //## auto_generated
    std::map<int, ConnMap*>::const_iterator getItsConnMapEnd() const;
    
    //## auto_generated
    void clearItsConnMap();
    
    //## auto_generated
    void removeItsConnMap(ConnMap* p_ConnMap);
    
    //## auto_generated
    ConnMap* getItsConnMap(int key) const;
    
    //## auto_generated
    void addItsConnMap(int key, ConnMap* p_ConnMap);
    
    //## auto_generated
    void removeItsConnMap(int key);
    
    //## auto_generated
    std::map<int, Device*>::const_iterator getItsDevice() const;
    
    //## auto_generated
    std::map<int, Device*>::const_iterator getItsDeviceEnd() const;
    
    //## auto_generated
    void clearItsDevice();
    
    //## auto_generated
    void removeItsDevice(Device* p_Device);
    
    //## auto_generated
    Device* getItsDevice(int key) const;
    
    //## auto_generated
    void addItsDevice(int key, Device* p_Device);
    
    //## auto_generated
    void removeItsDevice(int key);
    
    //## auto_generated
    std::map<int, SwitchCxl*>::const_iterator getItsSwitchCxl() const;
    
    //## auto_generated
    std::map<int, SwitchCxl*>::const_iterator getItsSwitchCxlEnd() const;
    
    //## auto_generated
    void clearItsSwitchCxl();
    
    //## auto_generated
    void removeItsSwitchCxl(SwitchCxl* p_SwitchCxl);
    
    //## auto_generated
    SwitchCxl* getItsSwitchCxl(int key) const;
    
    //## auto_generated
    void addItsSwitchCxl(int key, SwitchCxl* p_SwitchCxl);
    
    //## auto_generated
    void removeItsSwitchCxl(int key);
    
    //## auto_generated
    std::map<int, SwitchOptics*>::const_iterator getItsSwitchOptics() const;
    
    //## auto_generated
    std::map<int, SwitchOptics*>::const_iterator getItsSwitchOpticsEnd() const;
    
    //## auto_generated
    void clearItsSwitchOptics();
    
    //## auto_generated
    void removeItsSwitchOptics(SwitchOptics* p_SwitchOptics);
    
    //## auto_generated
    SwitchOptics* getItsSwitchOptics(int key) const;
    
    //## auto_generated
    void addItsSwitchOptics(int key, SwitchOptics* p_SwitchOptics);
    
    //## auto_generated
    void removeItsSwitchOptics(int key);
    
    //## auto_generated
    PacketQueue* getPacket_queue() const;
    
    //## auto_generated
    void setPacket_queue(PacketQueue* p_PacketQueue);
    
    //## auto_generated
    Serializer* getPacket_serializer() const;
    
    //## auto_generated
    void setPacket_serializer(Serializer* p_Serializer);
    
    //## auto_generated
    AppStats* getSim_stats() const;
    
    //## auto_generated
    void setSim_stats(AppStats* p_AppStats);

protected :

    int connected_dev_index;		//## attribute connected_dev_index
    
    int num_connected_dev;		//## attribute num_connected_dev
    
    SimParam_struct sim_param;		//## attribute sim_param
    
    std::map<int, ConnMap*> itsConnMap;		//## link itsConnMap
    
    std::map<int, Device*> itsDevice;		//## link itsDevice
    
    std::map<int, SwitchCxl*> itsSwitchCxl;		//## link itsSwitchCxl
    
    std::map<int, SwitchOptics*> itsSwitchOptics;		//## link itsSwitchOptics
    
    PacketQueue* packet_queue;		//## link packet_queue
    
    Serializer* packet_serializer;		//## link packet_serializer
    
    AppStats* sim_stats;		//## link sim_stats
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/Application.h
*********************************************************************/
