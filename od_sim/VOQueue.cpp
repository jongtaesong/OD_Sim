/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: VOQueue
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/VOQueue.cpp
*********************************************************************/

//## auto_generated
#include "VOQueue.h"
//## operation add_packet(int,Packet)
#include "Packet.h"
//## link vo_queue
#include "PacketQueue.h"
//## auto_generated
#include <iostream>
//## package Default

//## class VOQueue
VOQueue::VOQueue(char* n_, int n_out) : bw_gbps(100), num_output(0), num_packet(0) {
    {
        for (int pos = 0; pos < 32; pos++) {
        	vo_queue[pos] = NULL;
        }
    }
    //#[ operation VOQueue(char*,int)
    
    char n[40];
    
    num_output = n_out;   
    
    for (int i=0; i<num_output; i++)
    {
    	vo_queue[i] = new PacketQueue;
    	sprintf(n,"%s_output_%d", n_, i);
    	vo_queue[i]->set_name_string(n);
    }
    //#]
}

VOQueue::VOQueue() : bw_gbps(100), num_output(0), num_packet(0) {
    {
        for (int pos = 0; pos < 32; pos++) {
        	vo_queue[pos] = NULL;
        }
    }
}

VOQueue::~VOQueue() {
    cleanUpRelations();
}

void VOQueue::add_packet(int output, Packet*& p_pkt) {
    //#[ operation add_packet(int,Packet)
    
    // if the priority queue is empty     
    num_packet++; 
    num_packet_output[output]++; 
    
    
    vo_queue[output]->add_packet(p_pkt);
       
    
    //#]
}

