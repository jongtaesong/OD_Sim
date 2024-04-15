/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Application
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/Application.cpp
*********************************************************************/

//## auto_generated
#include "Application.h"
//## auto_generated
#include <iostream>
//## link sim_stats
#include "AppStats.h"
//## operation find_cxl_switch(Packet)
#include "Packet.h"
//## link packet_queue
#include "PacketQueue.h"
//## link packet_serializer
#include "Serializer.h"
//## package Default

//## class Application
//Application::Application(int app_id_, int flt_size, int clk_per_us, int throttle_threshold_high, int throttle_threshold_mid, int throttle_threshold_low, int delta_severe, int delta_normal, int bw, int reqs_flit_, int wd_size, int lk_delay) : time_clock(0), connected_dev_index(-1), num_connected_dev(0), itsConnMap(), itsDevice(), itsSwitchCxl(), itsSwitchOptics() {
Application::Application(int app_id_, int flt_size, int clk_per_us, int throttle_threshold_high, int throttle_threshold_mid, int throttle_threshold_low, int delta_severe, int delta_normal, int bw, int reqs_flit_, int wd_size, int lk_delay) : time_clock(0), connected_dev_index(-1), num_connected_dev(0) {
    sim_stats = NULL;
    packet_serializer = NULL;
    packet_queue = NULL;
    //#[ operation Application(int,int,int,int,int,int,int,int,int,int,int,int)
    //printf("Application constructor \n");    
    time_clock = 0;         
    //connected_ld = new Device;  
    
    
    throttle_load_threshold[0] = throttle_threshold_high; // threshold between Mod Overload and Severly Overload      
    throttle_load_threshold[1] = throttle_threshold_mid; // threshold for lightly loaded and Mod overload 
    throttle_load_threshold[2] = throttle_threshold_low; // threshold between Mod Overload and Severly Overload      
    sim_param.th_high = throttle_threshold_high;
    sim_param.th_mid = throttle_threshold_mid;
    sim_param.th_low = throttle_threshold_low;
    
    throttle_delta[0] = delta_severe;
    throttle_delta[1] = delta_normal;   
    sim_param.delta_severe = delta_severe;
    sim_param.delta_normal = delta_normal;   
                                   
    
                                   
    sim_param.flit_size = flt_size;           
    sim_param.reqs_per_flit = reqs_flit_;
    sim_param.link_bw_mbps = bw;     
    
    
    
    flit_clocks = sim_param.clocks_per_usec*sim_param.flit_size*8/sim_param.link_bw_mbps;     
    
    for (int i=0; i<3; i++)
    	throttle_per_priority[i] = 0;
     
    printf("clocks_per_flit %d clk_per_us %d flit_size %d link_bw_mbps %d \n",flit_clocks, sim_param.clocks_per_usec, sim_param.flit_size, sim_param.link_bw_mbps);  
    
    char name_[64];
    
    index = app_id_;
    
    
    sprintf(name_,"%s_serializer", name);          
    packet_serializer = new Serializer (bw, lk_delay, name_, sim_param.clocks_per_usec);
    // packet_serializer->reinit(bw, lk_delay, name_);
    
    packet_queue = new PacketQueue;      
    sim_stats = new AppStats (app_id_, -1);       
    
    sim_param.window_size = wd_size;    
    num_pending_resp = 0; 
    
                                             
                                             
     
    
    
    //#]
}

Application::Application() : time_clock(0), connected_dev_index(-1), num_connected_dev(0), itsConnMap(), itsDevice(), itsSwitchCxl(), itsSwitchOptics() {
    packet_queue = NULL;
    packet_serializer = NULL;
    sim_stats = NULL;
}

Application::~Application() {
    //#[ operation ~Application()
    
    //itsPacket.clear();
    packet_queue->remove_all_packets();
    
    //#]
    cleanUpRelations();
}

