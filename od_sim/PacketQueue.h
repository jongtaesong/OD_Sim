/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: PacketQueue
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/PacketQueue.h
*********************************************************************/

#ifndef PacketQueue_H
#define PacketQueue_H

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
//## class PacketQueue
#include "ODSimElement.h"
//## auto_generated
#include "Default.h"
//## package Default

//## class PacketQueue
class PacketQueue : public ODSimElement {
    ////    Constructors and destructors    ////
    
    ////    Operations    ////
    
public :

    //## operation remove_front_packet()
    Packet* remove_front_packet();
    
    //## operation add_packet(Packet)
    void add_packet(Packet* p_pkt);
    
    ////    Additional operations    ////
    
    ////    Attributes    ////
    
    //## operation print_all_packets()
    void print_all_packets();
    
    //## operation print_info()
    void print_info();
    
    //## operation reinit(char*)
    void reinit(char* name_);
    
    //## operation remove_all_packets()
    void remove_all_packets();
    
    //## auto_generated
    PacketQueue();
    
    //## auto_generated
    ~PacketQueue();
    
    //## operation get_front_packet()
    Packet* get_front_packet();
    
    //## operation get_queue_size()
    int get_queue_size();
    
    //## operation reinit()
    void reinit();
    
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
    
    std::list<Packet*> packet_list;		//## link packet_list
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/PacketQueue.h
*********************************************************************/
