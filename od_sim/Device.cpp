/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Device
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/Device.cpp
*********************************************************************/

//## auto_generated
#include "Device.h"
//## operation find_cxl_switch(Packet)
#include "Packet.h"
//## auto_generated
#include <iostream>
//## link rx_priority_queue
#include "PriorityPacketQueue.h"
//## link itsPriorityVOQueue
#include "PriorityVOQueue.h"
//## attribute switch_serializer
#include "Serializer.h"
//## package Default

//## class Device
Device::Device(char* name_, int t, int link_bw_gbps_, int mem_bw_gbps_, int flit_size_, int pr_delay, int n_app) : link_bw_gbps_(10), mem_bw_gbps_(10), itsApplication(), max_num_pkt_in_serializer_(2), itsConnMap(), itsSwitchCxl(), itsSwitchOptics() {
    tx_priority_queue = NULL;
    rx_priority_queue = NULL;
    packet_serializer_internal = NULL;
    {
        for (int pos = 0; pos < 32; pos++) {
        	packet_serializer[pos] = NULL;
        }
    }
    itsPriorityVOQueue = NULL;
    //#[ operation Device(char*,int,int,int,int,int,int)
    
    sprintf(name, "%s", name_);
    printf(" creating MEM %s \n", name_);
    
    
               
    char n[40];
                        
    //if (IsMultiReturnLinks)
    {
    	for (int i=0; i<num_connected_app; i++)
    	{
    		sprintf(n,"%s_multi_link_serial_%d", name_, i);
    		packet_serializer[i] = new Serializer(sim_param.link_bw_mbps, sim_param.link_delay, n, sim_param.clocks_per_usec);    
    		// packet_serializer[i]->setBw_gbps(link_bw_gbps_);
    		
    
    	}      
    	sprintf(n,"%s_priority_vo_queue", name_);
    	itsPriorityVOQueue = new PriorityVOQueue(n, num_connected_app);
    }
    //else
    {
    	sprintf(n,"%s_single_link_serial", name_);
    	switch_serializer = new Serializer (sim_param.link_bw_mbps, 0, n, sim_param.clocks_per_usec);    
    	//switch_serializer->setBw_gbps(link_bw_gbps_);
    	rx_priority_queue = new PriorityPacketQueue;
    	sprintf(n,"%s_rx_priority_queue", name_);
    	rx_priority_queue->set_name_string(n);
    	
    	tx_priority_queue = new PriorityPacketQueue;
    	sprintf(n,"%s_tx_priority_queue", name_);
    	tx_priority_queue->set_name_string(n);    
    } 
    
    
    sprintf(n,"%s_internal_serial", name_);
    packet_serializer_internal = new Serializer (sim_param.mem_bw_mbps, 0, n, sim_param.clocks_per_usec);
    
    
    for (int i=0; i<32; i++)
    {
    	app_idx_to_dest_port[i]=-1; 
    	dest_port_to_voq[i] = -1;
    	voq_to_dest_port[i] = -1;
    }
    
    
    
    //#]
}

Device::Device() : link_bw_gbps_(10), mem_bw_gbps_(10), itsApplication(), max_num_pkt_in_serializer_(2), itsConnMap(), itsSwitchCxl(), itsSwitchOptics() {
    itsPriorityVOQueue = NULL;
    {
        for (int pos = 0; pos < 32; pos++) {
        	packet_serializer[pos] = NULL;
        }
    }
    packet_serializer_internal = NULL;
    rx_priority_queue = NULL;
    tx_priority_queue = NULL;
}

Device::~Device() {
    cleanUpRelations();
}