Packet* VOQueue::generate_load_update_packet(int size) {
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

Packet* VOQueue::get_front_packet(int output) {
    //#[ operation get_front_packet(int)
    //if (num_packet_priority[pri] == 0)   
    if (vo_queue[output]->get_queue_size() == 0)   
    {
    	return 0;
    }	              
    
    Packet * p_pkt;
    p_pkt = vo_queue[output]->get_front_packet(); 
    
    if (p_pkt == 0)
    {
    	printf("%s: SW ERROR Null pointer head output:%d ============================ \n", name, output );
        print_info();
    }
    
    return p_pkt;	
    //#]
}

int VOQueue::get_num_packet_output(int output) {
    //#[ operation get_num_packet_output(int)
    
    return vo_queue[output]->get_queue_size();
    //#]
}

void VOQueue::print_info() {
    //#[ operation print_info()
    printf(" %s Total Packets:%d \n", name, num_packet);
    
    Packet * p_pkt;
    for (int i=0; i<num_output; i++)
    {
    	printf("Vo Queue %d has %d packets\n", i, vo_queue[i]->get_queue_size());      
        vo_queue[i]->print_all_packets();
    }    
    
    int sum = 0;
    for (int i=0; i<num_output; i++)
    {
    	sum+=vo_queue[i]->get_queue_size();
    }
    if (num_packet != sum)
    	printf("SW ERROR Packet Counter mismatch num:%d sum:%d\n", num_packet, sum);      
    
    printf("Load Count ");      
    for (int i=0; i<num_output; i++)
    	printf(" %d ", load_counter[i]);       
    printf(" total %d ", load_counter_total);      
    printf("\n");      
    //#]
}

int VOQueue::random_memory_access_delay() {
    //#[ operation random_memory_access_delay()
    return rand()%3;    
    
    //#]
}

void VOQueue::reinit() {
    //#[ operation reinit()
    
    if(DEBUG) printf("VOQ %s initialize ... remove all packets ... \n", name);
    remove_all_packet();
    num_packet = 0;
              
    char n[60];      
    for (int i=0; i<num_output; i++)
    {
    	sprintf(n, "%s_voq_%d",name ,i);
    	vo_queue[i]->reinit(n);
    }
    	
    //#]
}

void VOQueue::remove_all_packet() {
    //#[ operation remove_all_packet()
    int sum = 0;
    for (int i=0; i<num_output; i++)
    {   if (vo_queue[i] == 0)
    		printf("SW error null priority queue.... \n");   
    
    	sum += vo_queue[i]->get_queue_size();
    }
    
    if (num_packet != sum )
    	printf("SW ERROR Packet Counter mismatch num:%d sum:%d\n", num_packet, sum);   
    
    for (int i=0; i<num_output; i++)
    {
        vo_queue[i]->remove_all_packets();   
    } 
    num_packet = 0;
    
    //#]
}

Packet* VOQueue::remove_packet(int output) {
    //#[ operation remove_packet(int)
    
    if (vo_queue[output]->get_queue_size() == 0)   
    {
    	return 0;
    }	              
    
    Packet * p_pkt_removed;
    p_pkt_removed = vo_queue[output]->remove_front_packet(); 
    
    if (p_pkt_removed == 0)
    {
    	printf(" SW ERROR Null pointer head priority:%d ============================ \n", output );
        print_info();
    }
    
    num_packet--;         
    num_packet_output[output]--;
    	
    
    return p_pkt_removed;	
    
    //#]
}

Packet* VOQueue::remove_packet_start_from(int output) {
    //#[ operation remove_packet_start_from(int)
    
    if (num_packet == 0)   
    {
    	return 0;
    }	              
    	
    Packet * p_pkt_removed;
    
    for (int i=0; i<num_output; i++)
    {
    	if (vo_queue[(i+output)%num_output]->get_queue_size() == 0)
    		continue;
    	p_pkt_removed = vo_queue[output]->remove_front_packet();
    	break; 
    }
    
    num_packet--;     
    num_packet_output[output]--;     
    
    return p_pkt_removed;	
    
    //#]
}

void VOQueue::reset_load_count(int clk) {
    //#[ operation reset_load_count(int)
    for (int i=0; i<3; i++)
    {
    	load_counter[i] = 0;
    			
    }  
    load_counter_total = 0;
    
    
    //#]
}

void VOQueue::update_load_stats(int clk) {
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

int VOQueue::getBw_gbps() const {
    return bw_gbps;
}

void VOQueue::setBw_gbps(int p_bw_gbps) {
    bw_gbps = p_bw_gbps;
}

int VOQueue::getInterval_update_load() const {
    return interval_update_load;
}

void VOQueue::setInterval_update_load(int p_interval_update_load) {
    interval_update_load = p_interval_update_load;
}

int VOQueue::getLoad_counter(int i1) const {
    return load_counter[i1];
}

void VOQueue::setLoad_counter(int i1, int p_load_counter) {
    load_counter[i1] = p_load_counter;
}

int VOQueue::getLoad_counter_total() const {
    return load_counter_total;
}

void VOQueue::setLoad_counter_total(int p_load_counter_total) {
    load_counter_total = p_load_counter_total;
}

int VOQueue::getLoad_updated() const {
    return load_updated;
}

void VOQueue::setLoad_updated(int p_load_updated) {
    load_updated = p_load_updated;
}

int VOQueue::getNum_output() const {
    return num_output;
}

void VOQueue::setNum_output(int p_num_output) {
    num_output = p_num_output;
}

int VOQueue::getNum_packet() const {
    return num_packet;
}

void VOQueue::setNum_packet(int p_num_packet) {
    num_packet = p_num_packet;
}

int VOQueue::getNum_packet_output(int i1) const {
    return num_packet_output[i1];
}

void VOQueue::setNum_packet_output(int i1, int p_num_packet_output) {
    num_packet_output[i1] = p_num_packet_output;
}

int VOQueue::getPrev_load(int i1) const {
    return prev_load[i1];
}

void VOQueue::setPrev_load(int i1, int p_prev_load) {
    prev_load[i1] = p_prev_load;
}

int VOQueue::getUpdated_load(int i1) const {
    return updated_load[i1];
}

void VOQueue::setUpdated_load(int i1, int p_updated_load) {
    updated_load[i1] = p_updated_load;
}

int VOQueue::getVo_queue() const {
    int iter = 0;
    return iter;
}

void VOQueue::addVo_queue(PacketQueue* p_PacketQueue) {
    for (int pos = 0; pos < 32; pos++) {
    	if (!vo_queue[pos]) {
    		vo_queue[pos] = p_PacketQueue;
    		break;
    	}
    }
}

void VOQueue::removeVo_queue(PacketQueue* p_PacketQueue) {
    for (int pos = 0; pos < 32; pos++) {
    	if (vo_queue[pos] == p_PacketQueue) {
    		vo_queue[pos] = NULL;
    	}
    }
}

void VOQueue::clearVo_queue() {
}

void VOQueue::cleanUpRelations() {
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/VOQueue.cpp
*********************************************************************/
