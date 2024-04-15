/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: ConnMap
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/ConnMap.h
*********************************************************************/

#ifndef ConnMap_H
#define ConnMap_H

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

//## class ConnMap
class ConnMap {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    ConnMap();
    
    //## auto_generated
    ~ConnMap();
    
    ////    Operations    ////
    
    //## operation copyNames(char*,char*,char*)
    void copyNames(char* m_name, char* s_name, char* sw_name);
    
    //## operation find_conn_map_index()
    int find_conn_map_index();
    
    //## operation find_conn_map_index(int,int)
    static int find_conn_map_index(int s_idx, int d_idx);
    
    //## operation find_set_conn_map_index()
    int find_set_conn_map_index();
    
    //## operation print_info()
    void print_info();
    
    //## operation setNames(char*,char*)
    void setNames(char* m_name, char* s_name);
    
    //## operation setNames(char*,char*,char*)
    void setNames(char* s_name, char* sw_name, char* d_name);
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getBandwidth() const;
    
    //## auto_generated
    void setBandwidth(int p_bandwidth);
    
    //## auto_generated
    int getConn_map_index() const;
    
    //## auto_generated
    void setConn_map_index(int p_conn_map_index);
    
    //## auto_generated
    int getDest_idx() const;
    
    //## auto_generated
    void setDest_idx(int p_dest_idx);
    
    //## auto_generated
    char getDest_name(int i1) const;
    
    //## auto_generated
    void setDest_name(int i1, char p_dest_name);
    
    //## auto_generated
    int getDest_port() const;
    
    //## auto_generated
    void setDest_port(int p_dest_port);
    
    //## auto_generated
    int getPriority() const;
    
    //## auto_generated
    void setPriority(int p_priority);
    
    //## auto_generated
    int getSource_idx() const;
    
    //## auto_generated
    void setSource_idx(int p_source_idx);
    
    //## auto_generated
    char getSource_name(int i1) const;
    
    //## auto_generated
    void setSource_name(int i1, char p_source_name);
    
    //## auto_generated
    int getSource_port() const;
    
    //## auto_generated
    void setSource_port(int p_source_port);
    
    //## auto_generated
    int getSwitch_idx() const;
    
    //## auto_generated
    void setSwitch_idx(int p_switch_idx);
    
    //## auto_generated
    char getSwitch_name(int i1) const;
    
    //## auto_generated
    void setSwitch_name(int i1, char p_switch_name);
    
    //## auto_generated
    int getSwitch_port_dest() const;
    
    //## auto_generated
    void setSwitch_port_dest(int p_switch_port_dest);
    
    //## auto_generated
    int getSwitch_port_source() const;
    
    //## auto_generated
    void setSwitch_port_source(int p_switch_port_source);
    
    //## auto_generated
    int getValid() const;
    
    //## auto_generated
    void setValid(int p_valid);
    
    ////    Attributes    ////

protected :

    int bandwidth;		//## attribute bandwidth
    
    int conn_map_index;		//## attribute conn_map_index
    
    int dest_idx;		//## attribute dest_idx
    
    char dest_name[20];		//## attribute dest_name
    
    int dest_port;		//## attribute dest_port
    
    int priority;		//## attribute priority
    
    int source_idx;		//## attribute source_idx
    
    char source_name[20];		//## attribute source_name
    
    int source_port;		//## attribute source_port
    
    int switch_idx;		//## attribute switch_idx
    
    char switch_name[20];		//## attribute switch_name
    
    int switch_port_dest;		//## attribute switch_port_dest
    
    int switch_port_source;		//## attribute switch_port_source
    
    int valid;		//## attribute valid
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/ConnMap.h
*********************************************************************/