void Application::generate_packet() {
    //#[ operation generate_packet()
    
    if (DEBUG) printf("%s genterates packet conditions load:%d \n",name, sim_param.load);
    
    if (num_connected_dev == 0)
    	return;
    
    //if (sim_stats->getFile_flit_size_to_send() < 1) // || time_scheduled > time_clock)
    //	return;
    
    //if (packet_queue->get_queue_size() > 1)
    //{
    //	return;
    //}  
    
    Packet * p_pkt = 0;        
    int prob = rand()%100;          
    
    ePacketType p_type = ReadReq;             
    
    int time_offset = 0; // = rand()%20; // 10 clock differnece
    
    if (DEBUG) printf("%s genterates packet load:%d prob:%d \n",name,  sim_param.load, prob);
    if (prob >= sim_param.load)
    { 
    	return;
    }
                        
    
         
    
    
    //std::cout << "app_id:" << app_id << ", Prob:"<<prob <<std::endl;
    
    p_pkt = new Packet;      
    p_pkt->setTime_created(time_clock);
    p_pkt->setTime_sending_complete(time_clock);
    p_pkt->setType(p_type);  
    
    p_pkt->setSize(sim_param.flit_size/sim_param.reqs_per_flit);	// 64 byte fixed size  
    p_pkt->setApp_id(index);
    
    p_pkt->setDevice_id(connected_dev_index);   
    p_pkt->setPriority(priority);     
    
         
    if (DEBUG) printf("%s: app_id %d genterate packet at %d \n", name, index, time_clock);
    if (DEBUG) p_pkt->print_info();
    
    packet_queue->add_packet(p_pkt); 
    
    if (sim_stats->getFile_flit_size_to_send() > 0)
    {	
    	sim_stats->add_file_flit_size_to_send(-1);
    } 
    
    
    //#]
}

void Application::print_packets() {
    //#[ operation print_packets()
    if (packet_queue->get_queue_size()>0)
    {
    	std::cout << std::endl << "app_id:"<<index<<std::endl;
    	packet_queue->print_all_packets();
    }
    //#]
}

void Application::process_clock(int clk) {
    //#[ operation process_clock(int)
    if (time_clock > clk)  
    {
    	std::cout<<"SW ERROR time_clock:"<<time_clock<<" clk:"<< clk <<" , in "<< __FILE__<<", "<<__FUNCTION__<<", "<<__LINE__<<std::endl;
    	print_packets();
    }                                               
    
    time_clock = clk;   
    
    
    
    if (time_clock%sim_param.link_clock_per_req == 0)
    {
    	if (DEBUG) printf("%s: process serializer \n", name);	
    	process_serializer_packet(clk);    
    	if (DEBUG) printf("%s: process packet \n", name);	
    	process_packet(time_clock);    
    	if (DEBUG) printf("%s: generate packet \n", name);	
    	generate_packet();       
    }
    //#]
}

void Application::process_packet(int t_clk) {
    //#[ operation process_packet(int)
    
    
    
    
    if (packet_queue->get_queue_size() == 0 || num_connected_dev == 0)
    {
    	//printf("app_id %d packet mepty \n", app_id);
    	return;
    }             
    if (num_pending_resp > sim_param.window_size)
    {
    	return;
    }   
    
    Packet * p_pkt = packet_queue->get_front_packet();
    int prob = rand()%100;
    if (prob < throttle_per_priority[p_pkt->getPriority()])
    {
    	return;
    } 
    
    
    /*if (packet_serializer->is_overflowed())
    {
    	return;
    } */
    
    
    p_pkt = packet_queue->remove_front_packet();
    
    if (p_pkt == 0)
    	std::cout << "SW_ERROR null pointer" << std::endl;
    
    
    /*if (p_pkt->getTime_to_send() == t_clk)
    {
    
    	itsPacket.pop_front();
    	std::cout << "Pop out packet at " << t_clk << std::endl;
    } 
    */     
    
    
    
    int t_created = p_pkt->getTime_created();
    ePacketType p_type = p_pkt->getType(); 
    p_pkt->setTime_tx_app(t_clk);
    
          
    //if (connected_ld == 0)
    //	std::cout << "SW Error NULL ld" << std::endl;       
    
    if (p_type == NullPacketType)
    {
    	// printf ("app_id:%d delete Null packet at clk:%d \n", app_id, t_clk); 
    	delete p_pkt;	
    }
    else 
    {   
    	packet_serializer->serialize_packet(p_pkt, t_clk);
    	num_pending_resp ++;   
    	if(DEBUG) printf("%s: sending packet num_pending_resp: %d \n", name, num_pending_resp);
    			     	  
    	if ( num_pending_resp > sim_param.window_size + 1)
    	  	printf("!!!!!!!! Pending Response Error !!!!!!!!! num_pending_resp: %d\n",num_pending_resp);         
    }
    
                    
    
    //#]
}

