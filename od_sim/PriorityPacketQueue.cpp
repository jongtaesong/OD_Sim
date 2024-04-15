/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: PriorityPacketQueue
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/PriorityPacketQueue.cpp
*********************************************************************/

//## auto_generated
#include "PriorityPacketQueue.h"
//## operation add_packet(int,Packet)
#include "Packet.h"
//## link priority_queue
#include "PacketQueue.h"
//## auto_generated
#include <iostream>
//## package Default

//## class PriorityPacketQueue
PriorityPacketQueue::PriorityPacketQueue() : bw_gbps(100), num_packet(0) {
    {
        for (int pos = 0; pos < 3; pos++) {
        	priority_queue[pos] = NULL;
        }
    }
    //#[ operation PriorityPacketQueue()
    
    char n[20];
    
    for (int i=0; i<3; i++)
    {
    	priority_queue[i] = new PacketQueue;
    	sprintf(n,"priority_%d", i);
    	priority_queue[i]->set_name_string(n);
    }
    //#]
}

PriorityPacketQueue::~PriorityPacketQueue() {
    cleanUpRelations();
}

void PriorityPacketQueue::add_packet(int priority, Packet*& p_pkt) {
    //#[ operation add_packet(int,Packet)
    
    // if the priority queue is empty     
    num_packet++; 
    priority_queue[p_pkt->getPriority()]->add_packet(p_pkt);
       
    
    //#]
}

Packet* PriorityPacketQueue::generate_load_update_packet(int size) {
    //#[ operation generate_load_update_packet(int)
    
    Packet * p_pkt = new Packet;
    
    p_pkt->setLoad_updated(1);
    for (int i=0; i<3; i++)
    {
    	p_pkt->setUpdated_load(i, updated_load[i]);
    }
    
    p_pkt->setType(LoadControl);
    p_pkt->setSize(size);
    return p_pkt;
    
    //#]
}

Packet* PriorityPacketQueue::get_front_packet(int pri) {
    //#[ operation get_front_packet(int)
    //if (num_packet_priority[pri] == 0)   
    if (priority_queue[pri]->get_queue_size() == 0)   
    {
    	return 0;
    }	              
    
    Packet * p_pkt;
    p_pkt = priority_queue[pri]->get_front_packet(); 
    
    if (p_pkt == 0)
    {
    	printf(" SW ERROR Null pointer head priority:%d ============================ \n", pri );
        print_info();
    }
    
    return p_pkt;	
    //#]
}

int PriorityPacketQueue::get_num_packet_priority(int pri) {
    //#[ operation get_num_packet_priority(int)
    return priority_queue[pri]->get_queue_size();
    //#]
}

void PriorityPacketQueue::print_info() {
    //#[ operation print_info()
    printf("\n============================== \n %s Total Packets:%d \n", name, num_packet);
    
    Packet * p_pkt;
    for (int i=0; i<3; i++)
    {
    	printf("priority Queue %d has %d packets\n", i, priority_queue[i]->get_queue_size());      
        priority_queue[i]->print_all_packets();
    }    
    
    int sum = 0;
    for (int i=0; i<3; i++)
    {
    	sum+=priority_queue[i]->get_queue_size();
    }
    if (num_packet != sum)
    	printf("SW ERROR Packet Counter mismatch num:%d sum:%d\n", num_packet, sum);      
    
    printf("Load Count ");      
    for (int i=0; i<3; i++)
    	printf(" %d ", load_counter[i]);       
    printf(" total %d ", load_counter_total);      
    printf("\n");      
    
    printf(" ============================== \n \n ");
    //#]
}

int PriorityPacketQueue::random_memory_access_delay() {
    //#[ operation random_memory_access_delay()
    return rand()%3;    
    
    //#]
}

void PriorityPacketQueue::reinit() {
    //#[ operation reinit()
    
    if(DEBUG) printf("Priroty Packet Queue %s ... remove all packets ... \n", name);
    remove_all_packet();
    
    for (int i=0; i<3; i++)
    	priority_queue[i]->remove_all_packets();
    	
    //#]
}

void PriorityPacketQueue::remove_all_packet() {
    //#[ operation remove_all_packet()
    int sum = 0;
    for (int i=0; i<3; i++)
    {   if (priority_queue[i] == 0)
    		printf("SW error null priority queue.... \n");   
    
    	sum += priority_queue[i]->get_queue_size();
    }
    
    if (num_packet != sum )
    	printf("SW ERROR Packet Counter mismatch num:%d sum:%d\n", num_packet, sum);   
    
    for (int i=0; i<3; i++)
    {
        priority_queue[i]->remove_all_packets();
    } 
    num_packet = 0;
    
    //#]
}

Packet* PriorityPacketQueue::remove_packet() {
    //#[ operation remove_packet()
    
    if (num_packet == 0)   
    {
    	return 0;
    }	              
    
    
    
    Packet * p_pkt_removed;
    
    for (int i=0; i<3; i++)
    {
    	if (priority_queue[i]->get_queue_size() == 0)
    		continue;     
    
    	p_pkt_removed = priority_queue[i]->remove_front_packet();
    	break;
    } 
    
    
    num_packet--;     
            
    
    // print_info();	            
    return p_pkt_removed;	
    
    //#]
}