void Device::process_clock_multi_links(int clk) {
    //#[ operation process_clock_multi_links(int)
    Packet * p_pkt, p_pkt2;     
    
    //printf("%s: process clock multi link  \n", name);
    
    if(DEBUG) printf("%s: process clock multi link initial check complete ... \n", name);
    
    if (IsThrottled && clk%sim_param.link_clock_per_flit ==0)
    {
    	//itsPriorityVOQueue->update_load_count(clk);
    	update_load_count();     
    }
    
    if(DEBUG) printf("%s: process clock multi link - update rx queue load count complete ... \n", name);
    
    if (IsThrottled && clk%sim_param.load_update_interval == 0)
    { 
    	if(DEBUG) printf("%s: generate load update packet ... \n", name);
    	
    	for (int i=0; i<num_connected_app; i++)
    	{	
    		p_pkt = generate_load_update_packet();	  
    	    p_pkt->setApp_id(i); 
    	    p_pkt->setTime_created(clk);    
    	    p_pkt->setPriority(0);
    		p_pkt->setDevice_id(index);
    		
    		packet_serializer[i]->serialize_packet(p_pkt, clk);
    	}
    	reset_load_count();
    	
    	/*itsPriorityVOQueue->update_load_stats();   
    	    
    	for (int i=0; i<num_app; i++)
    	{	
    		p_pkt = itsPriorityVOQueue->generate_load_update_packet();	  
    	    p_pkt->setApp_id(i);
    		packet_serializer[i]->serialize_packet(p_pkt, clk);
    	}
    	// rx_priority_queue->print_info();	
    	itsPriorityVOQueue->reset_load_count(clk);
    	*/ 
    } 
    
    
    
    
    
    
    if(DEBUG) printf("%s: process clock multi link - generate load update complete ... \n", name);
     
    //if (itsPriorityVOQueue->getNum_packet() && clk%MemClocksPerReq == 0 && packet_serializer_internal->getNum_packet()<1)
    if (itsPriorityVOQueue->getNum_packet() > 0 && packet_serializer_internal->getNum_packet()<2)//  && clk%MemClocksPerReq  == 0)
    {
    	// send the head to tx priority queue  
    	// tx_priority_queue->add_packet(p_pkt_pending->getPriority(), p_pkt);
    	// schedule next packet
    	p_pkt = 0;
    	if (sim_param.resp_link_check)
    	{
    		/*printf("%s: Before select at %d NumPkt: %d, %d, %d, NumPktSer: %d, %d, %d \n", 
    		name, clk, itsPriorityVOQueue->getNum_packet_priority(0), itsPriorityVOQueue->getNum_packet_priority(1), 
    		itsPriorityVOQueue->getNum_packet_priority(2), 
    		packet_serializer[0]->getNum_packet(), packet_serializer[1]->getNum_packet(), packet_serializer[2]->getNum_packet());
    		*/
    		
    		/*for (int i=0; i<3; i++)
    		{
    			int ii = 2-i;
    			int rr_pointer = itsPriorityVOQueue->getRr_pointer(ii);
    			
    			for (int j=0; j<num_app; j++)
    			{
    				int jj = (j+rr_pointer)%num_app;
    				if (itsPriorityVOQueue->get_num_packet(ii,jj) > 0 && packet_serializer[jj]->getNum_packet() == 0)
    				{
    					sel_pri = ii;
    					sel_app = jj;
    				}
    			}
    		}*/
    		
    		//printf("Empty queue ckeck complete pri:%d, app:%d\n", sel_pri, sel_app);  
    		for (int i=0; i<3; i++)
    		{
    			int ii = 2-i;
    			int rr_pointer = itsPriorityVOQueue->getRr_pointer(i);
    			
    			for (int j=0; j<num_connected_app; j++)
    			{
    				int jj = (j+rr_pointer)%num_connected_app;
    				if (itsPriorityVOQueue->get_num_packet(i,jj) == 0 || packet_serializer[jj]->getNum_packet() > sim_param.max_num_pkt_serialize - 1)
    					continue; 
    				p_pkt = itsPriorityVOQueue->remove_packet(i,jj);
    				itsPriorityVOQueue->setRr_pointer(i, (jj+1)%num_connected_app);
    				break; 
    			}
    			if (p_pkt)
    			{
    				//printf("%s: at %d NumPkt: %d, %d, %d, NumPktSer: %d, %d, %d pkt_priority:%d\n", 
    				//name, clk, itsPriorityVOQueue->getNum_packet_priority(0), itsPriorityVOQueue->getNum_packet_priority(1), 
    				//itsPriorityVOQueue->getNum_packet_priority(2), 
    				//packet_serializer[0]->getNum_packet(), packet_serializer[1]->getNum_packet(), packet_serializer[2]->getNum_packet(), p_pkt->getPriority());
    				break;
    			}
    		}
    		//printf("Priority queue ckeck complete pri:%d, app:%d\n", sel_pri, sel_app);  
     	}	
    	else
    	{
    		//printf("%s: at %d NumPkt: %d, %d, %d, NumPktSer: %d, %d, %d ", 
    		//		name, clk, itsPriorityVOQueue->getNum_packet_priority(0), itsPriorityVOQueue->getNum_packet_priority(1), 
    		//		itsPriorityVOQueue->getNum_packet_priority(2), 
    		//		packet_serializer[0]->getNum_packet(), packet_serializer[1]->getNum_packet(), packet_serializer[2]->getNum_packet());
    				
    		for (int i=0; i<3; i++)
    		{
    			int rr_pointer = itsPriorityVOQueue->getRr_pointer(i);
    			for (int j=0; j<num_connected_app; j++)
    			{
    				
    				int jj = (j+rr_pointer)%num_connected_app;
    				if (itsPriorityVOQueue->get_num_packet(i,jj) == 0 )
    					continue;
    			
    				p_pkt = itsPriorityVOQueue->remove_packet(i,jj);
    				itsPriorityVOQueue->setRr_pointer(i, (jj+1)%num_connected_app);
    				break; 
    			}
    			if (p_pkt)
    			{
    				//if (itsPriorityVOQueue->getNum_packet_priority(0) > 0 && p_pkt->getPriority() !=0)
    				//printf(" ...  pkt_priority:%d\n", p_pkt->getPriority());
    				//printf("%d: select lower priority p0:%d pkt_priority:%d\n", itsPriorityVOQueue->getNum_packet_priority(0), p_pkt->getPriority());
    				break;
    			}
    		}
    	}
    		
    	if (p_pkt)
    	{
    	    //printf("\n %s: Send Internal Serialize packet at %d\n", name, clk);
    		//p_pkt->print_info();
    		//print_info();
            p_pkt->setType(ReadResp);    
    		p_pkt->setSize(sim_param.flit_size); 
    		packet_serializer_internal->serialize_packet(p_pkt, clk);    
    		
    	}
    	else
    	{
    		//printf("\n %s: !!!!!!!!!!! No Packet Selected at %d\n", name, clk);
    		//print_info();	
    	}  
    }
    
    
    if(DEBUG) printf("%s: process clock multi link - internal serializer -> packet serializer ... \n", name);
    
    if (clk%sim_param.mem_clock_per_flit == 0) //	&& !packet_serializer_internal->is_overflowed())
    {
    	p_pkt = packet_serializer_internal->get_front();  
    	if (p_pkt)
    	{
    		int app_id = p_pkt->getApp_id();
    		//if (packet_serializer[app_id]->getNum_packet() < max_num_pkt_in_serializer)
    		{ 
    			p_pkt = packet_serializer_internal->pop_completed_packet(clk); 
    			if (p_pkt)
    			{
      
    				if (app_id != p_pkt->getApp_id())
    				{
    					printf("!!!!!!!!!!!SW Error invalid app_id expect:%d real:%d\n", app_id, p_pkt->getApp_id());
    				}
    				//printf("\n %s: Send Packet Serialize packet at %d\n", name, clk);
    				//p_pkt->print_info();
    				packet_serializer[app_id]->serialize_packet(p_pkt, clk);
    			}
    		}
    	}
    }                           
    
    if(DEBUG) printf("%s: process clock multi link - packet serialize send response ... \n", name);
    
    if (clk%sim_param.link_clock_per_flit == 0) //	&& !packet_serializer_internal->is_overflowed())
    {
    	for (int i=0; i<num_connected_app; i++)        // in tx side consider the priority as parallal links
    	{ 
    		//printf("%s: app %d ... %d\n", name, i);
    		p_pkt = packet_serializer[i]->pop_completed_packet(clk);
    		if (p_pkt)
    		{
    			if(DEBUG) printf("%s: process clock multi link - send response ... \n", name);   
    			if(DEBUG) p_pkt->print_info();
    			send_response(p_pkt, clk);  
    		}
    	} 
    }
    
    if(DEBUG) printf("%s: process clock multi link - complete ... \n", name);
     
    //#]
}

int Device::memory_access_clk(int size_, int speed_) {
    //#[ operation memory_access_clk(int,int)
    return size_*8/sim_param.mem_bw_mbps;
    //#]
}

void Device::receive_packet(Packet* p_pkt, int clk) {
    //#[ operation receive_packet(Packet,int)
    
    
    //printf("%s: >>>> Receives packet at %d\n", name, vGlobalClock);    
    //p_pkt->print_info();
    
    if (p_pkt == 0)
    	std::cout << "SW ERROR 1111111" << ", in "<< __FILE__<<", "<<__FUNCTION__<<", "<<__LINE__<<std::endl;      
    
    
    
    /*if (IsMultiReturnLinks)
    {
    	receive_packet_multi_link(p_pkt);
    }
    else
    {
    	receive_packet_single_link(p_pkt);
    } */
    
    receive_packet_flex(p_pkt, clk);
    
    
    ///printf("%s: receive packet at %d\n", name, vGlobalClock);
    //print_info();
    //printf("%s: LinkClkPerFlit:%d, LinkClkPerReq:%d, MemClkPerFlit:%d, MemClkPerReq:%d\n", name, LinkClocksPerFlit, LinkClocksPerReq, MemClocksPerFlit, MemClocksPerReq);
    //printf("%s: After receive packet print rx priority queue at %d\n", name, vGlobalClock);
    //rx_priority_queue->print_info();
    //printf("%s: After receive packet print tx priority queue at %d\n", name, vGlobalClock);
    //tx_priority_queue->print_info();    
    
    /*printf("   PVOQ:%d [%d, %d, %d], ISer:%d, PSer: [%d, %d, %d]\n",
    	   itsPriorityVOQueue->getNum_packet(), 
    	   itsPriorityVOQueue->getNum_packet_priority(0), itsPriorityVOQueue->getNum_packet_priority(1), itsPriorityVOQueue->getNum_packet_priority(2), 
    	   packet_serializer_internal->getNum_packet(), 
    	   packet_serializer[0]->getNum_packet(), packet_serializer[1]->getNum_packet(), packet_serializer[2]->getNum_packet());  
    
    packet_serializer_internal->print_info();
    packet_serializer[0]->print_info();
    packet_serializer[1]->print_info();
    packet_serializer[2]->print_info();
    */	   
    
    
    //#]
}

