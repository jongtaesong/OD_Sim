/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: FlexODSim
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/FlexODSim.h
*********************************************************************/

#ifndef FlexODSim_H
#define FlexODSim_H

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
#include <iterator>
//## link itsApplication
#include "Application.h"
//## link itsDevice
#include "Device.h"
//## attribute net_conf
#include "ODNetConfig.h"
//## link itsSwitchCxl
#include "SwitchCxl.h"
//## auto_generated
#include <map>
//## auto_generated
#include <oxf/OMValueCompare.h>
//## link itsConnMap
#include "ConnMap.h"
//## link itsSwitchOptics
#include "SwitchOptics.h"
//## auto_generated
#include "Default.h"
//## package Default

//## class FlexODSim
class FlexODSim {
    ////    Constructors and destructors    ////
    
public :

    //## operation FlexODSim(int)
    FlexODSim(int n_app = 3);
    
    ////    Additional operations    ////
    
    //## auto_generated
    std::map<int, Application*>::const_iterator getItsApplication() const;
    
    //## auto_generated
    std::map<int, Application*>::const_iterator getItsApplicationEnd() const;
    
    //## auto_generated
    void removeItsApplication(Application* p_Application);
    
    //## auto_generated
    void clearItsApplication();

protected :

    //## auto_generated
    void cleanUpRelations();
    
    ////    Relations and components    ////
    
    std::map<int, Application*> itsApplication;		//## link itsApplication

public :

    //## operation print_statistics()
    void print_statistics();
    
    //## operation reinitialize(int,int)
    void reinitialize(int n_app, int max_rtt_delay);
    
    //## operation start_sim()
    void start_sim();
    
    //## auto_generated
    int getSim_clock() const;
    
    //## auto_generated
    void setSim_clock(int p_sim_clock);

protected :

    int sim_clock;		//## attribute sim_clock

public :

    //## auto_generated
    ODNetConfig* getNet_conf() const;
    
    //## auto_generated
    std::map<int, Device*>::const_iterator getItsDevice() const;
    
    //## auto_generated
    std::map<int, Device*>::const_iterator getItsDeviceEnd() const;
    
    //## auto_generated
    void removeItsDevice(Device* p_Device);
    
    //## auto_generated
    void clearItsDevice();

protected :

    ODNetConfig net_conf;		//## attribute net_conf
    
    std::map<int, Device*> itsDevice;		//## link itsDevice

public :

    //## auto_generated
    ~FlexODSim();
    
    //## operation calculateConfigParam()
    void calculateConfigParam();
    
    //## operation changeConnParam()
    void changeConnParam();
    
    //## operation changeSimParam()
    void changeSimParam();
    
    //## operation change_connection_load(int,int)
    void change_connection_load(int app_idx, int load);
    
    //## operation change_connection_priority(int,int)
    void change_connection_priority(int app_idx, int prio);
    
    //## operation createConnMap(ConnMap)
    void createConnMap(ConnMap* c_map);
    
    //## operation createConnection_CPU_MEM(ConnMap)
    void createConnection_CPU_MEM(ConnMap*& p_c_map);
    
    //## operation createODElement()
    void createODElement();
    
    //## operation findConfigParam(char*)
    void findConfigParam(char* conn_map_line);
    
    //## operation findConnMap(char*,ConnMap)
    void findConnMap(char* conn_map_line, ConnMap*& p_c_map);
    
    //## operation findIndex(char*)
    int findIndex(char* _name);
    
    //## operation findSimParam(char*)
    void findSimParam(char* conn_map_line);
    
    //## operation initialize()
    void initialize();
    
    //## operation print_all_conn_map()
    void print_all_conn_map();
    
    //## operation print_sim_param()
    void print_sim_param();
    
    //## operation print_sim_param(SimParam_struct)
    static void print_sim_param(const SimParam_struct& s_);
    
    //## operation run_sim()
    void run_sim();
    
    //## operation run_sim_batch_membw()
    void run_sim_batch_membw();
    
    //## operation run_sim_batch_win()
    void run_sim_batch_win();
    
    //## operation validate_conn_interface()
    void validate_conn_interface();
    
