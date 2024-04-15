/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: ODNetConfig
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/ODNetConfig.h
*********************************************************************/

#ifndef ODNetConfig_H
#define ODNetConfig_H

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
#include "Default.h"
//## package Default

//## class ODNetConfig
class ODNetConfig {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    ODNetConfig();
    
    //## auto_generated
    ~ODNetConfig();
    
    ////    Operations    ////
    
    //## operation init_connection()
    void init_connection();
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getConnection_map(int i1) const;
    
    //## auto_generated
    void setConnection_map(int i1, int p_connection_map);
    
    //## auto_generated
    int getNum_app_cpu() const;
    
    //## auto_generated
    void setNum_app_cpu(int p_num_app_cpu);
    
    //## auto_generated
    int getNum_device() const;
    
    //## auto_generated
    void setNum_device(int p_num_device);
    
    //## auto_generated
    int getSwitch_type() const;
    
    //## auto_generated
    void setSwitch_type(int p_switch_type);
    
    ////    Attributes    ////

protected :

    int connection_map[100];		//## attribute connection_map
    
    int num_app_cpu;		//## attribute num_app_cpu
    
    int num_device;		//## attribute num_device
    
    // 0: CXL Switch - single link in Device
    // 1: Optical Switch - multiple links in Device
    int switch_type;		//## attribute switch_type
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/ODNetConfig.h
*********************************************************************/
