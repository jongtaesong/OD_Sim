/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: ODSim
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/ODSim.h
*********************************************************************/

#ifndef ODSim_H
#define ODSim_H

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
//## auto_generated
#include <map>
//## auto_generated
#include <oxf/OMValueCompare.h>
//## auto_generated
#include "Default.h"
//## link itsFlexODSim
class FlexODSim;

//## link cxl_switch
class SwitchCxl;

//## package Default

//## class ODSim
class ODSim {
    ////    Constructors and destructors    ////
    
public :

    //## operation ODSim(int)
    ODSim(int n_app = 3);
    
    //## auto_generated
    ~ODSim();
    
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

    //## operation initialize(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int)
    void initialize(int* p_clk, int n_app, int load_update_interval, int flit_size, int clk_per_us, int max_rtt_delay, int lk_bw_mbps, int m_bw_mbps, int th_h, int th_m, int th_l, int delta_h, int delta_l, int reqs_flit, int wd_size, int lk_prop_delay);
    
    //## operation print_statistics()
    void print_statistics();
    
    //## operation reinitialize(int,int)
    void reinitialize(int n_app, int max_rtt_delay);
    
    //## operation start_sim()
    void start_sim();
    
    //## auto_generated
    int getNum_app() const;
    
    //## auto_generated
    void setNum_app(int p_num_app);
    
    //## auto_generated
    int getSim_clock() const;
    
    //## auto_generated
    void setSim_clock(int p_sim_clock);
    
    //## auto_generated
    int getSim_clock_max() const;
    
    //## auto_generated
    void setSim_clock_max(int p_sim_clock_max);

protected :

    int num_app;		//## attribute num_app
    
    int sim_clock;		//## attribute sim_clock
    
    int sim_clock_max;		//## attribute sim_clock_max

public :

    //## auto_generated
    SwitchCxl* getCxl_switch() const;
    
    //## auto_generated
    void setCxl_switch(SwitchCxl* p_SwitchCxl);
    
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
    int getNum_device() const;
    
    //## auto_generated
    void setNum_device(int p_num_device);
    
    //## auto_generated
    Application* getItsApplication(int key) const;
    
    //## auto_generated
    void removeItsApplication(int key);
    
    //## auto_generated
    Device* getItsDevice(int key) const;
    
    //## auto_generated
    void removeItsDevice(int key);
    
    //## auto_generated
    FlexODSim* getItsFlexODSim() const;
    
    //## auto_generated
    void setItsFlexODSim(FlexODSim* p_FlexODSim);

protected :

    int num_device;		//## attribute num_device
    
    SwitchCxl* cxl_switch;		//## link cxl_switch
    
    FlexODSim* itsFlexODSim;		//## link itsFlexODSim

public :

    //## auto_generated
    void addItsApplication(int key, Application* p_Application);
    
    //## auto_generated
    void addItsDevice(int key, Device* p_Device);
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/ODSim.h
*********************************************************************/
