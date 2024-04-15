/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: AppStats
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/AppStats.cpp
*********************************************************************/

//## auto_generated
#include <iostream>
//## auto_generated
#include "AppStats.h"
//## package Default

//## class AppStats
AppStats::AppStats(int app_id_, int dev_id_) {
    //#[ operation AppStats(int,int)
    //printf("Application constructor \n");    
    
                                   
    app_idx = app_id_;    
    dev_idx = dev_id_;
                                             
                                             
     
    
    
    //#]
}

AppStats::~AppStats() {
    //#[ operation ~AppStats()
    
    
    //#]
}

void AppStats::print_info() {
    //#[ operation print_info()
    printf("appstats info app_id %d  \n", app_idx);       
    printf("sum_delay_created:%ld, sum_delay_rtt:%ld sum_delay_internal:%ld, num_pkt:%d \n", 
            sim_value_sum_delay_created, sim_value_sum_delay_rtt, sim_value_sum_delay_internal, num_sim_packets);
    //#]
}

void AppStats::update_rtt_delay_stats(int pri, int t_create, int t_current) {
    //#[ operation update_rtt_delay_stats(int,int,int)
           
    int rtt_delay = t_current-t_create;
    if (rtt_delay < RttDelayMax)
    {
    	sim_value_rtt_delay_histo[rtt_delay] ++;
    }
    else
    {
    	// printf("!!!!!RTT DELAY overflow priority!!!! at %d priority %d rtt:%d \n", vGlobalClock, pri, rtt_delay);
    	sim_value_rtt_delay_histo[RttDelayMax-1] ++; 	  
    }
    //#]
}

int AppStats::getNum_sim_packets() const {
    return num_sim_packets;
}

void AppStats::setNum_sim_packets(int p_num_sim_packets) {
    num_sim_packets = p_num_sim_packets;
}

AppStats::AppStats() {
}

void AppStats::add_file_flit_size_to_rcv(int inc) {
    //#[ operation add_file_flit_size_to_rcv(int)
    file_flit_size_to_rcv += inc;
    
    //#]
}

void AppStats::add_file_flit_size_to_send(int inc) {
    //#[ operation add_file_flit_size_to_send(int)
    file_flit_size_to_send += inc;
    
    //#]
}

void AppStats::add_sim_value_sum_delay(int t1, int t2, int t3, int clk) {
    //#[ operation add_sim_value_sum_delay(int,int,int,int)
    int old_sum_d1 = sim_value_sum_delay_created;
    int old_sum_d2 = sim_value_sum_delay_rtt;
    int old_sum_d3 = sim_value_sum_delay_internal;  
    
    
    sim_value_sum_delay_created  += clk-t1;
    sim_value_sum_delay_rtt      += clk-t2;
    sim_value_sum_delay_internal += clk-t3;    
    
    if (old_sum_d1 > sim_value_sum_delay_created || old_sum_d2 > sim_value_sum_delay_rtt ||old_sum_d3 > sim_value_sum_delay_internal)
    {
    	printf("SW Error delay sum overflow at %d\n  old - d1:%u d2:%d d3:%d \n  new d1:%ld d2:%ld d3:%ld\n", clk, old_sum_d1, old_sum_d2, old_sum_d3, sim_value_sum_delay_created, sim_value_sum_delay_rtt, sim_value_sum_delay_internal);
    	print_info();   
    	exit(1);
    }
    
    if(sim_value_sum_delay_created < sim_value_sum_delay_rtt  || sim_value_sum_delay_rtt < sim_value_sum_delay_internal || sim_value_sum_delay_created < sim_value_sum_delay_internal)
    {
    	printf("SW Error invalid delay sum clk:%d t1:%d t2:%d t3:%d\n", clk, t1, t2, t3);
    	print_info();   
    	exit(1);
    }
    
    
    //#]
}

