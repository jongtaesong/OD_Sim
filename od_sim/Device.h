/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Device
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/Device.h
*********************************************************************/

#ifndef Device_H
#define Device_H

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
#include <map>
//## auto_generated
#include <iterator>
//## auto_generated
#include <oxf/OMValueCompare.h>
//## link itsApplication
#include "Application.h"
//## link itsConnMap
#include "ConnMap.h"
//## class Device
#include "ODSimElement.h"
//## link itsSwitchCxl
#include "SwitchCxl.h"
//## link itsSwitchOptics
#include "SwitchOptics.h"
//## auto_generated
#include "Default.h"
//## operation find_cxl_switch(Packet)
class Packet;

//## link rx_priority_queue
class PriorityPacketQueue;

//## link itsPriorityVOQueue
class PriorityVOQueue;

//## attribute switch_serializer
class Serializer;

//## package Default

//## class Device
class Device : public ODSimElement {
    ////    Constructors and destructors    ////
    
public :

    //## operation Device(char*,int,int,int,int,int,int)
    Device(char* name_, int t, int link_bw_gbps_, int mem_bw_gbps_, int flit_size_, int pr_delay, int n_app);
    
    //## auto_generated
    Device();
    
    //## auto_generated
    ~Device();
    
    ////    Operations    ////
    
    //## operation process_clock_multi_links(int)
    void process_clock_multi_links(int clk);
    
    //## operation memory_access_clk(int,int)
    int memory_access_clk(int size_, int speed_);
    
    //## operation receive_packet(Packet,int)
    void receive_packet(Packet* p_pkt, int clk);
    
    //## operation reinit_(int,int,int)
    void reinit_(int l_bw, int m_bw, int n_ser);
    
    //## operation send_response(Packet,int)
    void send_response(Packet* p_pkt, int clk);
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getPacket_serializer() const;
    
    //## auto_generated
    Serializer* getPacket_serializer_internal() const;
    
    //## auto_generated
    PriorityPacketQueue* getRx_priority_queue() const;
    
    //## auto_generated
    PriorityPacketQueue* getTx_priority_queue() const;
    
    //## auto_generated
    std::map<int, Application*>::const_iterator getItsApplication() const;
    
    //## auto_generated
    std::map<int, Application*>::const_iterator getItsApplicationEnd() const;
    
    //## auto_generated
    void clearItsApplication();
    
    //## auto_generated
    void removeItsApplication(Application* p_Application);
    
    //## auto_generated
    Application* getItsApplication(int key) const;
    
    //## auto_generated
    void addItsApplication(int key, Application* p_Application);
    
    //## auto_generated
    void removeItsApplication(int key);

protected :

    //## auto_generated
    void cleanUpRelations();
    
    ////    Attributes    ////
    
    int interval_update_load_;		//## attribute interval_update_load_
    
    int link_bw_gbps_;		//## attribute link_bw_gbps_
    
    int mem_bw_gbps_;		//## attribute mem_bw_gbps_
    
    ////    Relations and components    ////
    
    std::map<int, Application*> itsApplication;		//## link itsApplication

public :

    //## operation Device(char*,int,SimParam_struct)
    Device(char* name_, int idx_, const SimParam_struct& s_p);
    
    //## operation find_cxl_switch(Packet)
    SwitchCxl* find_cxl_switch(Packet * p_pkt);
    
    //## operation generate_load_update_packet()
    Packet* generate_load_update_packet();
    
    //## operation init_conn_interface()
    void init_conn_interface();
    
    //## operation print_app_to_port_table()
    void print_app_to_port_table();
    
    //## operation print_dest_port_to_voq()
    void print_dest_port_to_voq();
    
    //## operation print_info()
    void print_info();
    
    //## operation print_info_simple()
    void print_info_simple();
    
    //## operation print_sim_param(SimParam_struct)
    static void print_sim_param(const SimParam_struct& s_);
    
    //## operation print_voq_to_dest_port()
    void print_voq_to_dest_port();
    
    //## operation process_clock(int)
    void process_clock(int clk);
    
    //## operation process_clock_flex(int)
    void process_clock_flex(int clk);
    
    //## operation process_clock_single_link(int)
    void process_clock_single_link(int clk);
    
    //## operation receive_packet_flex(Packet,int)
    void receive_packet_flex(Packet* p_pkt, int clk);
    
    //## operation receive_packet_multi_link(Packet,int)
    void receive_packet_multi_link(Packet* p_pkt, int clk);
    
    //## operation receive_packet_single_link(Packet,int)
    void receive_packet_single_link(Packet* p_pkt, int clk);
    
    //## operation reinit(SimParam_struct)
    void reinit(const SimParam_struct& s_p);
    
    //## operation reset_load_count()
    void reset_load_count();
    
    //## operation update_load_count()
    void update_load_count();
    
    //## auto_generated
    int getApp_idx_to_dest_port(int i1) const;
    
    //## auto_generated
    void setApp_idx_to_dest_port(int i1, int p_app_idx_to_dest_port);
    
