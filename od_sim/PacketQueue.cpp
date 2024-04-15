/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: PacketQueue
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/PacketQueue.cpp
*********************************************************************/

//## auto_generated
#include <iostream>
//## auto_generated
#include "PacketQueue.h"
//## package Default

//## class PacketQueue
Packet* PacketQueue::remove_front_packet() {
    //#[ operation remove_front_packet()
    if (packet_list.size() == 0)
    {
    	printf("SW ERROR cannot removed from empty queue \n");
    	return 0;
    }
    Packet * p_pkt = packet_list.front();
    if (p_pkt == 0)
    {
    	printf("SW ERROR in pop_completed_packet \n");
    	return 0;
    }
    
    packet_list.pop_front();
    return p_pkt;
    
    //#]
}

void PacketQueue::add_packet(Packet* p_pkt) {
    //#[ operation add_packet(Packet)
    
    packet_list.push_back(p_pkt);     
                                      
                                        
    
    
    //#]
}

void PacketQueue::print_all_packets() {
    //#[ operation print_all_packets()
    
    if (packet_list.size()>0)
    {
    	printf("all packets in %s \n", name);
    	std::list<Packet*>::iterator p_pkt;
    	for (p_pkt = packet_list.begin(); p_pkt != packet_list.end(); ++p_pkt)
    		(*p_pkt)->print_info();
    }  
    
    //#]
}

void PacketQueue::print_info() {
    //#[ operation print_info()
    printf("name:%s, num_pkts:%d \n", name, (int) packet_list.size());
    //#]
}

void PacketQueue::reinit(char* name_) {
    //#[ operation reinit(char*)
    
    
    sprintf(name, "%s",name_);   
    while (packet_list.size()>0)
    {
    	Packet * p_pkt = packet_list.front();  
    	packet_list.pop_front();
    	//printf("%s: remove packet \n", name);
    	//p_pkt->print_info();
    	
    	delete p_pkt;
    } 
    packet_list.clear();
    
    //#]
}

void PacketQueue::remove_all_packets() {
    //#[ operation remove_all_packets()
    
    
    while (packet_list.size()>0)
    {
    	Packet * p_pkt = packet_list.front();  
    	packet_list.pop_front();
    	//printf("%s: remove packet \n", name);
    	//p_pkt->print_info();
    	
    	delete p_pkt;
    } 
    
    packet_list.clear();     
    
    //#]
}

PacketQueue::PacketQueue() {
}

PacketQueue::~PacketQueue() {
    cleanUpRelations();
}

Packet* PacketQueue::get_front_packet() {
    //#[ operation get_front_packet()
    if (packet_list.size() == 0)
    {
    	printf("SW ERROR cannot removed from empty queue \n");
    	return 0;
    }
    Packet * p_pkt = packet_list.front();
    if (p_pkt == 0)
    {
    	printf("SW ERROR in pop_completed_packet \n");
    	return 0;
    }
    
    return p_pkt;
    
    //#]
}

int PacketQueue::get_queue_size() {
    //#[ operation get_queue_size()
    
    return packet_list.size();     
                                      
                                        
    
    
    //#]
}

void PacketQueue::reinit() {
    //#[ operation reinit()
    
    
    
    while (packet_list.size()>0)
    {
    	Packet * p_pkt = packet_list.front();  
    	packet_list.pop_front();
    	//printf("%s: remove packet \n", name);
    	//p_pkt->print_info();
    	
    	delete p_pkt;
    } 
    packet_list.clear();
    
    //#]
}

std::list<Packet*>::const_iterator PacketQueue::getPacket_list() const {
    std::list<Packet*>::const_iterator iter;
    iter = packet_list.begin();
    return iter;
}

std::list<Packet*>::const_iterator PacketQueue::getPacket_listEnd() const {
    return packet_list.end();
}

void PacketQueue::addPacket_list(Packet* p_Packet) {
    packet_list.push_back(p_Packet);
}

void PacketQueue::removePacket_list(Packet* p_Packet) {
    std::list<Packet*>::iterator pos = std::find(packet_list.begin(), packet_list.end(),p_Packet);
    if (pos != packet_list.end()) {
    	packet_list.erase(pos);
    }
}

void PacketQueue::clearPacket_list() {
    packet_list.clear();
}

void PacketQueue::cleanUpRelations() {
    {
        packet_list.clear();
    }
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/PacketQueue.cpp
*********************************************************************/