void AppStats::check_histo_with_total_packets(int n_pkts) {
    //#[ operation check_histo_with_total_packets(int)
    
    
    int sum=0;
    
    for (int i=0; i<RttDelayMax; i++)
    {
    	if  (sim_value_rtt_delay_histo[i])
    		sum+= sim_value_rtt_delay_histo[i];
    }                                    
    
    if (n_pkts != sum)
    {
    	printf("SW Error histo and sum mismatch app_id:%d, n_pkts:%d, sum:%d \n", app_idx, n_pkts, sum);
    	
    	for (int i=0; i<RttDelayMax; i++)
    	{
    		if  (sim_value_rtt_delay_histo[i])
    			printf("delay %d: %ld times \n", i, sim_value_rtt_delay_histo[i]); 
    	}
    }
                               
    //#]
}

void AppStats::increase_num_sim_packets(int inc) {
    //#[ operation increase_num_sim_packets(int)
    num_sim_packets += inc;
    
    //#]
}

void AppStats::print_rtt_to_file(FILE * p_file) {
    //#[ operation print_rtt_to_file(FILE *)
    for (int i=0; i<RttDelayMax; i++)   
    {
    	if (sim_value_rtt_delay_histo[i] == 0)
    		continue;
    	fprintf(p_file,"app_id %d rtt delay: %d occurs: %ld \n", app_idx, i, sim_value_rtt_delay_histo[i]);
    }      
    	    
    
    //#]
}

void AppStats::reset(int f_size, int flt_size) {
    //#[ operation reset(int,int)
    //memset(&sim_value_rtt_delay_histo[0], 0, sizeof(unsigned long)*RttDelayMax);
    
    
    file_flit_size_to_send = f_size/flt_size;
    file_flit_size_to_rcv = f_size/flt_size;
    
    num_sim_packets = 0;           
    
    sim_value_max_delay = 0;
    sim_value_sum_delay_created = 0;
    sim_value_sum_delay_rtt = 0;
    sim_value_sum_delay_internal = 0;
    for (int i=0; i<RttDelayMax; i++)
    	sim_value_rtt_delay_histo[i] = 0;
    	
    //#]
}

void AppStats::write_file_completion_time(int clk, int a_id, int pri, int multi, int return_ck, int load, int cnt_q, int ser_q) {
    //#[ operation write_file_completion_time(int,int,int,int,int,int,int,int)
    
    file_completion_time = clk;    
    printf("completion: %d app_id: %d priority: %d optical: %d return_ck: %d load: %d cnt_q: %d ser_q: %d strict_priority: %d  num_packets: %d \n", 
    		clk, a_id, pri, multi, return_ck, load, cnt_q, ser_q, StrictPriority, num_sim_packets);  
    
    //fprintf(sim_result3,"completion: %d app_id: %d priority: %d optical: %d return_ck: %d load: %d cnt_q: %d ser_q: %d strict_priority: %d  num_packets: %d \n", 
    //					clk, a_id, pri, multi, return_ck, load, cnt_q, ser_q, StrictPriority, num_sim_packets);  
    					
    
    
    //#]
}