void Device::reinit_(int l_bw, int m_bw, int n_ser) {
    //#[ operation reinit_(int,int,int)
    if(DEBUG) printf("Device %s initialize ...\n", name);
    for (int i=0; i<3; i++)
    {
    	pending_packets_priority[i] = 0;	    
    	load_count_priority[i] = 0;	
    }
    load_count_total = 0;	
    
    if (rx_priority_queue)
    	rx_priority_queue->reinit();                             
    
    if (tx_priority_queue)
    	tx_priority_queue->reinit();     
    	
    if (itsPriorityVOQueue)
    	itsPriorityVOQueue->reinit();  
    	
                          
    
    char name_[40];
    
    for (int i=0; i<32; i++)
    {
    	sprintf(name_, "device_serilizer_%d",i);
        if(packet_serializer[i]==0)
        	packet_serializer[i] = new Serializer(l_bw, sim_param.link_delay, name_, sim_param.clocks_per_usec);  	
        packet_serializer[i]->reinit(l_bw, sim_param.link_delay, name_);   
    }
    
    
    
    sprintf(name_, "device_switch_serilizer");      
    if(switch_serializer==0)
    	switch_serializer = new Serializer(l_bw, sim_param.link_delay, name_, sim_param.clocks_per_usec); 
    switch_serializer->reinit(l_bw, sim_param.link_delay, name_);   
    
    sprintf(name_, "device_internal_serilizer");
    packet_serializer_internal->reinit(m_bw, 0, name_);   
    sim_param.max_num_pkt_serialize = n_ser;     
    
    if(DEBUG) print_info();
    
    //#]
}

void Device::send_response(Packet* p_pkt, int clk) {
    //#[ operation send_response(Packet,int)
    
    if (p_pkt == 0)
    {
    	printf("SW ERROR null pkt in %s %s line %d \n",__FILE__, __FUNCTION__, __LINE__);
    } 
    
    int s_idx, d_idx, c_idx;
    s_idx=p_pkt->getApp_id();
    d_idx=p_pkt->getDevice_id(); 
    c_idx=ConnMap::find_conn_map_index(s_idx, d_idx);
    ConnMap * p_conn_map = getItsConnMap(c_idx);
    if (p_conn_map == 0)
    {
    	printf("SW ERROR no p_conn_map in device for c_idx %d in %s %s line %d \n",c_idx, __FILE__, __FUNCTION__, __LINE__);
    	p_pkt->print_info();
    } 
    
    char s_name[20], d_name[20], sw_name[20];
    p_conn_map->copyNames(s_name, d_name, sw_name);
    int pri = p_pkt->getPriority();
    	 	
    if (strcmp(sw_name, "none") == 0)
    {    
    	Application * p_app = getItsApplication(p_pkt->getApp_id());       
    	
    	
    	if(DEBUG) printf(">>>>>>>> %s sending response to app_id %d ... \n", name, p_app->getIndex());  
    	if (p_app==0)
    	{
    		printf("%s: SW ERROR no app found ... \n", name);
    		p_pkt->print_info();
    	}
    	p_app->receive_response(p_pkt, clk);   
    	pending_packets_priority[pri]--;
    }
    
    else
    { 
    	SwitchCxl * p_sw_cxl = find_cxl_switch(p_pkt);
    	p_sw_cxl->receive_packet_from_device(p_pkt, clk); 
    	pending_packets_priority[pri]--;                 
    	
    	if(DEBUG) printf(">>>>>>>> %s sending response to cxl switch ... \n", name);  
     	if(DEBUG) p_sw_cxl->print_info();
    	if(DEBUG) p_pkt->print_info();  
    }
    //#]
}

int Device::getPacket_serializer() const {
    int iter = 0;
    return iter;
}

Serializer* Device::getPacket_serializer_internal() const {
    return packet_serializer_internal;
}

PriorityPacketQueue* Device::getRx_priority_queue() const {
    return rx_priority_queue;
}

PriorityPacketQueue* Device::getTx_priority_queue() const {
    return tx_priority_queue;
}

std::map<int, Application*>::const_iterator Device::getItsApplication() const {
    std::map<int, Application*>::const_iterator iter;
    iter = itsApplication.begin();
    return iter;
}

std::map<int, Application*>::const_iterator Device::getItsApplicationEnd() const {
    return itsApplication.end();
}

void Device::clearItsApplication() {
    itsApplication.clear();
}

void Device::removeItsApplication(Application* p_Application) {
    std::map<int, Application*>::iterator pos = std::find_if(itsApplication.begin(), itsApplication.end(),OMValueCompare<const int,Application*>(p_Application));
    if (pos != itsApplication.end()) {
    	itsApplication.erase(pos);
    }
}

Application* Device::getItsApplication(int key) const {
    std::map<int, Application*>::const_iterator it = itsApplication.find(key);
    if (it != itsApplication.end())
    	return (*it).second;
    else
    	return NULL;
}

void Device::addItsApplication(int key, Application* p_Application) {
    itsApplication.insert(std::map<int, Application*>::value_type(key, p_Application));
}

void Device::removeItsApplication(int key) {
    itsApplication.erase(key);
}

void Device::cleanUpRelations() {
    {
        itsApplication.clear();
    }
    {
        itsConnMap.clear();
    }
    if(itsPriorityVOQueue != NULL)
        {
            itsPriorityVOQueue = NULL;
        }
    {
        itsSwitchCxl.clear();
    }
    {
        itsSwitchOptics.clear();
    }
    
    if(packet_serializer_internal != NULL)
        {
            packet_serializer_internal = NULL;
        }
    if(rx_priority_queue != NULL)
        {
            rx_priority_queue = NULL;
        }
    if(tx_priority_queue != NULL)
        {
            tx_priority_queue = NULL;
        }
}

Device::Device(char* name_, int idx_, const SimParam_struct& s_p) : link_bw_gbps_(10), mem_bw_gbps_(10), itsApplication(), max_num_pkt_in_serializer_(2), itsConnMap(), itsSwitchCxl(), itsSwitchOptics() {
    tx_priority_queue = NULL;
    rx_priority_queue = NULL;
    packet_serializer_internal = NULL;
    {
        for (int pos = 0; pos < 32; pos++) {
        	packet_serializer[pos] = NULL;
        }
    }
    itsPriorityVOQueue = NULL;
    //#[ operation Device(char*,int,SimParam_struct)
    
    sprintf(name, "%s", name_); 
    sim_param = s_p;  
    index = idx_; 
    
    char n[40];
                        
    
    
    sprintf(n,"%s_internal_serial", name_);
    packet_serializer_internal = new Serializer (sim_param.mem_bw_mbps, 0, n, sim_param.clocks_per_usec);
    //packet_serializer_internal->setBw_gbps(mem_bw_gbps_);  
    //packet_serializer_internal->setProp_delay(0);     
    
    for (int i=0; i<32; i++)
    {
    	app_idx_to_dest_port[i] = -1;  
    	voq_to_dest_port[i] = -1;
    	dest_port_to_voq[i] = -1;
    }
    
        
    num_connected_app = 0;     
               
                        
    //if (IsMultiReturnLinks)
    {
    	sprintf(n,"%s_priority_voq", name_);
    	itsPriorityVOQueue = new PriorityVOQueue(n, num_connected_app);
    }
    //else
    {
    	sprintf(n,"%s_single_link_serial", name_);
    	switch_serializer = new Serializer (sim_param.link_bw_mbps, 0, n, sim_param.clocks_per_usec);    
    	//switch_serializer->setBw_gbps(link_bw_gbps_);
    	rx_priority_queue = new PriorityPacketQueue;
    	sprintf(n,"%s_rx_priority_queue", name_);
    	rx_priority_queue->set_name_string(n);
    	
    	tx_priority_queue = new PriorityPacketQueue;
    	sprintf(n,"%s_tx_priority_queue", name_);
    	tx_priority_queue->set_name_string(n);    
    } 
    
    
    sprintf(n,"%s_internal_serial", name_);
    packet_serializer_internal = new Serializer (sim_param.mem_bw_mbps, 0, n, sim_param.clocks_per_usec);
    //packet_serializer_internal->setBw_gbps(mem_bw_gbps_);  
    //packet_serializer_internal->setProp_delay(0);     
    
    
    
    //#]
}

