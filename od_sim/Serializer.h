/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Serializer
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/Serializer.h
*********************************************************************/

#ifndef Serializer_H
#define Serializer_H

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
#include <list>
//## auto_generated
#include <iterator>
//## link packet_list
#include "Packet.h"
//## auto_generated
#include "Default.h"
//## package Default

//## class Serializer
class Serializer {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    Serializer();
    
    //## auto_generated
    ~Serializer();
    
    ////    Operations    ////
    
    //## operation pop_completed_packet(int)
    Packet* pop_completed_packet(int clk);
    
    //## operation serialize_packet(Packet,int)
    void serialize_packet(Packet* p_pkt, int clk);
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getLatest_completion_time() const;
    
    //## auto_generated
    void setLatest_completion_time(int p_latest_completion_time);
    
    ////    Attributes    ////

protected :

    int bw_mbps;		//## attribute bw_mbps
    
    int latest_completion_time;		//## attribute latest_completion_time

public :

    //## operation is_overflowed()
    bool is_overflowed();
    
    //## operation print_all_packets()
    void print_all_packets();
    
    //## operation print_info()
    void print_info();
    
    //## operation reinit(int,int,char*)
    void reinit(int bw, int lk_delay, char* name_);
    
    //## operation remove_all_packets()
    void remove_all_packets();
    
    //## auto_generated
    char getName(int i1) const;
    
    //## auto_generated
    void setName(int i1, char p_name);

protected :

    char name[30];		//## attribute name

public :

    //## operation Serializer(int,int,char*,int)
    Serializer(int bw, int pr_delay, char* name_, int c_us);
    
    //## operation get_front()
    Packet* get_front();
    
    //## auto_generated
    int getBw_mbps() const;
    
    //## auto_generated
    void setBw_mbps(int p_bw_mbps);
    
    //## auto_generated
    int getClocks_per_usec() const;
    
    //## auto_generated
    void setClocks_per_usec(int p_clocks_per_usec);
    
    //## auto_generated
    int getNum_packet() const;
    
    //## auto_generated
    void setNum_packet(int p_num_packet);
    
    //## auto_generated
    int getProp_delay() const;
    
    //## auto_generated
    void setProp_delay(int p_prop_delay);
    
    //## auto_generated
    std::list<Packet*>::const_iterator getPacket_list() const;
    
    //## auto_generated
    std::list<Packet*>::const_iterator getPacket_listEnd() const;
    
    //## auto_generated
    void addPacket_list(Packet* p_Packet);
    
    //## auto_generated
    void removePacket_list(Packet* p_Packet);
    
    //## auto_generated
    void clearPacket_list();

protected :

    //## auto_generated
    void cleanUpRelations();
    
    int clocks_per_usec;		//## attribute clocks_per_usec
    
    int num_packet;		//## attribute num_packet
    
    int prop_delay;		//## attribute prop_delay
    
    std::list<Packet*> packet_list;		//## link packet_list
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/Serializer.h
*********************************************************************/
