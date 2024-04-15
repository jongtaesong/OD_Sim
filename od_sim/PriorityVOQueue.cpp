/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: PriorityVOQueue
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/PriorityVOQueue.cpp
*********************************************************************/

//## auto_generated
#include "PriorityVOQueue.h"
//## operation add_packet(int,int,Packet)
#include "Packet.h"
//## link itsVOQueue
#include "VOQueue.h"
//## auto_generated
#include <iostream>
//## package Default

//## class PriorityVOQueue
PriorityVOQueue::PriorityVOQueue(char* name_, int n_out) : bw_gbps(100), num_packet(0) {
    {
        for (int pos = 0; pos < 3; pos++) {
        	itsVOQueue[pos] = NULL;
        }
    }
    //#[ operation PriorityVOQueue(char*,int)
    
    char n[40];   
    
    sprintf(name,"%s",name_);
    
    num_output = n_out;
    for (int i=0; i<3; i++)
    {
    	sprintf(n,"%s_pri_%d", name_, i);
    	if(DEBUG) printf("%s creating %s \n", name, n);
    	itsVOQueue[i] = new VOQueue(n, n_out);
    	itsVOQueue[i]->set_name_string(n);
    } 
    
    //#]
}

PriorityVOQueue::PriorityVOQueue() : bw_gbps(100), num_packet(0) {
    {
        for (int pos = 0; pos < 3; pos++) {
        	itsVOQueue[pos] = NULL;
        }
    }
}

PriorityVOQueue::~PriorityVOQueue() {
    cleanUpRelations();
}

void PriorityVOQueue::add_packet(int priority, int out, Packet*& p_pkt) {
    //#[ operation add_packet(int,int,Packet)
    
    // if the priority queue is empty     
    
    int pri = p_pkt->getPriority();
    int o = p_pkt->getApp_id();
    
    
    num_packet++;  
    num_packet_priority[pri]++;
    
    if(DEBUG) printf("%s: Add packet to Priority VoQ p %d out %d\n", name, pri, out);
    itsVOQueue[pri]->add_packet(out, p_pkt);   
    if(DEBUG) printf("%s: Add packet to Priority VoQ p %d out %d Complete\n", name, pri, out);
    
    //#]
}