SwitchCxl* Device::find_cxl_switch(Packet * p_pkt) {
    //#[ operation find_cxl_switch(Packet)
    
    int c_idx = ConnMap::find_conn_map_index(p_pkt->getApp_id(), p_pkt->getDevice_id());
    ConnMap * conn_map = getItsConnMap(c_idx);
    
    SwitchCxl * p_sw_cxl = getItsSwitchCxl(conn_map->getSwitch_idx());
    return p_sw_cxl; 	
    //#]
}

Packet* Device::generate_load_update_packet() {
    //#[ operation generate_load_update_packet()
    
    Packet * p_pkt = new Packet;
    
    p_pkt->setLoad_updated(1);
    for (int i=0; i<3; i++)
    { 
    	int updated_load = 0;
    	if (load_count_total)
    		updated_load = 100*load_count_priority[i]/load_count_total;
    
    	p_pkt->setUpdated_load(i, updated_load);
    }
    
    p_pkt->setType(LoadControl);
    p_pkt->setSize(sim_param.flit_size);
    return p_pkt;
    
    //#]
}

void Device::init_conn_interface() {
    //#[ operation init_conn_interface()
    //if (IsMultiReturnLinks)  
    char n[64];
    
    /*for (int i=0; i<num_connected_app; i++)
    {
    	sprintf(n,"%s_packet_serial_%d", name, i);
    	packet_serializer[i] = new Serializer(sim_param.link_bw_mbps, sim_param.link_delay, n, sim_param.clocks_per_usec);    
    }*/  
    
    if(DEBUG) printf("%s Intialize serializer \n", name);
    			
    for (int i=0; i<32 ; i++)
    {
    	if (app_idx_to_dest_port[i] != -1)
    	{
    		if (packet_serializer[app_idx_to_dest_port[i]] == 0)
    		{
    			sprintf(n,"%s_packet_serial_%d", name, i);
    			packet_serializer[app_idx_to_dest_port[i]] = new Serializer(sim_param.link_bw_mbps, sim_param.link_delay, n, sim_param.clocks_per_usec);    
    		}
    	}
    }      
      
    if(DEBUG) printf("%s Intialize Intialize Conn ... app to dest \n", name);
    int n_out = 0;
    for (int i=0; i<32 ; i++)
    {
    	int dest_port =  app_idx_to_dest_port[i];
    	if (dest_port == -1)
    		continue;
    	if (dest_port_to_voq[dest_port] == -1)
    	{
    		dest_port_to_voq[dest_port] = n_out;  
    		voq_to_dest_port[n_out] = dest_port;   
    		n_out ++;
    	}
    }  
    num_dest_port = n_out;
    
    sprintf(n,"%s_priority_voq", name);
    if(DEBUG) printf("%s Intialize Conn ... Priority VoQ %s \n", name, n);
    itsPriorityVOQueue = new PriorityVOQueue(n, num_dest_port);   
    
     
    
    
    //#]
}

void Device::print_app_to_port_table() {
    //#[ operation print_app_to_port_table()
    printf("App to dest_port:");
    for (int i=0; i<32; i++)
    {
    	if (app_idx_to_dest_port[i] !=-1)
    		printf(" app:%d -> port:%d", i, app_idx_to_dest_port[i]);
    }
    printf("\n");
    
    //#]
}

void Device::print_dest_port_to_voq() {
    //#[ operation print_dest_port_to_voq()
    printf("dest_port to voq:");
    for (int i=0; i<32; i++)
    {
    	if (dest_port_to_voq[i] !=-1)
    		printf(" dest:%d -> voq:%d", i, dest_port_to_voq[i]);
    }
    printf("\n");
    
    //#]
}

void Device::print_info() {
    //#[ operation print_info()
    printf("%s dev_idx:%d num_connected_app:%d, num_dest_port:%d \n", name, index, num_connected_app, num_dest_port);
    print_sim_param(sim_param);
    //printf("   update_interval:%d, link_bw:%d, mem_bw:%d max_num_pkt_in_serializer:%d\n", sim_param.load_update_interval, sim_param.link_bw_mbps, sim_param.mem_bw_mbps, sim_param.max_num_pkt_serialize);
    
    packet_serializer_internal->print_info();
    
    printf("   Print Priority VoQ \n");
    itsPriorityVOQueue->print_info();
    for (int i=0; i<num_connected_app; i++)
    {
    	printf("%s print packet serializer %d num_connected_app %d\n", name, i, num_connected_app);
    	if(packet_serializer[i])
    		packet_serializer[i]->print_info();
    }    
    
    print_app_to_port_table();     
    print_dest_port_to_voq(); 
    print_voq_to_dest_port();
    
    /*if (IsMultiReturnLinks)
    {
    	printf("print Priority VoQ \n");
    	itsPriorityVOQueue->print_info();
    	for (int i=0; i<num_connected_app; i++)
    	{
    		printf("%s print packet serializer %d num_connected_app %d\n", name, i, num_connected_app);
    		if(packet_serializer[i])
    			packet_serializer[i]->print_info();
    	}
    }
    else
    {   
        rx_priority_queue->print_info();
    	tx_priority_queue->print_info();
    	switch_serializer->print_info();
    } */                                                                  
    //#]
}

void Device::print_info_simple() {
    //#[ operation print_info_simple()
    
    //printf("%s dev_idx:%d update_interval:%d, link_bw:%d, mem_bw:%d max_num_pkt_in_serializer:%d\n", name, index, sim_param.load_update_interval, sim_param.link_bw_mbps, sim_param.mem_bw_mbps, sim_param.max_num_pkt_serialize);
    printf("print Priority VoQ \n");
    itsPriorityVOQueue->print_info_simple(); 
    
    for (int i=0; i<32; i++)
    {
    	if(packet_serializer[i]->getNum_packet() > 0)
    		printf(" output:%d has %d packets\n", i, packet_serializer[i]->getNum_packet());
    } 
    
    //print_app_to_port_table(); 
    //print_dest_port_to_voq();  
    //print_voq_to_dest_port();
                                                                
    //#]
}

void Device::print_sim_param(const SimParam_struct& s_) {
    //#[ operation print_sim_param(SimParam_struct)
    printf("Simulation Parameters \n");
    printf("  num_priority:%d, num_app:%d, num_device:%d, num_switch_cxl:%d, num_switch_optics:%d\n",
    		  s_.num_priority, s_.num_app, s_.num_device, s_.num_switch_cxl, s_.num_switch_optics);
    printf("  th_high:%d, th_mid:%d, th_low:%d, delta_severe:%d, delta_normal:%d, window_size:%d\n",
    		  s_.th_high, s_.th_mid, s_.th_low, s_.delta_severe, s_.delta_normal, s_.window_size);
    printf("  flit_size:%d, reqs_per_flit:%d, clocks_per_usec:%d\n",
    		  s_.flit_size, s_.reqs_per_flit, s_.clocks_per_usec);
    printf("  link_delay:%d, link_bw_mbps:%d, link_clock_per_flit:%d, link_clock_per_req:%d\n",
    		  s_.link_delay, s_.link_bw_mbps, s_.link_clock_per_flit, s_.link_clock_per_req);
    
    printf("  mem_bw_mbps:%d, mem_clock_per_req:%d, mem_clock_per_flit:%d\n",
    		  s_.mem_bw_mbps, s_.mem_clock_per_req, s_.mem_clock_per_flit);
    printf("  load_update_interval:%d, load_update_queue:%d, resp_link_check:%d, max_num_pkt_serialize:%d\n",
    		  s_.load_update_interval, s_.load_update_queue, s_.resp_link_check, s_.max_num_pkt_serialize);
    printf("  max_sim_clock:%d, file_size:%d, load:%d\n",
    		  s_.max_sim_clock, s_.file_size, s_.load);
    		  
    //#]
}

