/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: PriorityVOQueue
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/PriorityVOQueue.h
*********************************************************************/

#ifndef PriorityVOQueue_H
#define PriorityVOQueue_H

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
//## class PriorityVOQueue
#include "ODSimElement.h"
//## auto_generated
#include "Default.h"
//## operation add_packet(int,int,Packet)
class Packet;

//## link itsVOQueue
class VOQueue;

//## package Default

//## class PriorityVOQueue
class PriorityVOQueue : public ODSimElement {
    ////    Constructors and destructors    ////
    
public :

    //## operation PriorityVOQueue(char*,int)
    PriorityVOQueue(char* name_, int n_out);
    
    //## auto_generated
    PriorityVOQueue();
    
    //## auto_generated
    ~PriorityVOQueue();
    
    ////    Operations    ////
    
    //## operation add_packet(int,int,Packet)
    void add_packet(int priority, int out, Packet*& p_pkt);
    
    //## operation generate_load_update_packet(int)
    Packet* generate_load_update_packet(int size);
    
    //## operation get_front_packet(int,int)
    int get_front_packet(int pri, int output);
    
    //## operation get_num_packet(int,int)
    int get_num_packet(int pri, int output);
    
    //## operation get_num_packet_priority(int)
    int get_num_packet_priority(int pri);
    
    //## operation print_info()
    void print_info();
    
    //## operation print_info_simple()
    void print_info_simple();
    
    //## operation random_memory_access_delay()
    int random_memory_access_delay();
    
    //## operation reinit()
    void reinit();
    
    //## operation remove_all_packet()
    void remove_all_packet();
    
    //## operation remove_packet(int,int)
    Packet* remove_packet(int pri, int output);
    
    //## operation reset_load_count(int)
    void reset_load_count(int clk);
    
    //## operation update_load_count(int,int)
    void update_load_count(int clk, int l_q);
    
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
    int getNum_output() const;
    
    //## auto_generated
    void setNum_output(int p_num_output);
    
    //## auto_generated
    int getNum_packet() const;
    
    //## auto_generated
    void setNum_packet(int p_num_packet);
    
    //## auto_generated
    int getNum_packet_priority(int i1) const;
    
    //## auto_generated
    void setNum_packet_priority(int i1, int p_num_packet_priority);
    
    //## auto_generated
    int getPrev_load(int i1) const;
    
    //## auto_generated
    void setPrev_load(int i1, int p_prev_load);
    
    //## auto_generated
    int getRr_pointer(int i1) const;
    
    //## auto_generated
    void setRr_pointer(int i1, int p_rr_pointer);
    
    //## auto_generated
    int getUpdated_load(int i1) const;
    
    //## auto_generated
    void setUpdated_load(int i1, int p_updated_load);
    
    //## auto_generated
    int getItsVOQueue() const;
    
    //## auto_generated
    void addItsVOQueue(VOQueue* p_VOQueue);
    
    //## auto_generated
    void removeItsVOQueue(VOQueue* p_VOQueue);
    
    //## auto_generated
    void clearItsVOQueue();

protected :

    //## auto_generated
    void cleanUpRelations();
    
    ////    Attributes    ////
    
    int bw_gbps;		//## attribute bw_gbps
    
    int interval_update_load;		//## attribute interval_update_load
    
    int load_counter[3];		//## attribute load_counter
    
    int load_counter_total;		//## attribute load_counter_total
    
    int load_updated;		//## attribute load_updated
    
    int num_output;		//## attribute num_output
    
    int num_packet;		//## attribute num_packet
    
    int num_packet_priority[3];		//## attribute num_packet_priority
    
    int prev_load[3];		//## attribute prev_load
    
    int rr_pointer[3];		//## attribute rr_pointer
    
    int updated_load[3];		//## attribute updated_load
    
    ////    Relations and components    ////
    
    VOQueue* itsVOQueue[3];		//## link itsVOQueue
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/PriorityVOQueue.h
*********************************************************************/