Packet* PriorityVOQueue::generate_load_update_packet(int size) {
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

int PriorityVOQueue::get_front_packet(int pri, int output) {
    //#[ operation get_front_packet(int,int)
    //if (num_packet_priority[pri] == 0)   
    return itsVOQueue [pri]->get_num_packet_output(output);
    
    //#]
}

int PriorityVOQueue::get_num_packet(int pri, int output) {
    //#[ operation get_num_packet(int,int)
    //if (num_packet_priority[pri] == 0)   
    return itsVOQueue [pri]->get_num_packet_output(output);
    
    //#]
}

int PriorityVOQueue::get_num_packet_priority(int pri) {
    //#[ operation get_num_packet_priority(int)
    return num_packet_priority[pri];
    
    //#]
}

void PriorityVOQueue::print_info() {
    //#[ operation print_info()
    printf("  %s Total Packets:%d \n", name, num_packet);
    
    Packet * p_pkt;
    for (int i=0; i<3; i++)
    {
    	printf("priority Queue %d has %d packets\n", i, itsVOQueue[i]->getNum_packet());      
        itsVOQueue[i]->print_info();
    }    
    
    
    printf("Load Count ");      
    for (int i=0; i<3; i++)
    	printf(" %d ", load_counter[i]);       
    printf(" total %d ", load_counter_total);      
    printf("\n");      
    //#]
}

void PriorityVOQueue::print_info_simple() {
    //#[ operation print_info_simple()
    printf("Priority VOQ Total Packets:%d \n", num_packet);
    Packet * p_pkt;
    for (int i=0; i<3; i++)
    {
    	printf("priority %d has %d packets\n", i, itsVOQueue[i]->getNum_packet());      
    }    
    
    /*
    printf("Load Count ");      
    for (int i=0; i<3; i++)
    	printf(" %d ", load_counter[i]);       
    printf(" total %d ", load_counter_total);      
    printf("\n");      
    
    printf(" ============================== \n \n ");
    */
    //#]
}

int PriorityVOQueue::random_memory_access_delay() {
    //#[ operation random_memory_access_delay()
    return rand()%3;    
    
    //#]
}

void PriorityVOQueue::reinit() {
    //#[ operation reinit()
    
    if(DEBUG) printf("Priority VOQ %s initialize ... remove all packets ... \n", name);
    num_packet = 0;
    load_updated = 1;  
    
    load_counter_total = 0;
    
    for (int i=0; i<3; i++)
    {	
    	num_packet_priority[i] = 0;
        updated_load[i] = 0;  
        load_counter[i] = 0;  
    	itsVOQueue[i]->reinit();
    }	
    //#]
}

void PriorityVOQueue::remove_all_packet() {
    //#[ operation remove_all_packet()
    int sum = 0;
    for (int i=0; i<3; i++)
    {   if (itsVOQueue[i] == 0)
    		printf("SW error null priority queue.... \n");   
    
    	sum += itsVOQueue[i]->getNum_packet();
    }
    
    if (num_packet != sum )
    	printf("SW ERROR Packet Counter mismatch num:%d sum:%d\n", num_packet, sum);   
    
    for (int i=0; i<3; i++)
    {
        itsVOQueue[i]->remove_all_packet();
    } 
    num_packet = 0;
    
    //#]
}

Packet* PriorityVOQueue::remove_packet(int pri, int output) {
    //#[ operation remove_packet(int,int)
    
    if (itsVOQueue[pri]->get_num_packet_output(output) == 0)   
    {
    	return 0;
    }	              
    
    Packet * p_pkt_removed;
    p_pkt_removed = itsVOQueue[pri]->remove_packet(output); 
    
    if (p_pkt_removed == 0)
    {
    	printf(" SW ERROR Null pointer head priority:%d ============================ \n", pri );
        print_info();
    }
    
    num_packet--;     
    num_packet_priority[pri]--;
    	
    
    return p_pkt_removed;	
    
    //#]
}

void PriorityVOQueue::reset_load_count(int clk) {
    //#[ operation reset_load_count(int)
    for (int i=0; i<3; i++)
    {
    	load_counter[i] = 0;
    			
    }  
    load_counter_total = 0;
    
    
    //#]
}

void PriorityVOQueue::update_load_count(int clk, int l_q) {
    //#[ operation update_load_count(int,int)
    if (StrictPriority)
    {
    	if (num_packet_priority[0] > l_q)
    		load_counter[0]++;
    	if (num_packet_priority[0] > l_q || num_packet_priority[1] > l_q)
    		load_counter[1]++;
    	if (num_packet_priority[0] > l_q || num_packet_priority[1] > l_q || num_packet_priority[2] > l_q)
    		load_counter[2]++;
    }
    else
    {
    	if (num_packet_priority[0] > l_q)
    		load_counter[0]++;
    	if (num_packet_priority[1] > l_q)
    		load_counter[1]++;
    	if (num_packet_priority[2] > l_q)
    		load_counter[2]++;
    }
    
    load_counter_total++;           
    
    
    
    //#]
}

void PriorityVOQueue::update_load_stats(int clk) {
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

int PriorityVOQueue::getBw_gbps() const {
    return bw_gbps;
}

void PriorityVOQueue::setBw_gbps(int p_bw_gbps) {
    bw_gbps = p_bw_gbps;
}

int PriorityVOQueue::getInterval_update_load() const {
    return interval_update_load;
}

void PriorityVOQueue::setInterval_update_load(int p_interval_update_load) {
    interval_update_load = p_interval_update_load;
}

int PriorityVOQueue::getLoad_counter(int i1) const {
    return load_counter[i1];
}

void PriorityVOQueue::setLoad_counter(int i1, int p_load_counter) {
    load_counter[i1] = p_load_counter;
}

int PriorityVOQueue::getLoad_counter_total() const {
    return load_counter_total;
}

void PriorityVOQueue::setLoad_counter_total(int p_load_counter_total) {
    load_counter_total = p_load_counter_total;
}

int PriorityVOQueue::getLoad_updated() const {
    return load_updated;
}

void PriorityVOQueue::setLoad_updated(int p_load_updated) {
    load_updated = p_load_updated;
}

int PriorityVOQueue::getNum_output() const {
    return num_output;
}

void PriorityVOQueue::setNum_output(int p_num_output) {
    num_output = p_num_output;
}

int PriorityVOQueue::getNum_packet() const {
    return num_packet;
}

void PriorityVOQueue::setNum_packet(int p_num_packet) {
    num_packet = p_num_packet;
}

int PriorityVOQueue::getNum_packet_priority(int i1) const {
    return num_packet_priority[i1];
}

void PriorityVOQueue::setNum_packet_priority(int i1, int p_num_packet_priority) {
    num_packet_priority[i1] = p_num_packet_priority;
}

int PriorityVOQueue::getPrev_load(int i1) const {
    return prev_load[i1];
}

void PriorityVOQueue::setPrev_load(int i1, int p_prev_load) {
    prev_load[i1] = p_prev_load;
}

int PriorityVOQueue::getRr_pointer(int i1) const {
    return rr_pointer[i1];
}

void PriorityVOQueue::setRr_pointer(int i1, int p_rr_pointer) {
    rr_pointer[i1] = p_rr_pointer;
}

int PriorityVOQueue::getUpdated_load(int i1) const {
    return updated_load[i1];
}

void PriorityVOQueue::setUpdated_load(int i1, int p_updated_load) {
    updated_load[i1] = p_updated_load;
}

int PriorityVOQueue::getItsVOQueue() const {
    int iter = 0;
    return iter;
}

void PriorityVOQueue::addItsVOQueue(VOQueue* p_VOQueue) {
    for (int pos = 0; pos < 3; pos++) {
    	if (!itsVOQueue[pos]) {
    		itsVOQueue[pos] = p_VOQueue;
    		break;
    	}
    }
}

void PriorityVOQueue::removeItsVOQueue(VOQueue* p_VOQueue) {
    for (int pos = 0; pos < 3; pos++) {
    	if (itsVOQueue[pos] == p_VOQueue) {
    		itsVOQueue[pos] = NULL;
    	}
    }
}

void PriorityVOQueue::clearItsVOQueue() {
}

void PriorityVOQueue::cleanUpRelations() {
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/PriorityVOQueue.cpp
*********************************************************************/
