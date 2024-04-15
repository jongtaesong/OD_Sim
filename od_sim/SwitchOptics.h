/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: SwitchOptics
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/SwitchOptics.h
*********************************************************************/

#ifndef SwitchOptics_H
#define SwitchOptics_H

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
//## class SwitchOptics
#include "ODSimElement.h"
//## auto_generated
#include "Default.h"
//## operation receive_packet_from_app(Packet,int)
class Packet;

//## package Default

//## class SwitchOptics
class SwitchOptics : public ODSimElement {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    SwitchOptics();
    
    //## auto_generated
    ~SwitchOptics();
    
    ////    Operations    ////
    
    //## operation print_info()
    void print_info();
    
    //## operation process_clock(int)
    void process_clock(int clk);
    
    //## operation receive_packet_from_app(Packet,int)
    void receive_packet_from_app(Packet* p_pkt, int clk);
    
    //## operation receive_packet_from_device(Packet,int)
    void receive_packet_from_device(Packet* p_pkt, int clk);
    
    //## operation reinit()
    void reinit();
    
    ////    Additional operations    ////
    
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
    
    ////    Relations and components    ////
    
    std::map<int, Application*> itsApplication;		//## link itsApplication
    
    std::map<int, ConnMap*> itsConnMap;		//## link itsConnMap
    
    std::map<int, Device*> itsDevice;		//## link itsDevice
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/SwitchOptics.h
*********************************************************************/
