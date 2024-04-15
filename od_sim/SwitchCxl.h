/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: SwitchCxl
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/SwitchCxl.h
*********************************************************************/

#ifndef SwitchCxl_H
#define SwitchCxl_H

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
#include <map>
//## auto_generated
#include <iterator>
//## auto_generated
#include <oxf/OMValueCompare.h>
//## link itsApplication
#include "Application.h"
//## link itsConnMap
#include "ConnMap.h"
//## link itsDevice
#include "Device.h"
//## class SwitchCxl
#include "ODSimElement.h"
//## auto_generated
#include "Default.h"
//## operation receive_packet_from_app(Packet,int)
class Packet;

//## attribute app_side_serializer
class Serializer;

//## package Default

//## class SwitchCxl
class SwitchCxl : public ODSimElement {
    ////    Constructors and destructors    ////
    
public :

    //## operation SwitchCxl(char*,int,int,int,int,int)
    SwitchCxl(char* n_, int bw, int pr_delay, int n_app, int n_dev, int c_us);
    
    //## auto_generated
    SwitchCxl();
    
    //## auto_generated
    ~SwitchCxl();
    
    ////    Operations    ////
    
    //## operation print_info()
    void print_info();
    
    //## operation process_clock(int)
    void process_clock(int clk);
    
    //## operation receive_packet_from_app(Packet,int)
    void receive_packet_from_app(Packet* p_pkt, int clk);
    
    //## operation receive_packet_from_device(Packet,int)
    void receive_packet_from_device(Packet* p_pkt, int clk);
    
    //## operation reinit(int,int)
    void reinit(int n_app, int p_delay);
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getApp_idx_to_source_port(int i1) const;
    
    //## auto_generated
    void setApp_idx_to_source_port(int i1, int p_app_idx_to_source_port);
    
    //## auto_generated
    int getApp_side_serializer() const;
    
    //## auto_generated
    void setApp_side_serializer(Serializer* p_app_side_serializer);
    
    //## auto_generated
    int getClocks_per_usec() const;
    
    //## auto_generated
    void setClocks_per_usec(int p_clocks_per_usec);
    
    //## auto_generated
    int getDest_idx_to_dest_port_(int i1) const;
    
    //## auto_generated
    void setDest_idx_to_dest_port_(int i1, int p_dest_idx_to_dest_port_);
    
    //## auto_generated
    int getDevice_side_serializer() const;
    
    //## auto_generated
    void setDevice_side_serializer(Serializer* p_device_side_serializer);
    
    //## auto_generated
    int getNum_connected_app() const;
    
    //## auto_generated
    void setNum_connected_app(int p_num_connected_app);
    
    //## auto_generated
    int getNum_connected_device() const;
    
    //## auto_generated
    void setNum_connected_device(int p_num_connected_device);
    
    //## auto_generated
    int getSw_bw_gbps() const;
    
    //## auto_generated
    void setSw_bw_gbps(int p_sw_bw_gbps);
    
    //## auto_generated
    std::map<int, Application*>::const_iterator getItsApplication() const;
    
    //## auto_generated
    std::map<int, Application*>::const_iterator getItsApplicationEnd() const;
    
    //## auto_generated
    void clearItsApplication();
    
    //## auto_generated
    void removeItsApplication(Application* p_Application);
    
    //## auto_generated
    Application* getItsApplication(int key) const;
    
    //## auto_generated
    void addItsApplication(int key, Application* p_Application);
    
    //## auto_generated
    void removeItsApplication(int key);
    
    //## auto_generated
    std::map<int, ConnMap*>::const_iterator getItsConnMap() const;
    
    //## auto_generated
    std::map<int, ConnMap*>::const_iterator getItsConnMapEnd() const;
    
    //## auto_generated
    void clearItsConnMap();
    
    //## auto_generated
    void removeItsConnMap(ConnMap* p_ConnMap);
    
    //## auto_generated
    ConnMap* getItsConnMap(int key) const;
    
    //## auto_generated
    void addItsConnMap(int key, ConnMap* p_ConnMap);
    
    //## auto_generated
    void removeItsConnMap(int key);
    
    //## auto_generated
    std::map<int, Device*>::const_iterator getItsDevice() const;
    
    //## auto_generated
    std::map<int, Device*>::const_iterator getItsDeviceEnd() const;
    
    //## auto_generated
    void clearItsDevice();
    
    //## auto_generated
    void removeItsDevice(Device* p_Device);
    
    //## auto_generated
    Device* getItsDevice(int key) const;
    
    //## auto_generated
    void addItsDevice(int key, Device* p_Device);
    
    //## auto_generated
    void removeItsDevice(int key);

protected :

    //## auto_generated
    void cleanUpRelations();
    
    ////    Attributes    ////
    
    int app_idx_to_source_port[32];		//## attribute app_idx_to_source_port
    
    Serializer* app_side_serializer[32];		//## attribute app_side_serializer
    
    int clocks_per_usec;		//## attribute clocks_per_usec
    
    int dest_idx_to_dest_port_[32];		//## attribute dest_idx_to_dest_port_
    
    Serializer* device_side_serializer[32];		//## attribute device_side_serializer
    
    int num_connected_app;		//## attribute num_connected_app
    
    int num_connected_device;		//## attribute num_connected_device
    
    int sw_bw_gbps;		//## attribute sw_bw_gbps
    
    ////    Relations and components    ////
    
    std::map<int, Application*> itsApplication;		//## link itsApplication
    
    std::map<int, ConnMap*> itsConnMap;		//## link itsConnMap
    
    std::map<int, Device*> itsDevice;		//## link itsDevice
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/SwitchCxl.h
*********************************************************************/