void Application::receive_response(Packet* p_pkt, int clk) {
    //#[ operation receive_response(Packet,int)
    
    
    if (p_pkt == 0)
    	std::cout << "SW ERROR 1111111" << ", in "<< __FILE__<<", "<<__FUNCTION__<<", "<<__LINE__<<std::endl;      
    
    
    if(DEBUG) printf("<<<<<< %s: Receive response ---  at %d \n",name, clk);
    if(DEBUG) p_pkt->print_info();
    	
    int pri = p_pkt->getPriority();  
    
    if (index != p_pkt->getApp_id())
    	printf("SW ERROR !!!!!! app_id mismatch error in %s %s %d \n", __FILE__, __FUNCTION__, __LINE__);
    	
    
    
    //if (vGlobalClock != clk)
    //	std::cout << "SW ERROR !!!!!! global clock time g_clk:"<<vGlobalClock << " clk:"<<clk<<" error in "<< __FILE__<<", "<<__FUNCTION__<<", "<<__LINE__<<std::endl;
    	          
      
    if (p_pkt->getType() == ReadResp)
    {
    	/*
    	if (sim_stats->getFile_flit_size_to_rcv() < 1)
    	{	
    		printf ("SW Error Receive Response when negative file size app:%d clk:%d file_to_send:%d, file_to_rcv:%d\n", 
    				app_id, clk, sim_stats->getFile_flit_size_to_send(), sim_stats->getFile_flit_size_to_rcv());     
    		p_pkt->print_info();
    	}
    	*/  
    	
    	num_pending_resp --;      
    	//printf("%s: receives response num_pending_resp: %d \n", name, num_pending_resp);    
    	
    	
    	int t1, t2, t3;
    	t1 = p_pkt->getTime_created();
    	t2 = p_pkt->getTime_tx_app();
    	t3 = p_pkt->getTime_tx_internal();
    	//if (t > sim_stats->getSim_value_max_delay())
    	//	sim_stats->setSim_value_max_delay (t);  
    	if (t1>t2||t2>t3||t1>t3)
    	{
    		printf("%s: SW Error invalid delay\n", name);
    		p_pkt->print_info();
    	} 
    	
    	int hold_measure = sim_param.max_sim_clock/20; 
    	//if (clk>hold_measure)
    	{
    		sim_stats->add_sim_value_sum_delay (t1, t2, t3, clk);     
    	    sim_stats->increase_num_sim_packets(1);
    		sim_stats->update_rtt_delay_stats(pri, p_pkt->getTime_created(), clk);   
    	}
    	
    	//int current_avg = sim_stats->getSim_value_sum_delay_rtt()/sim_stats->getNum_sim_packets();
    	
    	//if (current_avg < 0 || t < 0)
    	//	printf ("SW Error negative delay value current_avg:%d sum:%d delay:%d in app:%d\n", current_avg, sim_stats->getSim_value_sum_delay(), t, index);
    	  
    	if (sim_stats->getFile_flit_size_to_rcv() > 0)
    	{	
    		sim_stats->add_file_flit_size_to_rcv(-1);
    		//printf ("rcv_file_size:%d in app:%d \n", file_size_to_rcv, app_id);
    		if (sim_stats->getFile_flit_size_to_rcv() < 1)
    		{
    			sim_stats->setFile_completion_time(clk);
    		}
    	} 
     
    }    
    
    // printf("<<<<<< %s: Process LoadControl ---  %s %s %d \n",name, __FILE__, __FUNCTION__, __LINE__);
    /*if (p_pkt->getType() == LoadControl)
    {
    	//printf("%s Receive load control packet app_id %d at %d \n", name, app_id, clk);     
    	if (p_pkt->getLoad_updated())
    	{
    		update_throttle(p_pkt);
    	}      	
    } */
    
     
    delete p_pkt;   
    
    if (num_pending_resp < 0 || (num_pending_resp > sim_param.window_size+1))
    {
    	printf("SW ERROR !!!!!!  pending response error n_pending_resp %d  %s %s %d \n", num_pending_resp, __FILE__, __FUNCTION__, __LINE__);
    } 
    //#]
}

void Application::reinit_(int ld, int file_size_, int lk_delay, int w_size) {
    //#[ operation reinit_(int,int,int,int)
    if(DEBUG) printf("App %s initialize ...\n", name);
    time_clock = 0;   
    char name_[64];
    sprintf(name_,"app_id_%d_packet_queue", index);
    
    packet_queue->reinit(name_);
    sim_param.load = ld;   
    num_pending_resp = 0;
    
    if(DEBUG) printf("Reset sim_stats file_size %d flit_size %d \n", sim_param.file_size, sim_param.flit_size);    
    sim_stats->reset(sim_param.file_size, sim_param.flit_size);
    
    
    
    if (num_connected_dev == 1)
    {
    	if(DEBUG) printf("Reinit %s_serializer num_device %d\n", name, num_connected_dev);    
    	sprintf(name_,"%s_serializer", name);    
    	packet_serializer->reinit(sim_param.link_bw_mbps, sim_param.link_delay, name_);   
    }
    else if (num_connected_dev != 0)
    {
        printf("SW ERROR %s has invalid num_connected_dev %d shoud be 1 or 0 \n", name, num_connected_dev);    
    }                                                                                        
    
    for (int i=0; i<3; i++)
    	throttle_per_priority[i] = 0;        
    	
    sim_param.window_size = w_size;
    
    if(DEBUG) print_info();
    
    //#]
}