void AppStats::write_stats_and_reset(int app_id, int prio, const SimParam_struct& s_pr, int clk) {
    //#[ operation write_stats_and_reset(int,int,SimParam_struct,int)
    
      
    
    if (num_sim_packets == 0)
    	return;
    	
    int avg_d_created  = sim_value_sum_delay_created/num_sim_packets;
    int avg_d_rtt      = sim_value_sum_delay_rtt/num_sim_packets;
    int avg_d_internal = sim_value_sum_delay_internal/num_sim_packets;
    	
    printf (" %2d->%2d |  %3d |  %d  |%5d |%8d |%11d |%7d |%8d\n", 
    		 app_id, dev_idx, s_pr.load, prio, num_sim_packets, file_completion_time, avg_d_created, avg_d_rtt, avg_d_internal); 
    //printf ("app_%d pkts:%d in %d, %dkB complete at %d, avg delay d1:%d d2:%d d3:%d\n", 
    //		 app_id, num_sim_packets, clk, f_size/1000, file_completion_time, avg_d_created, avg_d_rtt, avg_d_internal); 
    		 
    if (avg_d_created<avg_d_rtt||avg_d_rtt<avg_d_internal||avg_d_created<avg_d_internal)
    	printf ("SW Error invalid average delay avg_delay_created:%d rtt:%d internal:%d\n", 
    		 avg_d_created, avg_d_rtt, avg_d_internal); 
      
    
    check_histo_with_total_packets(num_sim_packets);
    
    if (num_sim_packets!=0)
    fprintf(sim_result2,"app_id: %d prioirty: %d load: %d window: %d resp_check: %d mem_bw: %d load_q_size: %d comp_time: %d max_delay: %d sum_delay_app: %ld e2e: %ld internal: %ld num_packets: %d \n", 
    					app_id, prio, s_pr.load, s_pr.window_size, s_pr.resp_link_check, s_pr.mem_bw_mbps/1000, s_pr.load_update_queue, file_completion_time, sim_value_max_delay, sim_value_sum_delay_created, sim_value_sum_delay_rtt, sim_value_sum_delay_internal, num_sim_packets);   
    					
        
    sim_value_max_delay = 0;
    sim_value_sum_delay_created = 0;
    sim_value_sum_delay_rtt = 0;
    sim_value_sum_delay_internal = 0;
    num_sim_packets = 0;
    file_completion_time = 0;
                           
    //#]
}

int AppStats::getApp_idx() const {
    return app_idx;
}

void AppStats::setApp_idx(int p_app_idx) {
    app_idx = p_app_idx;
}

int AppStats::getDev_idx() const {
    return dev_idx;
}

void AppStats::setDev_idx(int p_dev_idx) {
    dev_idx = p_dev_idx;
}

int AppStats::getFile_completion_time() const {
    return file_completion_time;
}

void AppStats::setFile_completion_time(int p_file_completion_time) {
    file_completion_time = p_file_completion_time;
}

int AppStats::getFile_flit_size_to_rcv() const {
    return file_flit_size_to_rcv;
}

void AppStats::setFile_flit_size_to_rcv(int p_file_flit_size_to_rcv) {
    file_flit_size_to_rcv = p_file_flit_size_to_rcv;
}

int AppStats::getFile_flit_size_to_send() const {
    return file_flit_size_to_send;
}

void AppStats::setFile_flit_size_to_send(int p_file_flit_size_to_send) {
    file_flit_size_to_send = p_file_flit_size_to_send;
}

int AppStats::getSim_value_max_delay() const {
    return sim_value_max_delay;
}

void AppStats::setSim_value_max_delay(int p_sim_value_max_delay) {
    sim_value_max_delay = p_sim_value_max_delay;
}

unsigned long AppStats::getSim_value_rtt_delay_histo(int i1) const {
    return sim_value_rtt_delay_histo[i1];
}

void AppStats::setSim_value_rtt_delay_histo(int i1, unsigned long p_sim_value_rtt_delay_histo) {
    sim_value_rtt_delay_histo[i1] = p_sim_value_rtt_delay_histo;
}

unsigned long AppStats::getSim_value_sum_delay_created() const {
    return sim_value_sum_delay_created;
}

void AppStats::setSim_value_sum_delay_created(unsigned long p_sim_value_sum_delay_created) {
    sim_value_sum_delay_created = p_sim_value_sum_delay_created;
}

unsigned long AppStats::getSim_value_sum_delay_internal() const {
    return sim_value_sum_delay_internal;
}

void AppStats::setSim_value_sum_delay_internal(unsigned long p_sim_value_sum_delay_internal) {
    sim_value_sum_delay_internal = p_sim_value_sum_delay_internal;
}

unsigned long AppStats::getSim_value_sum_delay_rtt() const {
    return sim_value_sum_delay_rtt;
}

void AppStats::setSim_value_sum_delay_rtt(unsigned long p_sim_value_sum_delay_rtt) {
    sim_value_sum_delay_rtt = p_sim_value_sum_delay_rtt;
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/AppStats.cpp
*********************************************************************/
