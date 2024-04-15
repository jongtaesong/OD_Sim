/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: SwitchCxl
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/SwitchCxl.cpp
*********************************************************************/

//## auto_generated
#include "SwitchCxl.h"
//## operation receive_packet_from_app(Packet,int)
#include "Packet.h"
//## attribute app_side_serializer
#include "Serializer.h"
//## auto_generated
#include <iostream>
//## package Default

//## class SwitchCxl
SwitchCxl::SwitchCxl(char* n_, int bw, int pr_delay, int n_app, int n_dev, int c_us) : itsApplication(), itsConnMap(), itsDevice() {
    {
        for (int pos = 0; pos < 32; pos++) {
        	app_side_serializer[pos] = NULL;
        };
    }
    {
        for (int pos = 0; pos < 32; pos++) {
        	device_side_serializer[pos] = NULL;
        };
    }
    //#[ operation SwitchCxl(char*,int,int,int,int,int)
    sw_bw_gbps = bw;     
    num_connected_app = n_app;
    num_connected_device = n_dev;    
    clocks_per_usec = c_us;
    sprintf(name,"%s", n_);
    
    char name_[64];    
    if (n_app>32 || n_dev > 32)
    	printf("SW ERROT max 32 CPU or Device is allowed");    
    	
    for (int i=0; i<32; i++)
    {
    	if(DEBUG) printf("switch app side serializer %d intializing \n", i);
    	sprintf(name_,"%s_app_side_ser_%d",name, i);
    	app_side_serializer[i] = new Serializer(bw, pr_delay, name_, clocks_per_usec);     
    	// app_side_serializers[i]->setProp_delay(0);
    	if(DEBUG) app_side_serializer[i]->print_info();   
    	app_idx_to_source_port[i] = -1;  
    }
    
    for (int i=0; i<32; i++)
    {
    	if(DEBUG) printf("%s switch device side serializer %d intializing \n",name, i);
    	sprintf(name_,"%s_dev_side_ser_%d",name, i);
    	device_side_serializer[i] = new Serializer(bw, 0, name_, clocks_per_usec);
    	if(DEBUG) device_side_serializer[i]->print_info();
    	if(DEBUG) printf("switch device side serializer %d intialized \n", i);
    }	
    //#]
}

SwitchCxl::SwitchCxl() : itsApplication(), itsConnMap(), itsDevice() {
    {
        for (int pos = 0; pos < 32; pos++) {
        	app_side_serializer[pos] = NULL;
        };
    }
    {
        for (int pos = 0; pos < 32; pos++) {
        	device_side_serializer[pos] = NULL;
        };
    }
}

SwitchCxl::~SwitchCxl() {
    cleanUpRelations();
}

void SwitchCxl::print_info() {
    //#[ operation print_info()
    printf("%s index:%d cxl_switch bw_gbps:%d, num_app:%d, num_device:%d \n", name, index, sw_bw_gbps, num_connected_app, num_connected_device);
    
    for (int i=0; i<32; i++)
    {
    	if (app_idx_to_source_port[i] == -1)
    		continue;
    	printf("app_idx %d --> source_port %d\n", i, app_idx_to_source_port[i]); 
    }
    
    for (int i=0; i<num_connected_app; i++)
    	app_side_serializer[i]->print_info();
    
    for (int i=0; i<num_connected_device; i++)
    	device_side_serializer[i]->print_info();
    
    
    //#]
}