void Application::schedule_packet(Packet*& p_pkt) {
    //#[ operation schedule_packet(Packet)
    
         
    if (p_pkt == 0)
    	std::cout <<"SW_ERROR!!! NULL Packet"<<std::endl;    
    
    packet_queue->add_packet(p_pkt);
    
    //#]
}

void Application::update_throttle(Packet* p_pkt) {
    //#[ operation update_throttle(Packet)
    
    ///*
    for (int i=0; i<3; i++) // per priority
    {
     	if (p_pkt->getUpdated_load(i) > throttle_load_threshold[0]) // severely overload
    	{
    		throttle_per_priority[i] += throttle_delta[0];
    	}
    	
    	else if (p_pkt->getUpdated_load(i) > throttle_load_threshold[1])  // mod overload
    	{
    		throttle_per_priority[i] += throttle_delta[1];
    	} 
    	else if (p_pkt->getUpdated_load(i) > throttle_load_threshold[2])  // optimally loaded
    	{
    		throttle_per_priority[i] += 0;
    	} 
    	else                                                     // lightly loded
    	{
    		throttle_per_priority[i] -= throttle_delta[1];
    	} 
    	
    	if (throttle_per_priority[i] > 90)
    		throttle_per_priority[i] = 90;
    	else if (throttle_per_priority[i] < 0)
    		throttle_per_priority[i] = 0;
    }  
    //*/
                          
    /*if (LoadUpdateOption == 1)
    {
    	for (int i=0; i<3; i++) // per priority
    	{
        
    	 	if (p_pkt->getUpdated_load(2) > throttle_load_threshold[0]) // severely overload
    		{
    			throttle_per_priority[i] += throttle_delta[0];
    		}
    		
    		else if (p_pkt->getUpdated_load(2) > throttle_load_threshold[1])  // mod overload
    		{
    			throttle_per_priority[i] += throttle_delta[1];
    		}
    		else                                                     // lightly loded
    		{
    			throttle_per_priority[i] -= throttle_delta[1];
    		} 
    		
    		if (throttle_per_priority[i] > 80)
    			throttle_per_priority[i] = 80;
    		else if (throttle_per_priority[i] < 0)
    			throttle_per_priority[i] = 0;
    
    	}        
    	if ( !(throttle_per_priority[0] == throttle_per_priority[1] && throttle_per_priority[2] == throttle_per_priority[1]))
    		printf("SW Error Throttle per priority should be the same!!!! %d %d %d ", throttle_per_priority[0], throttle_per_priority[1], throttle_per_priority[2]);
    }
    */
    
    
    if (sim_stats->getFile_flit_size_to_rcv() > 0)
    {
    	//fprintf(sim_result, "throttle_update at %d app_id %d load", time_clock, index);
    	//printf("throttle_update at %d app_id %d load", time_clock, app_id);
    	for (int i=0; i<3; i++) // per priority
    	{
    		//fprintf(sim_result, " %d", p_pkt->getUpdated_load(i));		
    		//printf(" %d", p_pkt->getUpdated_load(i));		
    	}    
    	
    	//fprintf(sim_result, " throttle");
    	//printf(" throttle");
    	
    	for (int i=0; i<3; i++) // per priority
    	{
    		//fprintf(sim_result, " %d", throttle_per_priority[i]);		
    		//printf(" %d", throttle_per_priority[i]);		
    	}    
    	
    	//fprintf(sim_result, " file_size %d\n", sim_stats->getFile_flit_size_to_rcv());
    	//printf(" file_size %d\n", sim_stats->getFile_flit_size_to_rcv());
    }
    //#]
}

void Application::update_time_clock(int clock) {
    //#[ operation update_time_clock(int)
    if (time_clock > clock)
    	std::cout<<"SW ERROR , in "<< __FILE__<<", "<<__FUNCTION__<<", "<<__LINE__<<std::endl;
    time_clock = clock;
    //#]
}

int Application::getNum_pending_resp() const {
    return num_pending_resp;
}

void Application::setNum_pending_resp(int p_num_pending_resp) {
    num_pending_resp = p_num_pending_resp;
}

int Application::getPriority() const {
    return priority;
}

void Application::setPriority(int p_priority) {
    priority = p_priority;
}

int Application::getThrottle_delta(int i1) const {
    return throttle_delta[i1];
}