Packet* PriorityPacketQueue::remove_packet(int pri) {
    //#[ operation remove_packet(int)
    
    //if (num_packet_priority[pri] == 0)   
    if (priority_queue[pri]->get_queue_size() == 0)   
    {
    	return 0;
    }	              
    
    Packet * p_pkt_removed;
    p_pkt_removed = priority_queue[pri]->remove_front_packet(); 
    
    if (p_pkt_removed == 0)
    {
    	printf(" SW ERROR Null pointer head priority:%d ============================ \n", pri );
        print_info();
    }
    
    num_packet--;     
    	
    
    return p_pkt_removed;	
    
    //#]
}

Packet* PriorityPacketQueue::remove_packet_start_from(int p) {
    //#[ operation remove_packet_start_from(int)
    
    if (num_packet == 0)   
    {
    	return 0;
    }	              
    
    
    /*p_pkt_removed = packet_head[priority_to_complete];
    
    if (p_pkt_removed == 0)
    {
    	printf(" SW ERROR Null pointer head priority:%d time:%d ============================ \n", priority_to_complete, time_to_complete );
        print_info();
    }
    packet_head[priority_to_complete] = p_pkt_removed->getNext();    
    */
    
    	
    Packet * p_pkt_removed;
    
    for (int i=0; i<3; i++)
    {
    	int idx = (i+p)%3;
    	if (priority_queue[idx]->get_queue_size() == 0)
    		continue;     
    
    	p_pkt_removed = priority_queue[idx]->remove_front_packet();
    	break;
    } 
    
    
    num_packet--;     
            
    
    // print_info();	            
    return p_pkt_removed;	
    
    //#]
}

void PriorityPacketQueue::reset_load_count(int clk) {
    //#[ operation reset_load_count(int)
    for (int i=0; i<3; i++)
    {
    	load_counter[i] = 0;
    			
    }  
    load_counter_total = 0;
    
    
    //#]
}

void PriorityPacketQueue::update_load_stats(int clk) {
    //#[ operation update_load_stats(int)
    load_updated = 1;  
    
    if (load_counter_total == 0) 
    {
    	for (int i=0; i<3; i++)
    	{
    	    updated_load[i] = 0;  
    	}
    	return;
    }
    for (int i=0; i<3; i++)
    {
        int current_load = 100*load_counter[i]/load_counter_total; 
    	updated_load[i] = current_load;  
    }
    
    if (clk < 10000) 
    {
    	fprintf(sim_result, "load_per_priority  ");
    	for (int i=0; i<3; i++)
    	{
    		fprintf(sim_result, " %d ", updated_load[i]);
    	}  
    	fprintf(sim_result, " clk %d \n", clk); 
    }
    
    
    
    
    //#]
}

int PriorityPacketQueue::getBw_gbps() const {
    return bw_gbps;
}

void PriorityPacketQueue::setBw_gbps(int p_bw_gbps) {
    bw_gbps = p_bw_gbps;
}

int PriorityPacketQueue::getInterval_update_load() const {
    return interval_update_load;
}

void PriorityPacketQueue::setInterval_update_load(int p_interval_update_load) {
    interval_update_load = p_interval_update_load;
}

int PriorityPacketQueue::getLoad_counter(int i1) const {
    return load_counter[i1];
}

void PriorityPacketQueue::setLoad_counter(int i1, int p_load_counter) {
    load_counter[i1] = p_load_counter;
}

int PriorityPacketQueue::getLoad_counter_total() const {
    return load_counter_total;
}

void PriorityPacketQueue::setLoad_counter_total(int p_load_counter_total) {
    load_counter_total = p_load_counter_total;
}

int PriorityPacketQueue::getLoad_updated() const {
    return load_updated;
}

void PriorityPacketQueue::setLoad_updated(int p_load_updated) {
    load_updated = p_load_updated;
}

int PriorityPacketQueue::getNum_packet() const {
    return num_packet;
}

void PriorityPacketQueue::setNum_packet(int p_num_packet) {
    num_packet = p_num_packet;
}

int PriorityPacketQueue::getPrev_load(int i1) const {
    return prev_load[i1];
}

void PriorityPacketQueue::setPrev_load(int i1, int p_prev_load) {
    prev_load[i1] = p_prev_load;
}

int PriorityPacketQueue::getUpdated_load(int i1) const {
    return updated_load[i1];
}

void PriorityPacketQueue::setUpdated_load(int i1, int p_updated_load) {
    updated_load[i1] = p_updated_load;
}

int PriorityPacketQueue::getPriority_queue() const {
    int iter = 0;
    return iter;
}

void PriorityPacketQueue::addPriority_queue(PacketQueue* p_PacketQueue) {
    for (int pos = 0; pos < 3; pos++) {
    	if (!priority_queue[pos]) {
    		priority_queue[pos] = p_PacketQueue;
    		break;
    	}
    }
}

void PriorityPacketQueue::removePriority_queue(PacketQueue* p_PacketQueue) {
    for (int pos = 0; pos < 3; pos++) {
    	if (priority_queue[pos] == p_PacketQueue) {
    		priority_queue[pos] = NULL;
    	}
    }
}

void PriorityPacketQueue::clearPriority_queue() {
}

void PriorityPacketQueue::cleanUpRelations() {
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/PriorityPacketQueue.cpp
*********************************************************************/
