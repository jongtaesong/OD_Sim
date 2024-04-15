/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: SwitchOptics
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/SwitchOptics.cpp
*********************************************************************/

//## auto_generated
#include "SwitchOptics.h"
//## operation receive_packet_from_app(Packet,int)
#include "Packet.h"
//## auto_generated
#include <iostream>
//## package Default

//## class SwitchOptics
SwitchOptics::SwitchOptics() : itsApplication(), itsConnMap(), itsDevice() {
}

SwitchOptics::~SwitchOptics() {
    cleanUpRelations();
}

void SwitchOptics::print_info() {
    //#[ operation print_info()
    printf("%s\n", name);
    
    //#]
}

void SwitchOptics::process_clock(int clk) {
    //#[ operation process_clock(int)
                                                                       
    //#]
}

void SwitchOptics::receive_packet_from_app(Packet* p_pkt, int clk) {
    //#[ operation receive_packet_from_app(Packet,int)
    
    
    
    //#]
}

void SwitchOptics::receive_packet_from_device(Packet* p_pkt, int clk) {
    //#[ operation receive_packet_from_device(Packet,int)
    //#]
}

void SwitchOptics::reinit() {
    //#[ operation reinit()
    //#]
}

std::map<int, Application*>::const_iterator SwitchOptics::getItsApplication() const {
    std::map<int, Application*>::const_iterator iter;
    iter = itsApplication.begin();
    return iter;
}

std::map<int, Application*>::const_iterator SwitchOptics::getItsApplicationEnd() const {
    return itsApplication.end();
}

void SwitchOptics::clearItsApplication() {
    itsApplication.clear();
}

void SwitchOptics::removeItsApplication(Application* p_Application) {
    std::map<int, Application*>::iterator pos = std::find_if(itsApplication.begin(), itsApplication.end(),OMValueCompare<const int,Application*>(p_Application));
    if (pos != itsApplication.end()) {
    	itsApplication.erase(pos);
    }
}

Application* SwitchOptics::getItsApplication(int key) const {
    std::map<int, Application*>::const_iterator it = itsApplication.find(key);
    if (it != itsApplication.end())
    	return (*it).second;
    else
    	return NULL;
}

void SwitchOptics::addItsApplication(int key, Application* p_Application) {
    itsApplication.insert(std::map<int, Application*>::value_type(key, p_Application));
}

void SwitchOptics::removeItsApplication(int key) {
    itsApplication.erase(key);
}

std::map<int, ConnMap*>::const_iterator SwitchOptics::getItsConnMap() const {
    std::map<int, ConnMap*>::const_iterator iter;
    iter = itsConnMap.begin();
    return iter;
}

std::map<int, ConnMap*>::const_iterator SwitchOptics::getItsConnMapEnd() const {
    return itsConnMap.end();
}

void SwitchOptics::clearItsConnMap() {
    itsConnMap.clear();
}

void SwitchOptics::removeItsConnMap(ConnMap* p_ConnMap) {
    std::map<int, ConnMap*>::iterator pos = std::find_if(itsConnMap.begin(), itsConnMap.end(),OMValueCompare<const int,ConnMap*>(p_ConnMap));
    if (pos != itsConnMap.end()) {
    	itsConnMap.erase(pos);
    }
}

ConnMap* SwitchOptics::getItsConnMap(int key) const {
    std::map<int, ConnMap*>::const_iterator it = itsConnMap.find(key);
    if (it != itsConnMap.end())
    	return (*it).second;
    else
    	return NULL;
}

void SwitchOptics::addItsConnMap(int key, ConnMap* p_ConnMap) {
    itsConnMap.insert(std::map<int, ConnMap*>::value_type(key, p_ConnMap));
}

void SwitchOptics::removeItsConnMap(int key) {
    itsConnMap.erase(key);
}

std::map<int, Device*>::const_iterator SwitchOptics::getItsDevice() const {
    std::map<int, Device*>::const_iterator iter;
    iter = itsDevice.begin();
    return iter;
}

std::map<int, Device*>::const_iterator SwitchOptics::getItsDeviceEnd() const {
    return itsDevice.end();
}

void SwitchOptics::clearItsDevice() {
    itsDevice.clear();
}

void SwitchOptics::removeItsDevice(Device* p_Device) {
    std::map<int, Device*>::iterator pos = std::find_if(itsDevice.begin(), itsDevice.end(),OMValueCompare<const int,Device*>(p_Device));
    if (pos != itsDevice.end()) {
    	itsDevice.erase(pos);
    }
}

Device* SwitchOptics::getItsDevice(int key) const {
    std::map<int, Device*>::const_iterator it = itsDevice.find(key);
    if (it != itsDevice.end())
    	return (*it).second;
    else
    	return NULL;
}

void SwitchOptics::addItsDevice(int key, Device* p_Device) {
    itsDevice.insert(std::map<int, Device*>::value_type(key, p_Device));
}

void SwitchOptics::removeItsDevice(int key) {
    itsDevice.erase(key);
}

void SwitchOptics::cleanUpRelations() {
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
	File Path	: DefaultComponent/DefaultConfig/SwitchOptics.cpp
*********************************************************************/