void Application::setThrottle_delta(int i1, int p_throttle_delta) {
    throttle_delta[i1] = p_throttle_delta;
}

int Application::getThrottle_per_priority(int i1) const {
    return throttle_per_priority[i1];
}

void Application::setThrottle_per_priority(int i1, int p_throttle_per_priority) {
    throttle_per_priority[i1] = p_throttle_per_priority;
}

int Application::getTime_clock() const {
    return time_clock;
}

void Application::setTime_clock(int p_time_clock) {
    time_clock = p_time_clock;
}

void Application::cleanUpRelations() {
    {
        itsConnMap.clear();
    }
    {
        itsDevice.clear();
    }
    {
        itsSwitchCxl.clear();
    }
    {
        itsSwitchOptics.clear();
    }
    if(packet_queue != NULL)
        {
            packet_queue = NULL;
        }
    if(packet_serializer != NULL)
        {
            packet_serializer = NULL;
        }
    if(sim_stats != NULL)
        {
            sim_stats = NULL;
        }
}

void Application::print_info() {
    //#[ operation print_info()
    printf("%s: index %d \n  file_size %d flit_clocks %d flit_size %d priority %d\n", 
    		name, index, sim_param.file_size , flit_clocks, sim_param.flit_size, priority);    
    printf("  link_bw_mbps %d load %d  num_conn_device %d num_pending_resp %d\n", 
              sim_param.link_bw_mbps, sim_param.load, num_connected_dev, num_pending_resp);
    printf("  req_per_flit %d delta_sever %d  delta_normal %d th_high %d th_mid %d th_low  %d\n", 
              sim_param.reqs_per_flit, throttle_delta[0], throttle_delta[1], throttle_load_threshold[0], throttle_load_threshold[1], throttle_load_threshold[2]);         
    
    
    //#]
}

int Application::getFlit_clocks() const {
    return flit_clocks;
}

void Application::setFlit_clocks(int p_flit_clocks) {
    flit_clocks = p_flit_clocks;
}

int Application::getThrottle_load_threshold(int i1) const {
    return throttle_load_threshold[i1];
}

void Application::setThrottle_load_threshold(int i1, int p_throttle_load_threshold) {
    throttle_load_threshold[i1] = p_throttle_load_threshold;
}

Application::Application(int idx, const SimParam_struct& s_p) : time_clock(0), connected_dev_index(-1), num_connected_dev(0), itsConnMap(), itsDevice(), itsSwitchCxl(), itsSwitchOptics() {
    sim_stats = NULL;
    packet_serializer = NULL;
    packet_queue = NULL;
    //#[ operation Application(int,SimParam_struct)
    //printf("Application constructor \n");    
    time_clock = 0;         
    //connected_ld = new Device;  
    sim_param = s_p;
    
    throttle_load_threshold[0] = sim_param.th_high;
    throttle_load_threshold[1] = sim_param.th_mid;
    throttle_load_threshold[2] = sim_param.th_low;
    
    throttle_delta[0] = sim_param.delta_severe;
    throttle_delta[1] = sim_param.delta_normal;
                                   
    flit_clocks = sim_param.clocks_per_usec*sim_param.flit_size*8/sim_param.link_bw_mbps;     
    
    for (int i=0; i<3; i++)
    	throttle_per_priority[i] = 0;
    
    index = idx;
    packet_queue = new PacketQueue;      
    sim_stats = new AppStats (idx, -1);       
    
    num_pending_resp = 0; 
    
                                             
     
    
    
    //#]
}

void Application::createSerializer() {
    //#[ operation createSerializer()
    packet_serializer = new Serializer (sim_param.link_bw_mbps, sim_param.link_delay, name, sim_param.clocks_per_usec);
    //#]
}

SwitchCxl* Application::find_cxl_switch(Packet * p_pkt) {
    //#[ operation find_cxl_switch(Packet)
    ConnMap t_c_map;
    int c_idx = ConnMap::find_conn_map_index(p_pkt->getApp_id(), p_pkt->getDevice_id());     
    //printf("c_idx:%d\n",c_idx);
    
    ConnMap * conn_map = getItsConnMap(c_idx); 
    //conn_map->print_info();
    if (conn_map == 0)
    {
    	printf("NULL conn_map not exist for c_idx:%d\n",c_idx);   
    	p_pkt->print_info();
    }
    
    if(DEBUG) printf("conn map sw_idx:%d\n",conn_map->getSwitch_idx());
    
    SwitchCxl * p_sw_cxl = getItsSwitchCxl(conn_map->getSwitch_idx());
    return p_sw_cxl; 	
    //#]
}

int Application::get_file_completion_time() {
    //#[ operation get_file_completion_time()
    return sim_stats->getFile_completion_time();
    //#]
}