void Device::print_voq_to_dest_port() {
    //#[ operation print_voq_to_dest_port()
    printf("voq to dest_port:");
    for (int i=0; i<32; i++)
    {
    	if (voq_to_dest_port[i] !=-1)
    		printf(" voq:%d -> dest_port:%d", i, voq_to_dest_port[i]);
    }
    printf("\n");
    
    //#]
}

void Device::process_clock(int clk) {
    //#[ operation process_clock(int)
    /*if (IsMultiReturnLinks)   
    {
    	if (DEBUG) printf("%s: multi link clock prossing ... \n", name);
    	process_clock_multi_links(clk);
    }
    else
    {
    	if (DEBUG) printf("%s: single link clock prossing ... \n", name);
    	process_clock_single_link(clk);
    }*/                             
    
    process_clock_flex(clk);
     
    //#]
}

void Device::process_clock_flex(int clk) {
    //#[ operation process_clock_flex(int)
    Packet * p_pkt, p_pkt2;     
    
    //printf("%s: process clock multi link  \n", name);
    
    if(DEBUG) printf("%s: process clock flex initial check complete ... \n", name);
    
    if (IsThrottled && clk%sim_param.link_clock_per_flit ==0)
    {
    	//itsPriorityVOQueue->update_load_count(clk);
    	update_load_count();     
    }
    
    if(DEBUG) printf("%s: process clock flex - update rx queue load count complete ... \n", name);
    
    if (IsThrottled && clk%sim_param.load_update_interval == 0)
    { 
    	if(DEBUG) printf("%s: generate load update packet ... \n", name);
    	
    	for (int i=0; i<32; i++)
    	{ 
    		if (app_idx_to_dest_port[i] == -1)
    			continue;	
    		int d_port = app_idx_to_dest_port[i];
    		
    		p_pkt = generate_load_update_packet();	  
    	    p_pkt->setApp_id(i); 
    	    p_pkt->setTime_created(clk);    
    	    p_pkt->setPriority(0);
    		p_pkt->setDevice_id(index);
    		
    		packet_serializer[d_port]->serialize_packet(p_pkt, clk);
    	}
    	reset_load_count(); 
    } 
    
    if(DEBUG) printf("%s: process clock flex - generate load update complete ... resp_link_check %d\n", name, sim_param.resp_link_check);
     
    if (itsPriorityVOQueue->getNum_packet() > 0 && packet_serializer_internal->getNum_packet()<2)//  && clk%MemClocksPerReq  == 0)
    {
    	// send the head to tx priority queue  
    	// tx_priority_queue->add_packet(p_pkt_pending->getPriority(), p_pkt);
    	// schedule next packet
    	p_pkt = 0;
    				
    	if (sim_param.resp_link_check)
    	{
    		for (int i=0; i<3; i++)
    		{
    			//int ii = 2-i;
    			int rr_pointer = itsPriorityVOQueue->getRr_pointer(i); 
    			if (itsPriorityVOQueue->get_num_packet_priority(i) == 0)
    			{
    				continue;
    			}
    						
    			for (int j=0; j<num_dest_port; j++)
    			{
    				int jj = (j+rr_pointer)%num_dest_port;  // jj is voq, dest_port can be found by voq_to_dest_port[jj]  
    				int dest_port = voq_to_dest_port[jj]; 
    				if (itsPriorityVOQueue->get_num_packet(i,jj) == 0 || packet_serializer[dest_port]->getNum_packet() > sim_param.max_num_pkt_serialize - 1)
    					continue; 
    				p_pkt = itsPriorityVOQueue->remove_packet(i,jj);
    				itsPriorityVOQueue->setRr_pointer(i, (jj+1)%num_dest_port);
    				break; 
    			}
    			if (p_pkt)
    			{
    				break;
    			}
    		}
     	}	
    	else
    	{
    		for (int i=0; i<3; i++)
    		{
    			if (itsPriorityVOQueue->get_num_packet_priority(i) == 0)
    			{
    				continue;
    			}
    
    			int rr_pointer = itsPriorityVOQueue->getRr_pointer(i);
    			for (int j=0; j<num_dest_port; j++)
    			{
    				
    				int jj = (j+rr_pointer)%num_dest_port;   
    				int dest_port = voq_to_dest_port[jj];
    				if (itsPriorityVOQueue->get_num_packet(i,jj) == 0 )
    					continue;
    			
    				if(DEBUG) printf("%s Before Clock Processing \n", name);
    				if(DEBUG) print_info_simple();
    				p_pkt = itsPriorityVOQueue->remove_packet(i,jj);
    				itsPriorityVOQueue->setRr_pointer(i, (jj+1)%num_dest_port);
    				break; 
    			}
    			if (p_pkt)
    			{
    				break;
    			}
    		}
    	}
    		
    	if (p_pkt)
    	{
            if(DEBUG) printf("\n %s: >>>>>>>> from priority to internal serializer\n", name);
    		if(DEBUG) p_pkt->print_info(); 
    		
    		p_pkt->setType(ReadResp);    
    		p_pkt->setSize(sim_param.flit_size); 
    		p_pkt->setTime_tx_internal(clk); 
    		packet_serializer_internal->serialize_packet(p_pkt, clk);
    	}
    	else
    	{
    		//printf("\n %s: !!!!!!!!!!! No Packet Selected at %d\n", name, clk);
    		//print_info();	
    	}  
    }
    
    
    if(DEBUG) printf("%s: process clock flex - internal serializer -> packet serializer ... MemClocksPerFlit:%d\n", name, sim_param.mem_clock_per_flit);
    if(sim_param.mem_clock_per_flit == 0)
    	printf("%s: SW ERROR MemClocksPerFlit not initialized ... %d\n", name, sim_param.mem_clock_per_flit);
    	
    if (clk%sim_param.mem_clock_per_flit == 0) //	&& !packet_serializer_internal->is_overflowed())
    {
    	p_pkt = packet_serializer_internal->get_front();  
    	if (p_pkt)
    	{
    		int app_id = p_pkt->getApp_id();
    		{ 
    			p_pkt = packet_serializer_internal->pop_completed_packet(clk); 
    			if (p_pkt)
    			{
                    if(DEBUG) p_pkt->print_info();
    				if (app_id != p_pkt->getApp_id())
    				{
    					printf("!!!!!!!!!!!SW Error invalid app_id expect:%d real:%d\n", app_id, p_pkt->getApp_id());
    				}
    				int dest_port = app_idx_to_dest_port[app_id];    
    				if(DEBUG) printf("\n %s: >>>>>>>> from internal to packet serializer dest_port %d\n", name, dest_port);
    				if(DEBUG) p_pkt->print_info();
    				packet_serializer[dest_port]->serialize_packet(p_pkt, clk);
    			}
    		}
    	}
    }                           
    
    if(DEBUG) printf("%s: process clock flex - packet serialize send response ... \n", name);
    
    if (clk%sim_param.link_clock_per_flit == 0) //	&& !packet_serializer_internal->is_overflowed())
    {
    	for (int i=0; i<32; i++)        // in tx side consider the priority as parallal links
    	{
    		if (app_idx_to_dest_port[i] == -1)
    			continue;
    		int dest_port = app_idx_to_dest_port[i]; 	 
    		if(DEBUG) printf("%s: app_idx %d to dest port %d ... num_connected_app %d \n", name, i, dest_port, num_connected_app);   
    		if(DEBUG) print_info_simple();
    		p_pkt = packet_serializer[dest_port]->pop_completed_packet(clk);
    		if (p_pkt)
    		{
    			if(DEBUG) printf(">>>>>>>  %s: process clock flex - send response ... \n", name);   
    			if(DEBUG) p_pkt->print_info();
    			
    			send_response(p_pkt, clk);  
    		}
    	} 
    }
    
    if(DEBUG) printf("%s: process clock multi link - complete ... \n", name);
     
    //#]
}