    //## auto_generated
    int getDest_port_to_voq(int i1) const;
    
    //## auto_generated
    void setDest_port_to_voq(int i1, int p_dest_port_to_voq);
    
    //## auto_generated
    int getFlit_size_() const;
    
    //## auto_generated
    void setFlit_size_(int p_flit_size_);
    
    //## auto_generated
    int getInterval_update_load_() const;
    
    //## auto_generated
    void setInterval_update_load_(int p_interval_update_load_);
    
    //## auto_generated
    int getLink_bw_gbps_() const;
    
    //## auto_generated
    void setLink_bw_gbps_(int p_link_bw_gbps_);
    
    //## auto_generated
    int getLink_prop_delay_() const;
    
    //## auto_generated
    void setLink_prop_delay_(int p_link_prop_delay_);
    
    //## auto_generated
    int getLoad_count_priority(int i1) const;
    
    //## auto_generated
    void setLoad_count_priority(int i1, int p_load_count_priority);
    
    //## auto_generated
    int getLoad_count_total() const;
    
    //## auto_generated
    void setLoad_count_total(int p_load_count_total);
    
    //## auto_generated
    int getMax_num_pkt_in_serializer_() const;
    
    //## auto_generated
    void setMax_num_pkt_in_serializer_(int p_max_num_pkt_in_serializer_);
    
    //## auto_generated
    int getMem_bw_gbps_() const;
    
    //## auto_generated
    void setMem_bw_gbps_(int p_mem_bw_gbps_);
    
    //## auto_generated
    int getNum_connected_app() const;
    
    //## auto_generated
    void setNum_connected_app(int p_num_connected_app);
    
    //## auto_generated
    int getNum_dest_port() const;
    
    //## auto_generated
    void setNum_dest_port(int p_num_dest_port);
    
    //## auto_generated
    int getPending_packets_priority(int i1) const;
    
    //## auto_generated
    void setPending_packets_priority(int i1, int p_pending_packets_priority);
    
    //## auto_generated
    SimParam_struct getSim_param() const;
    
    //## auto_generated
    void setSim_param(SimParam_struct p_sim_param);
    
    //## auto_generated
    Serializer* getSwitch_serializer() const;
    
    //## auto_generated
    void setSwitch_serializer(Serializer* p_switch_serializer);
    
    //## auto_generated
    int getVoq_to_dest_port(int i1) const;
    
    //## auto_generated
    void setVoq_to_dest_port(int i1, int p_voq_to_dest_port);
    
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
    PriorityVOQueue* getItsPriorityVOQueue() const;
    
    //## auto_generated
    void setItsPriorityVOQueue(PriorityVOQueue* p_PriorityVOQueue);
    
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
    void addPacket_serializer(Serializer* p_Serializer);
    
    //## auto_generated
    void removePacket_serializer(Serializer* p_Serializer);
    
    //## auto_generated
    void clearPacket_serializer();
    
    //## auto_generated
    void setPacket_serializer_internal(Serializer* p_Serializer);
    
    //## auto_generated
    void setRx_priority_queue(PriorityPacketQueue* p_PriorityPacketQueue);
    
    //## auto_generated
    void setTx_priority_queue(PriorityPacketQueue* p_PriorityPacketQueue);

protected :

    int app_idx_to_dest_port[32];		//## attribute app_idx_to_dest_port
    
    int dest_port_to_voq[32];		//## attribute dest_port_to_voq
    
    int flit_size_;		//## attribute flit_size_
    
    int link_prop_delay_;		//## attribute link_prop_delay_
    
    int load_count_priority[3];		//## attribute load_count_priority
    
    int load_count_total;		//## attribute load_count_total
    
    int max_num_pkt_in_serializer_;		//## attribute max_num_pkt_in_serializer_
    
    int num_connected_app;		//## attribute num_connected_app
    
    int num_dest_port;		//## attribute num_dest_port
    
    int pending_packets_priority[3];		//## attribute pending_packets_priority
    
    SimParam_struct sim_param;		//## attribute sim_param
    
    Serializer* switch_serializer;		//## attribute switch_serializer
    
    int voq_to_dest_port[32];		//## attribute voq_to_dest_port
    
    std::map<int, ConnMap*> itsConnMap;		//## link itsConnMap
    
    PriorityVOQueue* itsPriorityVOQueue;		//## link itsPriorityVOQueue
    
    std::map<int, SwitchCxl*> itsSwitchCxl;		//## link itsSwitchCxl
    
    std::map<int, SwitchOptics*> itsSwitchOptics;		//## link itsSwitchOptics
    
    Serializer* packet_serializer[32];		//## link packet_serializer
    
    Serializer* packet_serializer_internal;		//## link packet_serializer_internal
    
    PriorityPacketQueue* rx_priority_queue;		//## link rx_priority_queue
    
    PriorityPacketQueue* tx_priority_queue;		//## link tx_priority_queue
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/Device.h
*********************************************************************/