void Application::initialize(int f_size, int clk_per_us, int th_h, int th_m, int th_l, int d_sv, int d_norm, int bw, int req_flit, int w_size, int lk_delay) {
    //#[ operation initialize(int,int,int,int,int,int,int,int,int,int,int)
    //printf("Application constructor \n");    
    time_clock = 0;         
    //connected_ld = new Device;  
    
    
    throttle_load_threshold[0] = th_h; // threshold between Mod Overload and Severly Overload      
    throttle_load_threshold[1] = th_m; // threshold for lightly loaded and Mod overload 
    throttle_load_threshold[2] = th_l; // threshold between Mod Overload and Severly Overload      
    
    
    throttle_delta[0] = d_sv;
    throttle_delta[1] = d_norm;   
                                   
    
                                   
    sim_param.flit_size = f_size;           
    sim_param.reqs_per_flit = req_flit;
    sim_param.link_bw_mbps = bw;     
    
    
    
    flit_clocks = sim_param.clocks_per_usec*sim_param.flit_size*8/sim_param.link_bw_mbps;     
    
    for (int i=0; i<3; i++)
    	throttle_per_priority[i] = 0;
     
    printf("clocks_per_flit %d clk_per_us %d flit_size %d link_bw_mbps %d \n",flit_clocks, sim_param.clocks_per_usec, sim_param.flit_size, sim_param.link_bw_mbps);  
    
    
    packet_serializer = new Serializer (bw, lk_delay, name, sim_param.clocks_per_usec);
    // packet_serializer->reinit(bw, lk_delay, name_);
    
    packet_queue = new PacketQueue;      
    sim_stats = new AppStats (index, -1);       
    
    sim_param.window_size = w_size;    
    num_pending_resp = 0; 
    
                                             
                                             
     
    
    
    //#]
}

void Application::print_rtt_to_file(FILE * p_file) {
    //#[ operation print_rtt_to_file(FILE *)
    sim_stats->print_rtt_to_file(p_file); 
    	    
    
    //#]
}

void Application::process_serializer_packet(int t_clk) {
    //#[ operation process_serializer_packet(int)
    
    if(DEBUG) printf("%s: Process serializer packet... num_connected_device %d\n", name, num_connected_dev);     
    
    if (num_connected_dev == 0)
    {
    	// printf("%s: Process serializer packet... no_packet\n", name);
    	return;
    }   
    if (packet_serializer->getNum_packet()==0)
    {
    	// printf("%s: Process serializer packet... no_packet\n", name);
    	return;
    }   
    
    Packet * p_pkt = packet_serializer->pop_completed_packet(t_clk);       
    int dev_id;
    if(p_pkt)
    {
    	dev_id = p_pkt->getDevice_id();
    }
    else 
    {
    	return;
    }
    
    Device * p_dev;
    SwitchCxl * p_sw_cxl;
    SwitchOptics * p_sw_op;
    p_sw_cxl = find_cxl_switch(p_pkt);
    p_dev = getItsDevice (dev_id);
    
    if (p_sw_cxl)
    {  
    	if(DEBUG) printf(">>>>>>>>>>>> %s sends packet to cxl switch \n", name); 
    	if(DEBUG) p_pkt->print_info();
    	p_sw_cxl->receive_packet_from_app(p_pkt, t_clk);
    } 
    else if ( p_dev )
    {
    	if(DEBUG) printf("%s sends packet to device %s\n", name, p_dev->get_name_string()); 
    	if(DEBUG) p_pkt->print_info();
    	p_dev->receive_packet(p_pkt, t_clk); 
    }
    else
    {
    	printf("ERROR no cxl switch found for device %d\n", dev_id); 
    	p_pkt->print_info();
    }
    
    //#]
}

void Application::reinit(const SimParam_struct& s_pr) {
    //#[ operation reinit(SimParam_struct)
    //sim_param = s_pr;
    
    if(DEBUG) printf("App %s initialize ...\n", name);
    time_clock = 0;   
    char name_[64];
    sprintf(name_,"app_id_%d_packet_queue", index);
    
    packet_queue->reinit(name_);
    num_pending_resp = 0;
    
    if(DEBUG) printf("Reset sim_stats file_size %d flit_size %d \n", sim_param.file_size, sim_param.flit_size);    
    sim_stats->reset(sim_param.file_size, sim_param.flit_size);
    
    
    
    if (num_connected_dev == 1)
    {
    	if(DEBUG) printf("Reinit %s_serializer num_device %d\n", name, num_connected_dev);    
    	sprintf(name_,"%s_serializer", name);    
    	packet_serializer->reinit(sim_param.link_bw_mbps, sim_param.link_delay, name_);   
    }
    else if (num_connected_dev != 0)
    {
        printf("SW ERROR %s has invalid num_connected_dev %d shoud be 1 or 0 \n", name, num_connected_dev);    
    }                                                                                        
    
    for (int i=0; i<3; i++)
    	throttle_per_priority[i] = 0;        
    	
    
    if(DEBUG) print_info();
    
    //#]
}