void Device::process_clock_single_link(int clk) {
    //#[ operation process_clock_single_link(int)
    Packet * p_pkt;     
    
    
    if (sim_param.mem_clock_per_flit == 0 && sim_param.link_clock_per_flit == 0)
    {
    	printf("!!!!!!!SW Error CRITICAL MemClocksPerFlit %d LinkClocksPerFlit %d \n", sim_param.mem_clock_per_flit, sim_param.link_clock_per_flit);
    }	
    
    
    if (clk%sim_param.link_clock_per_flit == 0)
    {
    	//tx_priority_queue->update_load_count(clk);  
    	update_load_count();      
    }
    
    ///////////////////////////////////////////////////////////////
    //
    //		insert load control packet to switch serializer
    //
    if (clk%sim_param.load_update_interval == 0)
    {
    	if(DEBUG) printf("%s: generate load update packet ... \n", name);
    	
    	for (int i=0; i<num_connected_app; i++)
    	{	
    		p_pkt = generate_load_update_packet();	  
    	    p_pkt->setApp_id(i); 
    	    p_pkt->setTime_created(clk);    
    	    p_pkt->setPriority(0);
    		p_pkt->setDevice_id(index);
    		
    		switch_serializer->serialize_packet(p_pkt, clk);
    	}
    	reset_load_count();
    	
    	
    	/*tx_priority_queue->update_load_stats(); 
    	
    	for (int i=0; i<num_app; i++)
    	{	
    		p_pkt = tx_priority_queue->generate_load_update_packet();	  
    		if (p_pkt == 0)
    			printf("!!!!!!!SW Error CRITICAL NULL Pkt \n");
    	    p_pkt->setApp_id(i);
    		p_pkt->setTime_created(clk);
    		switch_serializer->serialize_packet(p_pkt, clk);
    	}     
    	tx_priority_queue->reset_load_count(clk);*/
    }      
    
    
    
    
    
    ///////////////////////////////////////////////////////////////
    //
    //		Move pacekt from rxQ to internal serializer
    //
    if(DEBUG) printf("%s: Move pacekt from rxQ to internal serializer \n", name);
    
    //if (rx_priority_queue->getNum_packet() && packet_serializer_internal->getNum_packet() <  1 && clk%MemClocksPerReq == 0 ) //	&& !packet_serializer_internal->is_overflowed())
    if (rx_priority_queue->getNum_packet() && packet_serializer_internal->getNum_packet() <  2) //	&& !packet_serializer_internal->is_overflowed())
    {
    	// send the head to tx priority queue  
    	// tx_priority_queue->add_packet(p_pkt_pending->getPriority(), p_pkt);
    	// schedule next packet
    	//printf("rx remove packet at %d\n", clk);  
      
    	p_pkt = rx_priority_queue->remove_packet();
    	if (p_pkt == 0)      
    	{
    		printf("!!!!!!!!!!!SW Errot Num pkt pointer rx_priority queue \n");
    	}
    	//p_pkt->print_info();
    	//tx_priority_queue->print_info();     
      
    	p_pkt->setType(ReadResp);      
    	p_pkt->setSize(sim_param.flit_size);  
    	packet_serializer_internal->serialize_packet(p_pkt, clk);
    	//printf("After remove packet print rx queue at %d\n", clk);
    	//rx_priority_queue->print_info();   
    }
    
    
    ///////////////////////////////////////////////////////////////
    //
    //		Move pacekt from internal serializer to TX Q
    //
    if(DEBUG) printf("%s: Move pacekt from internal serializer to TX Q \n", name);
    
    //if (clk%MemClocksPerReq == 0 ) //	&& !packet_serializer_internal->is_overflowed())
    {
    	p_pkt = packet_serializer_internal->pop_completed_packet(clk);  
    	if (p_pkt)
    	{
        	
    		tx_priority_queue->add_packet(p_pkt->getPriority(), p_pkt);	    
    		//printf("%s: InternalBW:%d, LinkClkPerFlit:%d, LinkClkPerReq:%d, MemClkPerFlit:%d, MemClkPerReq:%d\n", 
    		//       name, packet_serializer_internal->getBw_mbps(), LinkClocksPerFlit, LinkClocksPerReq, MemClocksPerFlit, MemClocksPerReq);
    		//printf("%s: >>>>> After add  tx priority queue at %d\n", name, vGlobalClock);
    		//tx_priority_queue->print_info();
    
    	}
    }
    
    
    
    
    
    
    ///////////////////////////////////////////////////////////////
    //
    //		Move pacekt from TX Q to switch serializer
    //
    if(DEBUG) printf("%s: Move pacekt from TX Q to switch serializer \n", name);
    
    //if (clk%LinkClocksPerFlit == 0) //	&& !packet_serializer_internal->is_overflowed())
    {
    	if (tx_priority_queue->getNum_packet() > 0 && switch_serializer->getNum_packet() < sim_param.max_num_pkt_serialize)      
    	{ 
    		p_pkt = tx_priority_queue->remove_packet();   
    		//printf("%s: LinkClkPerFlit:%d, LinkClkPerReq:%d, MemClkPerFlit:%d, MemClkPerReq:%d\n", name, LinkClocksPerFlit, LinkClocksPerReq, MemClocksPerFlit, MemClocksPerReq);
    		//printf(" <<<< %s: After remove packet tx priority queue at %d\n", name, vGlobalClock);
    		//tx_priority_queue->print_info();
    
    		if (p_pkt == 0)   
    		{
    			printf("!!!!!!!!!!!SW Errot Num pkt pointer tx_priority queue \n");
    		}     
    		switch_serializer->serialize_packet(p_pkt, clk);   
    	}
    }     
    
    
    ///////////////////////////////////////////////////////////////
    //
    //		Move pacekt from switch serializer to Switch                  
    if(DEBUG) printf("%s: Send Response \n", name);
    
    //if (clk%LinkClocksPerFlit == 0) //	&& !packet_serializer_internal->is_overflowed())
    {
    	p_pkt = switch_serializer->pop_completed_packet(clk);
    	if (p_pkt)
    	{
    		send_response(p_pkt, clk);
    		//printf("%s: <<<< SEND RESPONSE to CXLSwitch tx remove packet at %d complete \n", name, clk);
    		//p_pkt->print_info();
    	}
    }
    
    
    
    
    
     
    //#]
}

void Device::receive_packet_flex(Packet* p_pkt, int clk) {
    //#[ operation receive_packet_flex(Packet,int)
    
    
    if(DEBUG) printf("%s: >>>> Receives packet at %d\n", name, clk);
    //p_pkt->print_info();
    
    if (p_pkt == 0)
    	std::cout << "SW ERROR 1111111" << ", in "<< __FILE__<<", "<<__FUNCTION__<<", "<<__LINE__<<std::endl;      
    
    
    
    //rx_priority_queue->print_info();
    
    if (p_pkt->getTime_created() > clk)
    {  
    	printf("SW ERROR !!!!! clk:%d LD receive packet ctreated:%d", clk, p_pkt->getTime_created());
    	p_pkt->print_info(); 
    }
    
    int output = dest_port_to_voq[app_idx_to_dest_port[p_pkt->getApp_id()]];
    int pri = p_pkt->getPriority();  
    
    if(DEBUG) printf("%s: Send to Priority VoQ Receives pri %d output %d\n", name, pri, output);
    if(DEBUG) p_pkt->print_info();
    if (output == -1)
    {
    	printf("SW ERROR !!!!! output %d \n", output);
    	print_info();
    }
    pending_packets_priority[pri]++; 
    if(DEBUG) printf("%s: increse num_packet for priority %d\n", name, pri);  
    itsPriorityVOQueue->add_packet(pri, output, p_pkt);
    if(DEBUG) printf("%s: Add packet to Priority VoQ Receives pri %d output %d\n", name, pri, output);
    
    
    //printf("%s: LinkClkPerFlit:%d, LinkClkPerReq:%d, MemClkPerFlit:%d, MemClkPerReq:%d\n", name, LinkClocksPerFlit, LinkClocksPerReq, MemClocksPerFlit, MemClocksPerReq);
    //printf("%s: After receive packet print rx priority queue at %d\n", name, vGlobalClock);
    //rx_priority_queue->print_info();
    //printf("%s: After receive packet print tx priority queue at %d\n", name, vGlobalClock);
    //tx_priority_queue->print_info();
    
    
    //#]
}