    //## operation validate_conn_map_pair(ConnMap,ConnMap)
    void validate_conn_map_pair(ConnMap* p_c_map_1, ConnMap* p_c_map_2);
    
    //## auto_generated
    int getLoad_delta() const;
    
    //## auto_generated
    void setLoad_delta(int p_load_delta);
    
    //## auto_generated
    int getLoad_max() const;
    
    //## auto_generated
    void setLoad_max(int p_load_max);
    
    //## auto_generated
    int getLoad_min() const;
    
    //## auto_generated
    void setLoad_min(int p_load_min);
    
    //## auto_generated
    int getMembw_delta() const;
    
    //## auto_generated
    void setMembw_delta(int p_membw_delta);
    
    //## auto_generated
    int getMembw_max() const;
    
    //## auto_generated
    void setMembw_max(int p_membw_max);
    
    //## auto_generated
    int getMembw_min() const;
    
    //## auto_generated
    void setMembw_min(int p_membw_min);
    
    //## auto_generated
    SimParam_struct getSim_param() const;
    
    //## auto_generated
    void setSim_param(SimParam_struct p_sim_param);
    
    //## auto_generated
    int getWin_delta() const;
    
    //## auto_generated
    void setWin_delta(int p_win_delta);
    
    //## auto_generated
    int getWin_max() const;
    
    //## auto_generated
    void setWin_max(int p_win_max);
    
    //## auto_generated
    int getWin_min() const;
    
    //## auto_generated
    void setWin_min(int p_win_min);
    
    //## auto_generated
    Application* getItsApplication(int key) const;
    
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
    Device* getItsDevice(int key) const;
    
    //## auto_generated
    void removeItsDevice(int key);
    
    //## auto_generated
    std::map<int, SwitchCxl*>::const_iterator getItsSwitchCxl() const;
    
    //## auto_generated
    std::map<int, SwitchCxl*>::const_iterator getItsSwitchCxlEnd() const;
    
    //## auto_generated
    void clearItsSwitchCxl();
    
    //## auto_generated
    void removeItsSwitchCxl(SwitchCxl* p_SwitchCxl);
    
    //## auto_generated
    SwitchCxl* getItsSwitchCxl(int key) const;
    
    //## auto_generated
    void addItsSwitchCxl(int key, SwitchCxl* p_SwitchCxl);
    
    //## auto_generated
    void removeItsSwitchCxl(int key);
    
    //## auto_generated
    std::map<int, SwitchOptics*>::const_iterator getItsSwitchOptics() const;
    
    //## auto_generated
    std::map<int, SwitchOptics*>::const_iterator getItsSwitchOpticsEnd() const;
    
    //## auto_generated
    void clearItsSwitchOptics();
    
    //## auto_generated
    void removeItsSwitchOptics(SwitchOptics* p_SwitchOptics);
    
    //## auto_generated
    SwitchOptics* getItsSwitchOptics(int key) const;
    
    //## auto_generated
    void addItsSwitchOptics(int key, SwitchOptics* p_SwitchOptics);
    
    //## auto_generated
    void removeItsSwitchOptics(int key);

protected :

    int load_delta;		//## attribute load_delta
    
    int load_max;		//## attribute load_max
    
    int load_min;		//## attribute load_min
    
    int membw_delta;		//## attribute membw_delta
    
    int membw_max;		//## attribute membw_max
    
    int membw_min;		//## attribute membw_min
    
    SimParam_struct sim_param;		//## attribute sim_param
    
    int win_delta;		//## attribute win_delta
    
    int win_max;		//## attribute win_max
    
    int win_min;		//## attribute win_min
    
    std::map<int, ConnMap*> itsConnMap;		//## link itsConnMap
    
    std::map<int, SwitchCxl*> itsSwitchCxl;		//## link itsSwitchCxl
    
    std::map<int, SwitchOptics*> itsSwitchOptics;		//## link itsSwitchOptics

public :

    //## auto_generated
    void addItsApplication(int key, Application* p_Application);
    
    //## auto_generated
    void addItsDevice(int key, Device* p_Device);
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/FlexODSim.h
*********************************************************************/