void Application::reset_stats() {
    //#[ operation reset_stats()
    sim_stats->reset(sim_param.file_size, sim_param.flit_size);
    	
    //#]
}

void Application::set_connected_dev_index(int dev_idx) {
    //#[ operation set_connected_dev_index(int)
    setConnected_dev_index(dev_idx);  
    sim_stats->setDev_idx(dev_idx);
    
    //#]
}

void Application::write_file_completion_time(int return_ck, int cnt_q, int ser_q) {
    //#[ operation write_file_completion_time(int,int,int)
    
    int t_complete = sim_stats->getFile_completion_time();  
    int num_sim_pkt = sim_stats->getNum_sim_packets();    
    int d_created = sim_stats->getSim_value_sum_delay_created();
    int d_rtt = sim_stats->getSim_value_sum_delay_rtt();
    int d_internal = sim_stats->getSim_value_sum_delay_internal();
    int max_delay = sim_stats->getSim_value_max_delay();
     
    //printf("completion: %d app_id: %d priority: %d optical: %d return_ck: %d load: %d cnt_q: %d ser_q: %d strict_priority: %d  num_packets: %d \n", 
    //		t_complete, app_id, priority, multi, return_ck, load, cnt_q, ser_q, StrictPriority, num_sim_pkt);  
    
    //if(num_sim_pkt!=0) 
    //fprintf(sim_result3, "completion: %d app_id: %d priority: %d return_ck: %d load: %d cnt_q: %d ser_q: %d st_prio: %d num_pkt: %d sum_delay_created: %d rtt: %d internal: %d max_delay: %d membw: %d throttled: %d window_size: %d\n", 
    //					  t_complete, index, priority, return_ck, sim_param.load, cnt_q, ser_q, StrictPriority, num_sim_pkt, d_created, d_rtt, d_internal, max_delay, sim_param.mem_bw_mbps/1000, IsThrottled,  sim_param.window_size);  
    
    					
    
    //#]
}

void Application::write_stats_and_reset(int app_id, int prio, int clk) {
    //#[ operation write_stats_and_reset(int,int,int)
    
      
    sim_stats->write_stats_and_reset(app_id, prio, sim_param, clk);
    //, p_file, sim_param.load_update_queue, sim_param.file_size, priority, sim_param.window_size);
                           
    //#]
}

int Application::getConnected_dev_index() const {
    return connected_dev_index;
}

void Application::setConnected_dev_index(int p_connected_dev_index) {
    connected_dev_index = p_connected_dev_index;
}

int Application::getNum_connected_dev() const {
    return num_connected_dev;
}

void Application::setNum_connected_dev(int p_num_connected_dev) {
    num_connected_dev = p_num_connected_dev;
}

SimParam_struct Application::getSim_param() const {
    return sim_param;
}

void Application::setSim_param(SimParam_struct p_sim_param) {
    sim_param = p_sim_param;
}

std::map<int, ConnMap*>::const_iterator Application::getItsConnMap() const {
    std::map<int, ConnMap*>::const_iterator iter;
    iter = itsConnMap.begin();
    return iter;
}

std::map<int, ConnMap*>::const_iterator Application::getItsConnMapEnd() const {
    return itsConnMap.end();
}

void Application::clearItsConnMap() {
    itsConnMap.clear();
}

void Application::removeItsConnMap(ConnMap* p_ConnMap) {
    std::map<int, ConnMap*>::iterator pos = std::find_if(itsConnMap.begin(), itsConnMap.end(),OMValueCompare<const int,ConnMap*>(p_ConnMap));
    if (pos != itsConnMap.end()) {
    	itsConnMap.erase(pos);
    }
}

ConnMap* Application::getItsConnMap(int key) const {
    std::map<int, ConnMap*>::const_iterator it = itsConnMap.find(key);
    if (it != itsConnMap.end())
    	return (*it).second;
    else
    	return NULL;
}

void Application::addItsConnMap(int key, ConnMap* p_ConnMap) {
    itsConnMap.insert(std::map<int, ConnMap*>::value_type(key, p_ConnMap));
}

void Application::removeItsConnMap(int key) {
    itsConnMap.erase(key);
}