void Device::receive_packet_multi_link(Packet* p_pkt, int clk) {
    //#[ operation receive_packet_multi_link(Packet,int)
    
    
    if(DEBUG) printf("%s: >>>> Receives packet at %d\n", name, clk);
    //p_pkt->print_info();
    
    if (p_pkt == 0)
    	std::cout << "SW ERROR 1111111" << ", in "<< __FILE__<<", "<<__FUNCTION__<<", "<<__LINE__<<std::endl;      
    
    
    
    //rx_priority_queue->print_info();
    
    if (p_pkt->getTime_created() > clk)
    {  
    	printf("SW ERROR !!!!! clk:%d LD receive packet ctreated:%d", clk, p_pkt->getTime_created());
    	p_pkt->print_info(); 
    }
    
    int output = p_pkt->getApp_id();
    int pri = p_pkt->getPriority();   
    
    pending_packets_priority[pri]++; 
    
    itsPriorityVOQueue->add_packet(pri, output, p_pkt);
    
    
    //printf("%s: LinkClkPerFlit:%d, LinkClkPerReq:%d, MemClkPerFlit:%d, MemClkPerReq:%d\n", name, LinkClocksPerFlit, LinkClocksPerReq, MemClocksPerFlit, MemClocksPerReq);
    //printf("%s: After receive packet print rx priority queue at %d\n", name, vGlobalClock);
    //rx_priority_queue->print_info();
    //printf("%s: After receive packet print tx priority queue at %d\n", name, vGlobalClock);
    //tx_priority_queue->print_info();
    
    
    //#]
}

void Device::receive_packet_single_link(Packet* p_pkt, int clk) {
    //#[ operation receive_packet_single_link(Packet,int)
    
    
    //printf("%s: >>>> Receives packet at %d\n", name, vGlobalClock);
    //p_pkt->print_info();
    
    if (p_pkt == 0)
    	std::cout << "SW ERROR 1111111" << ", in "<< __FILE__<<", "<<__FUNCTION__<<", "<<__LINE__<<std::endl;      
    
    
    
    //rx_priority_queue->print_info();
    
    if (p_pkt->getTime_created() > clk)
    {  
    	printf("SW ERROR !!!!! clk:%d LD receive packet ctreated:%d", clk, p_pkt->getTime_created());
    	p_pkt->print_info(); 
    }
    
    rx_priority_queue->add_packet(p_pkt->getPriority(), p_pkt);   
    
    
    //printf("%s: LinkClkPerFlit:%d, LinkClkPerReq:%d, MemClkPerFlit:%d, MemClkPerReq:%d\n", name, LinkClocksPerFlit, LinkClocksPerReq, MemClocksPerFlit, MemClocksPerReq);
    //printf("%s: After receive packet print rx priority queue at %d\n", name, vGlobalClock);
    //rx_priority_queue->print_info();
    //printf("%s: After receive packet print tx priority queue at %d\n", name, vGlobalClock);
    //tx_priority_queue->print_info();
    
    
    //#]
}

void Device::reinit(const SimParam_struct& s_p) {
    //#[ operation reinit(SimParam_struct)
    if(DEBUG) printf("Device %s initialize ...\n", name);   
    sim_param = s_p;
    
    for (int i=0; i<3; i++)
    {
    	pending_packets_priority[i] = 0;	    
    	load_count_priority[i] = 0;	
    }
    load_count_total = 0;	
    
    if (rx_priority_queue)
    	rx_priority_queue->reinit();                             
    
    if (tx_priority_queue)
    	tx_priority_queue->reinit();     
    	
    if (itsPriorityVOQueue)
    	itsPriorityVOQueue->reinit();  
    	
                          
    
    char name_[40];
    
    for (int i=0; i<32; i++)
    {
    	sprintf(name_, "device_serilizer_%d",i);
        if(packet_serializer[i]==0)
        	packet_serializer[i] = new Serializer(sim_param.link_bw_mbps, sim_param.link_delay, name_, sim_param.clocks_per_usec);  	
        packet_serializer[i]->reinit(sim_param.link_bw_mbps, sim_param.link_delay, name_);   
    }
    
    
    
    sprintf(name_, "device_switch_serilizer");      
    if(switch_serializer==0)
    	switch_serializer = new Serializer(sim_param.link_bw_mbps, sim_param.link_delay, name_, sim_param.clocks_per_usec); 
    switch_serializer->reinit(sim_param.link_bw_mbps, sim_param.link_delay, name_);   
    
    sprintf(name_, "device_internal_serilizer");
    packet_serializer_internal->reinit(sim_param.mem_bw_mbps, 0, name_);    
    
    if(DEBUG) print_info();
    
    //#]
}

void Device::reset_load_count() {
    //#[ operation reset_load_count()
    for (int i=0; i<3; i++)
    {
    	load_count_priority[i] = 0;
    			
    }  
    load_count_total = 0;
    
    
    //#]
}

void Device::update_load_count() {
    //#[ operation update_load_count()
    int l_q = sim_param.load_update_queue;
    
    if (StrictPriority)
    {
    	if (pending_packets_priority[0] > l_q)
    		load_count_priority[0]++;
    	if (pending_packets_priority[0] > l_q || pending_packets_priority[1] > l_q)
    		load_count_priority[1]++;
    	if (pending_packets_priority[0] > l_q || pending_packets_priority[1] > l_q || pending_packets_priority[2] > l_q)
    		load_count_priority[2]++;
    }
    else
    {
    	if (pending_packets_priority[0] > l_q)
    		load_count_priority[0]++;
    	if (pending_packets_priority[1] > l_q)
    		load_count_priority[1]++;
    	if (pending_packets_priority[2] > l_q)
    		load_count_priority[2]++;
    }
    
    load_count_total++;           
    
    
    
    //#]
}

int Device::getApp_idx_to_dest_port(int i1) const {
    return app_idx_to_dest_port[i1];
}

void Device::setApp_idx_to_dest_port(int i1, int p_app_idx_to_dest_port) {
    app_idx_to_dest_port[i1] = p_app_idx_to_dest_port;
}

int Device::getDest_port_to_voq(int i1) const {
    return dest_port_to_voq[i1];
}

void Device::setDest_port_to_voq(int i1, int p_dest_port_to_voq) {
    dest_port_to_voq[i1] = p_dest_port_to_voq;
}

int Device::getFlit_size_() const {
    return flit_size_;
}

void Device::setFlit_size_(int p_flit_size_) {
    flit_size_ = p_flit_size_;
}

int Device::getInterval_update_load_() const {
    return interval_update_load_;
}

void Device::setInterval_update_load_(int p_interval_update_load_) {
    interval_update_load_ = p_interval_update_load_;
}

int Device::getLink_bw_gbps_() const {
    return link_bw_gbps_;
}

void Device::setLink_bw_gbps_(int p_link_bw_gbps_) {
    link_bw_gbps_ = p_link_bw_gbps_;
}

int Device::getLink_prop_delay_() const {
    return link_prop_delay_;
}

void Device::setLink_prop_delay_(int p_link_prop_delay_) {
    link_prop_delay_ = p_link_prop_delay_;
}

