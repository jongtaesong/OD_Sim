/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: PriorityPacketQueue
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/PriorityPacketQueue.h
*********************************************************************/

#ifndef PriorityPacketQueue_H
#define PriorityPacketQueue_H

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
//## class PriorityPacketQueue
#include "ODSimElement.h"
//## auto_generated
#include "Default.h"
//## operation add_packet(int,Packet)
class Packet;

//## link priority_queue
class PacketQueue;

//## package Default

//## class PriorityPacketQueue
class PriorityPacketQueue : public ODSimElement {
    ////    Constructors and destructors    ////
    
public :

    //## operation PriorityPacketQueue()
    PriorityPacketQueue();
    
    //## auto_generated
    ~PriorityPacketQueue();
    
    ////    Operations    ////
    
    //## operation add_packet(int,Packet)
    void add_packet(int priority, Packet*& p_pkt);
    
    //## operation generate_load_update_packet(int)
    Packet* generate_load_update_packet(int size);
    
    //## operation get_front_packet(int)
    Packet* get_front_packet(int pri);
    
    //## operation get_num_packet_priority(int)
    int get_num_packet_priority(int pri);
    
    //## operation print_info()
    void print_info();
    
    //## operation random_memory_access_delay()
    int random_memory_access_delay();
    
    //## operation reinit()
    void reinit();
    
    //## operation remove_all_packet()
    void remove_all_packet();
    
    //## operation remove_packet()
    Packet* remove_packet();
    
    //## operation remove_packet(int)
    Packet* remove_packet(int pri);
    
    //## operation remove_packet_start_from(int)
    Packet* remove_packet_start_from(int p);
    
    //## operation reset_load_count(int)
    void reset_load_count(int clk);
    
    //## operation update_load_stats(int)
    void update_load_stats(int clk);
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getBw_gbps() const;
    
    //## auto_generated
    void setBw_gbps(int p_bw_gbps);
    
    //## auto_generated
    int getInterval_update_load() const;
    
    //## auto_generated
    void setInterval_update_load(int p_interval_update_load);
    
    //## auto_generated
    int getLoad_counter(int i1) const;
    
    //## auto_generated
    void setLoad_counter(int i1, int p_load_counter);
    
    //## auto_generated
    int getLoad_counter_total() const;
    
    //## auto_generated
    void setLoad_counter_total(int p_load_counter_total);
    
    //## auto_generated
    int getLoad_updated() const;
    
    //## auto_generated
    void setLoad_updated(int p_load_updated);
    
    //## auto_generated
    int getNum_packet() const;
    
    //## auto_generated
    void setNum_packet(int p_num_packet);
    
    //## auto_generated
    int getPrev_load(int i1) const;
    
    //## auto_generated
    void setPrev_load(int i1, int p_prev_load);
    
    //## auto_generated
    int getUpdated_load(int i1) const;
    
    //## auto_generated
    void setUpdated_load(int i1, int p_updated_load);
    
    //## auto_generated
    int getPriority_queue() const;
    
    //## auto_generated
    void addPriority_queue(PacketQueue* p_PacketQueue);
    
    //## auto_generated
    void removePriority_queue(PacketQueue* p_PacketQueue);
    
    //## auto_generated
    void clearPriority_queue();

protected :

    //## auto_generated
    void cleanUpRelations();
    
    ////    Attributes    ////
    
    int bw_gbps;		//## attribute bw_gbps
    
    int interval_update_load;		//## attribute interval_update_load
    
    int load_counter[3];		//## attribute load_counter
    
    int load_counter_total;		//## attribute load_counter_total
    
    int load_updated;		//## attribute load_updated
    
    int num_packet;		//## attribute num_packet
    
    int prev_load[3];		//## attribute prev_load
    
    int updated_load[3];		//## attribute updated_load
    
    ////    Relations and components    ////
    
    PacketQueue* priority_queue[3];		//## link priority_queue
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/PriorityPacketQueue.h
*********************************************************************/