void SwitchCxl::process_clock(int clk) {
    //#[ operation process_clock(int)
    Packet * p_pkt;           
    
    
    //if (sim_param.link_clock_per_flit == 0)
    //{
    //	printf("!!!!!!!SW Error CRITICAL LinkClocksPerFlit %d \n",LinkClocksPerFlit);
    //}	
    //if (clk%LinkClocksPerFlit !=0 && clk%LinkClocksPerReq !=0)
    //{
    //	return;
    //}
    
    // printf(">>>>>>>>>>>> %s cxl switch process clock \n", name);	
        
    	
    for (int i=0; i<32; i++)        // in tx side consider the priority as parallal links
    {
    	/*int source_port = app_idx_to_source_port[i];
    	if (source_port == -1)
    		continue; 
    	*/
    	//printf(">>>>>>>>>>>>>>>>> check source %d source port %d \n", i, source_port); 
    	p_pkt = app_side_serializer[i]->pop_completed_packet(clk);
    	if (p_pkt)
    	{
    		Application * p_app = getItsApplication(p_pkt->getApp_id());       
    		if(DEBUG) printf("<<<<<<<<<<<<<<<<<<< %s send packet to source port %d at %d\n", name, i, clk);
    		if(DEBUG) p_pkt->print_info();
    		p_app->receive_response(p_pkt, clk);   
    	} 
    } 
    
    
    
    for (int i=0; i<32; i++)        // in tx side consider the priority as parallal links
    { 
    	/*int dest_port = dest_idx_to_dest_port[i]; 
    	if (dest_port == -1)
    		continue;
    	*/
    	//printf(">>>>>>>>>>>>>>>>> check dest %d dest port %d \n", i, dest_port); 
    	p_pkt = device_side_serializer[i]->pop_completed_packet(clk);    
    	if (p_pkt)
    	{   
    		int dev_id = p_pkt->getDevice_id();
    		Device * p_dev = getItsDevice(dev_id);
    		if(DEBUG) printf(">>>>>>>>>>>>>>>>> %s  send packet to dest port %d at %d\n", name, i, clk);
    		if(DEBUG) p_pkt->print_info();
    		p_dev->receive_packet(p_pkt, clk);      
    		//printf(">>>>>>>>>>>>>>>>> %s  send packet to DEVICE %d at %d\n", name, i, clk);
    		//printf("------------------ at %d switch send packets to device\n", clk);
    		//device_side_serializer->print_all_packets();
    		
    	}
    }                                                                     
    //#]
}

void SwitchCxl::receive_packet_from_app(Packet* p_pkt, int clk) {
    //#[ operation receive_packet_from_app(Packet,int)
    
    if (p_pkt == 0)
    	std::cout << "SW ERROR 1111111" << ", in "<< __FILE__<<", "<<__FUNCTION__<<", "<<__LINE__<<std::endl;      
    
    int dev_id = p_pkt->getDevice_id();
    int app_id = p_pkt->getApp_id();  
    
    int c_idx = ConnMap::find_conn_map_index(app_id, dev_id);
    ConnMap * p_conn_map = getItsConnMap(c_idx);
    
    if (p_conn_map == 0)
    	printf("SW ERROR SwitchCxl cannot find ConnMap for c_idx:%d\n", c_idx);
    
    int dest_port = p_conn_map->getSwitch_port_dest();
    
    if(DEBUG) printf(">>>>>>>>>>>>>>> %s:  cxl switch receive packet from app %d to dest port %d at %d \n", name, p_pkt->getApp_id(), dest_port, clk);
    if(DEBUG) p_pkt->print_info();
    //printf(">>>>>>>>>>>>>>> %s:  cxl switch receive packet from app %d to dest port %d at %d \n", name, p_pkt->getApp_id(), dest_port, clk);
    device_side_serializer[dest_port]->serialize_packet(p_pkt, clk);     
    //print_info();
    //p_pkt->print_info();
    
    
    //printf("%s:  switch receive packet from app at %d \n", name, clk);
    //device_side_serializer[dev_id]->print_all_packets();
    
    
    //#]
}