int Device::getLoad_count_priority(int i1) const {
    return load_count_priority[i1];
}

void Device::setLoad_count_priority(int i1, int p_load_count_priority) {
    load_count_priority[i1] = p_load_count_priority;
}

int Device::getLoad_count_total() const {
    return load_count_total;
}

void Device::setLoad_count_total(int p_load_count_total) {
    load_count_total = p_load_count_total;
}

int Device::getMax_num_pkt_in_serializer_() const {
    return max_num_pkt_in_serializer_;
}

void Device::setMax_num_pkt_in_serializer_(int p_max_num_pkt_in_serializer_) {
    max_num_pkt_in_serializer_ = p_max_num_pkt_in_serializer_;
}

int Device::getMem_bw_gbps_() const {
    return mem_bw_gbps_;
}

void Device::setMem_bw_gbps_(int p_mem_bw_gbps_) {
    mem_bw_gbps_ = p_mem_bw_gbps_;
}

int Device::getNum_connected_app() const {
    return num_connected_app;
}

void Device::setNum_connected_app(int p_num_connected_app) {
    num_connected_app = p_num_connected_app;
}

int Device::getNum_dest_port() const {
    return num_dest_port;
}

void Device::setNum_dest_port(int p_num_dest_port) {
    num_dest_port = p_num_dest_port;
}

int Device::getPending_packets_priority(int i1) const {
    return pending_packets_priority[i1];
}

void Device::setPending_packets_priority(int i1, int p_pending_packets_priority) {
    pending_packets_priority[i1] = p_pending_packets_priority;
}

SimParam_struct Device::getSim_param() const {
    return sim_param;
}

void Device::setSim_param(SimParam_struct p_sim_param) {
    sim_param = p_sim_param;
}

Serializer* Device::getSwitch_serializer() const {
    return switch_serializer;
}

void Device::setSwitch_serializer(Serializer* p_switch_serializer) {
    switch_serializer = p_switch_serializer;
}

int Device::getVoq_to_dest_port(int i1) const {
    return voq_to_dest_port[i1];
}

void Device::setVoq_to_dest_port(int i1, int p_voq_to_dest_port) {
    voq_to_dest_port[i1] = p_voq_to_dest_port;
}

std::map<int, ConnMap*>::const_iterator Device::getItsConnMap() const {
    std::map<int, ConnMap*>::const_iterator iter;
    iter = itsConnMap.begin();
    return iter;
}

std::map<int, ConnMap*>::const_iterator Device::getItsConnMapEnd() const {
    return itsConnMap.end();
}

void Device::clearItsConnMap() {
    itsConnMap.clear();
}

void Device::removeItsConnMap(ConnMap* p_ConnMap) {
    std::map<int, ConnMap*>::iterator pos = std::find_if(itsConnMap.begin(), itsConnMap.end(),OMValueCompare<const int,ConnMap*>(p_ConnMap));
    if (pos != itsConnMap.end()) {
    	itsConnMap.erase(pos);
    }
}

ConnMap* Device::getItsConnMap(int key) const {
    std::map<int, ConnMap*>::const_iterator it = itsConnMap.find(key);
    if (it != itsConnMap.end())
    	return (*it).second;
    else
    	return NULL;
}

void Device::addItsConnMap(int key, ConnMap* p_ConnMap) {
    itsConnMap.insert(std::map<int, ConnMap*>::value_type(key, p_ConnMap));
}

void Device::removeItsConnMap(int key) {
    itsConnMap.erase(key);
}

PriorityVOQueue* Device::getItsPriorityVOQueue() const {
    return itsPriorityVOQueue;
}

void Device::setItsPriorityVOQueue(PriorityVOQueue* p_PriorityVOQueue) {
    itsPriorityVOQueue = p_PriorityVOQueue;
}

std::map<int, SwitchCxl*>::const_iterator Device::getItsSwitchCxl() const {
    std::map<int, SwitchCxl*>::const_iterator iter;
    iter = itsSwitchCxl.begin();
    return iter;
}

std::map<int, SwitchCxl*>::const_iterator Device::getItsSwitchCxlEnd() const {
    return itsSwitchCxl.end();
}

void Device::clearItsSwitchCxl() {
    itsSwitchCxl.clear();
}

void Device::removeItsSwitchCxl(SwitchCxl* p_SwitchCxl) {
    std::map<int, SwitchCxl*>::iterator pos = std::find_if(itsSwitchCxl.begin(), itsSwitchCxl.end(),OMValueCompare<const int,SwitchCxl*>(p_SwitchCxl));
    if (pos != itsSwitchCxl.end()) {
    	itsSwitchCxl.erase(pos);
    }
}

SwitchCxl* Device::getItsSwitchCxl(int key) const {
    std::map<int, SwitchCxl*>::const_iterator it = itsSwitchCxl.find(key);
    if (it != itsSwitchCxl.end())
    	return (*it).second;
    else
    	return NULL;
}

void Device::addItsSwitchCxl(int key, SwitchCxl* p_SwitchCxl) {
    itsSwitchCxl.insert(std::map<int, SwitchCxl*>::value_type(key, p_SwitchCxl));
}

void Device::removeItsSwitchCxl(int key) {
    itsSwitchCxl.erase(key);
}

std::map<int, SwitchOptics*>::const_iterator Device::getItsSwitchOptics() const {
    std::map<int, SwitchOptics*>::const_iterator iter;
    iter = itsSwitchOptics.begin();
    return iter;
}

std::map<int, SwitchOptics*>::const_iterator Device::getItsSwitchOpticsEnd() const {
    return itsSwitchOptics.end();
}

void Device::clearItsSwitchOptics() {
    itsSwitchOptics.clear();
}

void Device::removeItsSwitchOptics(SwitchOptics* p_SwitchOptics) {
    std::map<int, SwitchOptics*>::iterator pos = std::find_if(itsSwitchOptics.begin(), itsSwitchOptics.end(),OMValueCompare<const int,SwitchOptics*>(p_SwitchOptics));
    if (pos != itsSwitchOptics.end()) {
    	itsSwitchOptics.erase(pos);
    }
}

SwitchOptics* Device::getItsSwitchOptics(int key) const {
    std::map<int, SwitchOptics*>::const_iterator it = itsSwitchOptics.find(key);
    if (it != itsSwitchOptics.end())
    	return (*it).second;
    else
    	return NULL;
}

void Device::addItsSwitchOptics(int key, SwitchOptics* p_SwitchOptics) {
    itsSwitchOptics.insert(std::map<int, SwitchOptics*>::value_type(key, p_SwitchOptics));
}

void Device::removeItsSwitchOptics(int key) {
    itsSwitchOptics.erase(key);
}

void Device::addPacket_serializer(Serializer* p_Serializer) {
    for (int pos = 0; pos < 32; pos++) {
    	if (!packet_serializer[pos]) {
    		packet_serializer[pos] = p_Serializer;
    		break;
    	}
    }
}

void Device::removePacket_serializer(Serializer* p_Serializer) {
    for (int pos = 0; pos < 32; pos++) {
    	if (packet_serializer[pos] == p_Serializer) {
    		packet_serializer[pos] = NULL;
    	}
    }
}

void Device::clearPacket_serializer() {
}

void Device::setPacket_serializer_internal(Serializer* p_Serializer) {
    packet_serializer_internal = p_Serializer;
}

void Device::setRx_priority_queue(PriorityPacketQueue* p_PriorityPacketQueue) {
    rx_priority_queue = p_PriorityPacketQueue;
}

void Device::setTx_priority_queue(PriorityPacketQueue* p_PriorityPacketQueue) {
    tx_priority_queue = p_PriorityPacketQueue;
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/Device.cpp
*********************************************************************/
