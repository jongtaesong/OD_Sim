/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Serializer
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/Serializer.cpp
*********************************************************************/

//## auto_generated
#include "Serializer.h"
//## auto_generated
#include <iostream>
//## package Default

//## class Serializer
Serializer::Serializer() : num_packet(0), prop_delay(100) {
}

Serializer::~Serializer() {
    cleanUpRelations();
}

Packet* Serializer::pop_completed_packet(int clk) {
    //#[ operation pop_completed_packet(int)
    if (packet_list.size() == 0)
    {
    	return 0;
    }
    Packet * p_pkt = packet_list.front();
    if (p_pkt == 0)
    {
    	printf("SW ERROR in pop_completed_packet \n");
    	return 0;
    }
    
    if (p_pkt->getTime_sending_complete() > clk)
    {
    	return 0;
    }
    
    packet_list.pop_front();  
    num_packet--;
    return p_pkt;
    
    //#]
}

void Serializer::serialize_packet(Packet* p_pkt, int clk) {
    //#[ operation serialize_packet(Packet,int)
    
    if (bw_mbps == 0 || clocks_per_usec == 0)
    {
    	printf("!!!!!! SW ERROR bw_mbps:%d or clocks_per_usec:%d ... not initialzied\n", bw_mbps, clocks_per_usec);	    
    	print_info();
    }
    
    
    if (latest_completion_time < clk)
    	latest_completion_time = clk;
    int t_send = latest_completion_time + p_pkt->getSize()*8*clocks_per_usec/bw_mbps+1;     
    latest_completion_time = t_send;
    
    p_pkt->setTime_sending_complete(t_send+prop_delay);
    
    packet_list.push_back(p_pkt);  
    //printf("Push back serializer at clk:%d \n", clk);	
    //print_all_packets();    
    num_packet++;
       
    
    //if (packet_list.size()> 2*WindowSize && IsFlowControlled)
    if (packet_list.size()> 200)
    {
    	//printf("!!!!!! SW ERROR serializer overflow in %s num_packet:%d clk:%d \n", name, (int) packet_list.size(),clk);	
    	//print_all_packets();    
    }    
                                        
                                        
    
    
    //#]
}

int Serializer::getLatest_completion_time() const {
    return latest_completion_time;
}

void Serializer::setLatest_completion_time(int p_latest_completion_time) {
    latest_completion_time = p_latest_completion_time;
}

bool Serializer::is_overflowed() {
    //#[ operation is_overflowed()
    
    if (packet_list.size()>10)
    {
    	return true;
    }
    else
    {
    	return false;
    }
    //#]
}

void Serializer::print_all_packets() {
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

void Serializer::print_info() {
    //#[ operation print_info()
    printf("name:%s, bw_mbps:%d, last_comp_time:%d, num_pkts:%d, clk_per_us:%d \n", 
    		name, bw_mbps, latest_completion_time, (int) packet_list.size(), clocks_per_usec);      
    print_all_packets();
    //#]
}

void Serializer::reinit(int bw, int lk_delay, char* name_) {
    //#[ operation reinit(int,int,char*)
    bw_mbps = bw;   
    prop_delay = lk_delay; 
    latest_completion_time = 0;  
    num_packet = 0;
    sprintf(name, "%s",name_);  
    
    if (packet_list.size()>0)
    {
    	std::list<Packet*>::iterator p_pkt;
    	for (p_pkt = packet_list.begin(); p_pkt != packet_list.end(); ++p_pkt)
    	{	
    		//(*p_pkt)->print_info();
    		delete (*p_pkt);
    	}
    }
    
    
    /*while (packet_list.size()>0)
    {
    	Packet * p_pkt = packet_list.front();  
    	packet_list.pop_front();
    	printf("%s: remove packet size:%d \n", name, packet_list.size());
    	p_pkt->print_info(); 
    	
    	delete p_pkt;
    }
    */ 
    packet_list.clear();    
    
    if(DEBUG) printf("%s initialized bw_gbps:%d\n", name, bw);
    //#]
}

void Serializer::remove_all_packets() {
    //#[ operation remove_all_packets()
     
    latest_completion_time = 0;
    packet_list.clear();
    
    //#]
}

char Serializer::getName(int i1) const {
    return name[i1];
}

void Serializer::setName(int i1, char p_name) {
    name[i1] = p_name;
}

Serializer::Serializer(int bw, int pr_delay, char* name_, int c_us) : num_packet(0), prop_delay(100) {
    //#[ operation Serializer(int,int,char*,int)
    bw_mbps = bw;      
    strcpy(name, name_);   
    packet_list.clear();    
    latest_completion_time = 0;   
    prop_delay = pr_delay;  
    clocks_per_usec =c_us;
    
    if(c_us == 0)
    {
    	printf("%s: SW ERROR clocks_per_usec %d\n", name, c_us); 
    }                    
    if(DEBUG) printf("%s initialized bw_mbps:%d pr_delay:%d clocks_per_usec:%d\n", name, bw_mbps, prop_delay, clocks_per_usec);                                   
    //#]
}

Packet* Serializer::get_front() {
    //#[ operation get_front()
    if (num_packet == 0) 
    return NULL;
    std::list<Packet*>::iterator p_pkt;
    p_pkt = packet_list.begin();
    return (*p_pkt);
    //#]
}

int Serializer::getBw_mbps() const {
    return bw_mbps;
}

void Serializer::setBw_mbps(int p_bw_mbps) {
    bw_mbps = p_bw_mbps;
}

int Serializer::getClocks_per_usec() const {
    return clocks_per_usec;
}

void Serializer::setClocks_per_usec(int p_clocks_per_usec) {
    clocks_per_usec = p_clocks_per_usec;
}

int Serializer::getNum_packet() const {
    return num_packet;
}

void Serializer::setNum_packet(int p_num_packet) {
    num_packet = p_num_packet;
}

int Serializer::getProp_delay() const {
    return prop_delay;
}

void Serializer::setProp_delay(int p_prop_delay) {
    prop_delay = p_prop_delay;
}

std::list<Packet*>::const_iterator Serializer::getPacket_list() const {
    std::list<Packet*>::const_iterator iter;
    iter = packet_list.begin();
    return iter;
}

std::list<Packet*>::const_iterator Serializer::getPacket_listEnd() const {
    return packet_list.end();
}

void Serializer::addPacket_list(Packet* p_Packet) {
    packet_list.push_back(p_Packet);
}

void Serializer::removePacket_list(Packet* p_Packet) {
    std::list<Packet*>::iterator pos = std::find(packet_list.begin(), packet_list.end(),p_Packet);
    if (pos != packet_list.end()) {
    	packet_list.erase(pos);
    }
}

void Serializer::clearPacket_list() {
    packet_list.clear();
}

void Serializer::cleanUpRelations() {
    {
        packet_list.clear();
    }
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/Serializer.cpp
*********************************************************************/