void SwitchCxl::receive_packet_from_device(Packet* p_pkt, int clk) {
    //#[ operation receive_packet_from_device(Packet,int)
    
    
    if (p_pkt == 0)
    	std::cout << "SW ERROR 1111111" << ", in "<< __FILE__<<", "<<__FUNCTION__<<", "<<__LINE__<<std::endl;      
    
    if(DEBUG) printf(">>>>>  SwitchCxl %s receive packet from device \n",name);  
    if(DEBUG) p_pkt->print_info();  
    
    
    //int dev_id = p_pkt->getDevice_id();  
    int src_id = p_pkt->getApp_id();  
    
    /*int c_idx = ConnMap::find_conn_map_index(src_id, dev_id);
    ConnMap * p_conn_map = getItsConnMap(c_idx);
    if (p_conn_map == 0)
    	printf("SW ERROR SwitchCxl cannot find ConnMap for c_idx:%d\n", c_idx);
    
    */
    int source_port = app_idx_to_source_port[src_id]; 
    // p_conn_map->print_info();
    
    if(p_pkt->getType() == LoadControl)
    {
    	if(DEBUG) printf(">>>>> num_app in SwitchCxl %d \n",num_connected_app);  
    	for (int i=0; i<32; i++)
    	{
    		if (app_idx_to_source_port[i] != -1)
    		{
    			Packet * p_pkt_cp = new Packet;
    			memcpy (p_pkt_cp, p_pkt, sizeof(Packet));
    			p_pkt_cp->setApp_id(i);   
    			int s_p_ = app_idx_to_source_port[i];
    			//p_pkt->print_info();
    			app_side_serializer[s_p_]->serialize_packet(p_pkt, clk);   
    		}
    	} 
    }
    else
    {
    	if(DEBUG) printf("<<<<<<<<<<<  %s:  cxl switch receive packet from device %d to source port %d at %d \n", name, p_pkt->getDevice_id(), source_port, clk);
    	if(DEBUG) p_pkt->print_info();   
    	
    	//printf("<<<<<<<<<<<  %s:  cxl switch receive packet from device %d to source port %d at %d \n", name, p_pkt->getDevice_id(), source_port, clk);
    	//print_info();
    	//p_pkt->print_info();   
    	
    	app_side_serializer[source_port]->serialize_packet(p_pkt, clk);
    } 
    
    
         
    
    //#]
}

void SwitchCxl::reinit(int n_app, int p_delay) {
    //#[ operation reinit(int,int)
    char name_[40];
    
    for (int i=0; i<32; i++)
    {
    	sprintf(name_,"sw_app_side_serializer_%d",i);
    	app_side_serializer[i]->reinit(sw_bw_gbps, p_delay, name_);   
    }
    
    for (int i=0; i<32; i++)
    {
    	sprintf(name_,"sw_device_side_serializer_%d", i); 
    	device_side_serializer[i]->reinit(sw_bw_gbps, p_delay, name_);
    }
    
    //#]
}

int SwitchCxl::getApp_idx_to_source_port(int i1) const {
    return app_idx_to_source_port[i1];
}

void SwitchCxl::setApp_idx_to_source_port(int i1, int p_app_idx_to_source_port) {
    app_idx_to_source_port[i1] = p_app_idx_to_source_port;
}

int SwitchCxl::getApp_side_serializer() const {
    int iter = 0;
    return iter;
}

void SwitchCxl::setApp_side_serializer(Serializer* p_app_side_serializer) {
    for (int pos = 0; pos < 32; pos++) {
    	if (!app_side_serializer[pos]) {
    		app_side_serializer[pos] = p_app_side_serializer;
    		break;
    	}
    }
}

int SwitchCxl::getClocks_per_usec() const {
    return clocks_per_usec;
}

void SwitchCxl::setClocks_per_usec(int p_clocks_per_usec) {
    clocks_per_usec = p_clocks_per_usec;
}

int SwitchCxl::getDest_idx_to_dest_port_(int i1) const {
    return dest_idx_to_dest_port_[i1];
}

void SwitchCxl::setDest_idx_to_dest_port_(int i1, int p_dest_idx_to_dest_port_) {
    dest_idx_to_dest_port_[i1] = p_dest_idx_to_dest_port_;
}

int SwitchCxl::getDevice_side_serializer() const {
    int iter = 0;
    return iter;
}

void SwitchCxl::setDevice_side_serializer(Serializer* p_device_side_serializer) {
    for (int pos = 0; pos < 32; pos++) {
    	if (!device_side_serializer[pos]) {
    		device_side_serializer[pos] = p_device_side_serializer;
    		break;
    	}
    }
}

int SwitchCxl::getNum_connected_app() const {
    return num_connected_app;
}

void SwitchCxl::setNum_connected_app(int p_num_connected_app) {
    num_connected_app = p_num_connected_app;
}

int SwitchCxl::getNum_connected_device() const {
    return num_connected_device;
}

void SwitchCxl::setNum_connected_device(int p_num_connected_device) {
    num_connected_device = p_num_connected_device;
}

int SwitchCxl::getSw_bw_gbps() const {
    return sw_bw_gbps;
}

