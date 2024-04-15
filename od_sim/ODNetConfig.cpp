/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: ODNetConfig
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/ODNetConfig.cpp
*********************************************************************/

//## auto_generated
#include "ODNetConfig.h"
//## auto_generated
#include <iostream>
//## package Default

//## class ODNetConfig
ODNetConfig::ODNetConfig() : num_app_cpu(4), num_device(1), switch_type(1) {
}

ODNetConfig::~ODNetConfig() {
}

void ODNetConfig::init_connection() {
    //#[ operation init_connection()
    // when optical switch
    // all cpu send request to device 0
    if (switch_type == 0)
    { 
    	for (int i=0; i<num_device; i++)
    		for (int j=0; j<num_app_cpu; j++)
    		{
    			if (i==0)  // all cpu send request to device 0
    				connection_map[i*num_app_cpu+j] = 1;
    		    else
    		  		connection_map[i*num_app_cpu+j] = 0; 
    		}
    }
    	
    else if (switch_type == 1) 
    {
    	for (int i=0; i<num_device; i++)
    		for (int j=0; j<num_app_cpu; j++)
    		{
    				connection_map[i*num_app_cpu+j] = 1;
    		}
    }
    //#]
}

int ODNetConfig::getConnection_map(int i1) const {
    return connection_map[i1];
}

void ODNetConfig::setConnection_map(int i1, int p_connection_map) {
    connection_map[i1] = p_connection_map;
}

int ODNetConfig::getNum_app_cpu() const {
    return num_app_cpu;
}

void ODNetConfig::setNum_app_cpu(int p_num_app_cpu) {
    num_app_cpu = p_num_app_cpu;
}

int ODNetConfig::getNum_device() const {
    return num_device;
}

void ODNetConfig::setNum_device(int p_num_device) {
    num_device = p_num_device;
}

int ODNetConfig::getSwitch_type() const {
    return switch_type;
}

void ODNetConfig::setSwitch_type(int p_switch_type) {
    switch_type = p_switch_type;
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/ODNetConfig.cpp
*********************************************************************/