std::map<int, Device*>::const_iterator Application::getItsDevice() const {
    std::map<int, Device*>::const_iterator iter;
    iter = itsDevice.begin();
    return iter;
}

std::map<int, Device*>::const_iterator Application::getItsDeviceEnd() const {
    return itsDevice.end();
}

void Application::clearItsDevice() {
    itsDevice.clear();
}

void Application::removeItsDevice(Device* p_Device) {
    std::map<int, Device*>::iterator pos = std::find_if(itsDevice.begin(), itsDevice.end(),OMValueCompare<const int,Device*>(p_Device));
    if (pos != itsDevice.end()) {
    	itsDevice.erase(pos);
    }
}

Device* Application::getItsDevice(int key) const {
    std::map<int, Device*>::const_iterator it = itsDevice.find(key);
    if (it != itsDevice.end())
    	return (*it).second;
    else
    	return NULL;
}

void Application::addItsDevice(int key, Device* p_Device) {
    itsDevice.insert(std::map<int, Device*>::value_type(key, p_Device));
}

void Application::removeItsDevice(int key) {
    itsDevice.erase(key);
}

std::map<int, SwitchCxl*>::const_iterator Application::getItsSwitchCxl() const {
    std::map<int, SwitchCxl*>::const_iterator iter;
    iter = itsSwitchCxl.begin();
    return iter;
}

std::map<int, SwitchCxl*>::const_iterator Application::getItsSwitchCxlEnd() const {
    return itsSwitchCxl.end();
}

void Application::clearItsSwitchCxl() {
    itsSwitchCxl.clear();
}

void Application::removeItsSwitchCxl(SwitchCxl* p_SwitchCxl) {
    std::map<int, SwitchCxl*>::iterator pos = std::find_if(itsSwitchCxl.begin(), itsSwitchCxl.end(),OMValueCompare<const int,SwitchCxl*>(p_SwitchCxl));
    if (pos != itsSwitchCxl.end()) {
    	itsSwitchCxl.erase(pos);
    }
}

SwitchCxl* Application::getItsSwitchCxl(int key) const {
    std::map<int, SwitchCxl*>::const_iterator it = itsSwitchCxl.find(key);
    if (it != itsSwitchCxl.end())
    	return (*it).second;
    else
    	return NULL;
}

void Application::addItsSwitchCxl(int key, SwitchCxl* p_SwitchCxl) {
    itsSwitchCxl.insert(std::map<int, SwitchCxl*>::value_type(key, p_SwitchCxl));
}

void Application::removeItsSwitchCxl(int key) {
    itsSwitchCxl.erase(key);
}

std::map<int, SwitchOptics*>::const_iterator Application::getItsSwitchOptics() const {
    std::map<int, SwitchOptics*>::const_iterator iter;
    iter = itsSwitchOptics.begin();
    return iter;
}

std::map<int, SwitchOptics*>::const_iterator Application::getItsSwitchOpticsEnd() const {
    return itsSwitchOptics.end();
}

void Application::clearItsSwitchOptics() {
    itsSwitchOptics.clear();
}

void Application::removeItsSwitchOptics(SwitchOptics* p_SwitchOptics) {
    std::map<int, SwitchOptics*>::iterator pos = std::find_if(itsSwitchOptics.begin(), itsSwitchOptics.end(),OMValueCompare<const int,SwitchOptics*>(p_SwitchOptics));
    if (pos != itsSwitchOptics.end()) {
    	itsSwitchOptics.erase(pos);
    }
}

SwitchOptics* Application::getItsSwitchOptics(int key) const {
    std::map<int, SwitchOptics*>::const_iterator it = itsSwitchOptics.find(key);
    if (it != itsSwitchOptics.end())
    	return (*it).second;
    else
    	return NULL;
}

void Application::addItsSwitchOptics(int key, SwitchOptics* p_SwitchOptics) {
    itsSwitchOptics.insert(std::map<int, SwitchOptics*>::value_type(key, p_SwitchOptics));
}

void Application::removeItsSwitchOptics(int key) {
    itsSwitchOptics.erase(key);
}

PacketQueue* Application::getPacket_queue() const {
    return packet_queue;
}

void Application::setPacket_queue(PacketQueue* p_PacketQueue) {
    packet_queue = p_PacketQueue;
}

Serializer* Application::getPacket_serializer() const {
    return packet_serializer;
}

void Application::setPacket_serializer(Serializer* p_Serializer) {
    packet_serializer = p_Serializer;
}

AppStats* Application::getSim_stats() const {
    return sim_stats;
}

void Application::setSim_stats(AppStats* p_AppStats) {
    sim_stats = p_AppStats;
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/Application.cpp
*********************************************************************/