void SwitchCxl::setSw_bw_gbps(int p_sw_bw_gbps) {
    sw_bw_gbps = p_sw_bw_gbps;
}

std::map<int, Application*>::const_iterator SwitchCxl::getItsApplication() const {
    std::map<int, Application*>::const_iterator iter;
    iter = itsApplication.begin();
    return iter;
}

std::map<int, Application*>::const_iterator SwitchCxl::getItsApplicationEnd() const {
    return itsApplication.end();
}

void SwitchCxl::clearItsApplication() {
    itsApplication.clear();
}

void SwitchCxl::removeItsApplication(Application* p_Application) {
    std::map<int, Application*>::iterator pos = std::find_if(itsApplication.begin(), itsApplication.end(),OMValueCompare<const int,Application*>(p_Application));
    if (pos != itsApplication.end()) {
    	itsApplication.erase(pos);
    }
}

Application* SwitchCxl::getItsApplication(int key) const {
    std::map<int, Application*>::const_iterator it = itsApplication.find(key);
    if (it != itsApplication.end())
    	return (*it).second;
    else
    	return NULL;
}

void SwitchCxl::addItsApplication(int key, Application* p_Application) {
    itsApplication.insert(std::map<int, Application*>::value_type(key, p_Application));
}

void SwitchCxl::removeItsApplication(int key) {
    itsApplication.erase(key);
}

std::map<int, ConnMap*>::const_iterator SwitchCxl::getItsConnMap() const {
    std::map<int, ConnMap*>::const_iterator iter;
    iter = itsConnMap.begin();
    return iter;
}

std::map<int, ConnMap*>::const_iterator SwitchCxl::getItsConnMapEnd() const {
    return itsConnMap.end();
}

void SwitchCxl::clearItsConnMap() {
    itsConnMap.clear();
}

void SwitchCxl::removeItsConnMap(ConnMap* p_ConnMap) {
    std::map<int, ConnMap*>::iterator pos = std::find_if(itsConnMap.begin(), itsConnMap.end(),OMValueCompare<const int,ConnMap*>(p_ConnMap));
    if (pos != itsConnMap.end()) {
    	itsConnMap.erase(pos);
    }
}

ConnMap* SwitchCxl::getItsConnMap(int key) const {
    std::map<int, ConnMap*>::const_iterator it = itsConnMap.find(key);
    if (it != itsConnMap.end())
    	return (*it).second;
    else
    	return NULL;
}

void SwitchCxl::addItsConnMap(int key, ConnMap* p_ConnMap) {
    itsConnMap.insert(std::map<int, ConnMap*>::value_type(key, p_ConnMap));
}

void SwitchCxl::removeItsConnMap(int key) {
    itsConnMap.erase(key);
}

std::map<int, Device*>::const_iterator SwitchCxl::getItsDevice() const {
    std::map<int, Device*>::const_iterator iter;
    iter = itsDevice.begin();
    return iter;
}

std::map<int, Device*>::const_iterator SwitchCxl::getItsDeviceEnd() const {
    return itsDevice.end();
}

void SwitchCxl::clearItsDevice() {
    itsDevice.clear();
}

void SwitchCxl::removeItsDevice(Device* p_Device) {
    std::map<int, Device*>::iterator pos = std::find_if(itsDevice.begin(), itsDevice.end(),OMValueCompare<const int,Device*>(p_Device));
    if (pos != itsDevice.end()) {
    	itsDevice.erase(pos);
    }
}

Device* SwitchCxl::getItsDevice(int key) const {
    std::map<int, Device*>::const_iterator it = itsDevice.find(key);
    if (it != itsDevice.end())
    	return (*it).second;
    else
    	return NULL;
}

void SwitchCxl::addItsDevice(int key, Device* p_Device) {
    itsDevice.insert(std::map<int, Device*>::value_type(key, p_Device));
}

void SwitchCxl::removeItsDevice(int key) {
    itsDevice.erase(key);
}

void SwitchCxl::cleanUpRelations() {
    {
        itsApplication.clear();
    }
    {
        itsConnMap.clear();
    }
    {
        itsDevice.clear();
    }
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/SwitchCxl.cpp
*********************************************************************/
