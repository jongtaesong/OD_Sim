/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: ODSim
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/ODSim.cpp
*********************************************************************/

//## auto_generated
#include "ODSim.h"
//## auto_generated
#include <iostream>
//## link cxl_switch
#include "SwitchCxl.h"
//## link itsFlexODSim
#include "FlexODSim.h"
//## package Default

//## class ODSim
ODSim::ODSim(int n_app) : itsApplication(), num_app(1), itsDevice() {
    cxl_switch = NULL;
    itsFlexODSim = NULL;
    //#[ operation ODSim(int)
    //#]
}

ODSim::~ODSim() {
    cleanUpRelations();
}

std::map<int, Application*>::const_iterator ODSim::getItsApplication() const {
    std::map<int, Application*>::const_iterator iter;
    iter = itsApplication.begin();
    return iter;
}

std::map<int, Application*>::const_iterator ODSim::getItsApplicationEnd() const {
    return itsApplication.end();
}

void ODSim::removeItsApplication(Application* p_Application) {
    std::map<int, Application*>::iterator pos = std::find_if(itsApplication.begin(), itsApplication.end(),OMValueCompare<const int,Application*>(p_Application));
    if (pos != itsApplication.end()) {
    	itsApplication.erase(pos);
    }
}

void ODSim::clearItsApplication() {
    itsApplication.clear();
}

void ODSim::cleanUpRelations() {
    if(cxl_switch != NULL)
        {
            cxl_switch = NULL;
        }
    {
        itsApplication.clear();
    }
    {
        itsDevice.clear();
    }
    if(itsFlexODSim != NULL)
        {
            itsFlexODSim = NULL;
        }
}

void ODSim::initialize(int* p_clk, int n_app, int load_update_interval, int flit_size, int clk_per_us, int max_rtt_delay, int lk_bw_mbps, int m_bw_mbps, int th_h, int th_m, int th_l, int delta_h, int delta_l, int reqs_flit, int wd_size, int lk_prop_delay) {
    //#[ operation initialize(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int)
    char name[40];
    
    num_app = net_conf.getNum_app_cpu();    
    num_device = net_conf.getNum_device();      
    //IsMultiReturnLinks = net_conf.getSwitch_type();		// 0: CXL switch 1: Optical Switch with Multiple Link in device 
    
                                         
    std::cout <<"num_cpu: "<<num_app<<", num_device: "<<num_device<<std::endl;   
    //ClocksPerMicroSecond = clocks_per_micro_second;     
    
    for (int i=0; i<num_device; i++)
    {
    	sprintf(name, "device%d",i);
    	Device * p_device  = new Device(name, load_update_interval, lk_bw_mbps, m_bw_mbps, flit_size, lk_prop_delay, num_app);       // update interval 100
    	p_device->setIndex(i);   
    	p_device->setNum_connected_app(num_app);
    	addItsDevice(i, p_device);      
    } 
    
    for (int i=0; i<num_device; i++)
    {
    	Device * p_device  = getItsDevice(i);
    	if (p_device == 0)
    		printf("ERROR for device%d cannot retrieve - Null Pointer\n", i);
    	printf("Check device%d is added\n", i);
    } 
                                                        
    Application * p_app;                                                  
    printf("Initialize CPU ... \n");
    for (int i=0; i<num_app; i++)
    {
    	p_app = new Application (i, flit_size, clk_per_us, th_h, th_m, th_l, delta_h, delta_l, lk_bw_mbps, reqs_flit, wd_size, lk_prop_delay );   
    	
    	
    	//p_app->setPriority(i%3);
    	//p_app->setPriority(0);
    	if (i==num_app-1)
    		p_app->setPriority(1);
    	
    	p_app->setIndex(i);
    	sprintf(name, "app%d",i);
    	p_app->set_name_string(name);
    	p_app->reset_stats();
    	p_app->setNum_connected_dev(num_device);
    	
    	addItsApplication(i, p_app);    
    	//std::cout <<"app_id:"<<i<<std::endl;
    }
    
    printf("Initialize Device ... \n");
    for (int i=0; i<num_device; i++)
    	for (int j=0; j<num_app; j++)
    	{
            {
            	printf("device%d connect to cpu%d\n", i, j);        
    			Device * p_device  = getItsDevice(i);
    			Application * p_app = getItsApplication(j);  
    			if (p_device==0 || p_app==0)
    			{
    				printf("SW ERROR null point - dev%d or cpu%d not exist \n", i, j);
    				
    			}
    			p_device->addItsApplication(j, p_app);
    			p_app->addItsDevice(i, p_device);
    		}   
      	}
    
    
    printf("Initialize Connection ... \n");
    net_conf.init_connection();     
    
    // Initialize Switch       
    printf("Initialize switch ... \n");
    sprintf(name, "sw_cxl");

    cxl_switch = new SwitchCxl (name, lk_bw_mbps, lk_prop_delay, num_app, num_device, clk_per_us);
    
    printf("Setup App - Switch pointer ... \n");
    for (int i=0; i<num_app; i++)
    {
    	p_app = getItsApplication(i);
    	p_app->addItsSwitchCxl(0, cxl_switch);
    	cxl_switch->addItsApplication(p_app->getIndex(), p_app);
    }               
    
    printf("Setup Device - Switch pointer ... \n");
    for (int i=0; i<num_device; i++)
    {
    	Device * p_device = getItsDevice(i);  
    	if (p_device==0)
    	{
    		printf("SW ERROR null point - dev%d \n", i);
    	}
    	p_device->addItsSwitchCxl(0, cxl_switch);
        cxl_switch->addItsDevice(i, p_device);
    }
    printf("Initialization Complete .....  \n");     
    
    //#]
}

void ODSim::print_statistics() {
    //#[ operation print_statistics()
    fprintf(sim_result,"\n Delay Statistics \n");
    
    for (int i=0; i<1000; i++)
    {
    	if (delay_statistics[i] == 0)
    		continue;
    	fprintf(sim_result,"delay: %d occurs: %d \n", i, delay_statistics[i]);
    }        
    
    
    fprintf(sim_result,"\n RTT Delay Statistics \n");
    Application * p_app; 
    for (int i=0; i<num_app; i++)
    {
    	p_app = getItsApplication(i);
    	if (p_app==0)  
    		printf("SW ERROR null p_app %d\n", i);     
    	p_app->print_rtt_to_file(sim_result);
    } 
    
    /*
    std::list<Application*>::iterator p_app;    
    for (p_app = itsApplication.begin(); p_app != itsApplication.end(); ++p_app)
    {
    	if ((*p_app)==0)  
    		printf("SW ERROR null p_app\n");     
    	(*p_app)->print_rtt_to_file(sim_result);
    } 
    */  
     
    
    fprintf(sim_result,"\n Completion Time Statistics \n");	  
    for (int i=0; i<num_app; i++)
    {
    	p_app = getItsApplication(i);
    	if (p_app==0)  
    		printf("SW ERROR null p_app\n");     
    	fprintf(sim_result,"comp priority %d completion_time: %d \n", p_app->getPriority(), p_app->get_file_completion_time());
    }           
    
    
    
                                           
    
    
    //#]
}

void ODSim::reinitialize(int n_app, int max_rtt_delay) {
    //#[ operation reinitialize(int,int)
    Application * p_app;    
    for (int i=0; i<num_app; i++)
    {
    	p_app = getItsApplication(i);
    	if (p_app==0)  
    		printf("SW ERROR null p_app\n");     
    	p_app->reset_stats();
    }                                                
    //#]
}

void ODSim::start_sim() {
    //#[ operation start_sim()
    // define all simulation configuration
    FlexODSim * f_od_sim;
    char option[64];
    f_od_sim = new FlexODSim;
    f_od_sim->initialize();     
    
    char file_name[64];
    sprintf(file_name, "./output_file/Sim_Result_Summary.txt");
    sim_result2 = fopen(file_name, "w+");
    
    SimParam_struct s_pr = f_od_sim->getSim_param();
    fprintf(sim_result2, "clks/us %d\n", s_pr.clocks_per_usec);

     
    while (1)
    {
    	if (f_od_sim->getLoad_max() != 0 && f_od_sim->getWin_max())
    	{
    		f_od_sim->run_sim_batch_win(); 
    	}  
    	else if (f_od_sim->getLoad_max() != 0 && f_od_sim->getMembw_max())
    	{
    		f_od_sim->run_sim_batch_membw(); 
    	}
    	else
    	{
    		f_od_sim->run_sim(); 
    	}
    	
    	printf("Type   [0] to finish \n");
    	printf("   [Enter] to continue with other parameters \n");
    	//gets(option); 
    	fgets(option, sizeof(option), stdin); 
        option[strcspn(option,"\n")]=0;
    	
    	if (strcmp(option, "0") == 0)
    	{
    		break;
    	}
    	else
    	{
    		f_od_sim->changeSimParam();	
    	}
    } 
    
    
    fclose(sim_result2);
    
    printf("Simulation Completed!!!! \n");    
    exit(3);      
    
    
    
    //#]
}

int ODSim::getNum_app() const {
    return num_app;
}

void ODSim::setNum_app(int p_num_app) {
    num_app = p_num_app;
}

int ODSim::getSim_clock() const {
    return sim_clock;
}

void ODSim::setSim_clock(int p_sim_clock) {
    sim_clock = p_sim_clock;
}

int ODSim::getSim_clock_max() const {
    return sim_clock_max;
}

void ODSim::setSim_clock_max(int p_sim_clock_max) {
    sim_clock_max = p_sim_clock_max;
}

SwitchCxl* ODSim::getCxl_switch() const {
    return cxl_switch;
}

void ODSim::setCxl_switch(SwitchCxl* p_SwitchCxl) {
    cxl_switch = p_SwitchCxl;
}

ODNetConfig* ODSim::getNet_conf() const {
    return (ODNetConfig*) &net_conf;
}

std::map<int, Device*>::const_iterator ODSim::getItsDevice() const {
    std::map<int, Device*>::const_iterator iter;
    iter = itsDevice.begin();
    return iter;
}

std::map<int, Device*>::const_iterator ODSim::getItsDeviceEnd() const {
    return itsDevice.end();
}

void ODSim::removeItsDevice(Device* p_Device) {
    std::map<int, Device*>::iterator pos = std::find_if(itsDevice.begin(), itsDevice.end(),OMValueCompare<const int,Device*>(p_Device));
    if (pos != itsDevice.end()) {
    	itsDevice.erase(pos);
    }
}

void ODSim::clearItsDevice() {
    itsDevice.clear();
}

int ODSim::getNum_device() const {
    return num_device;
}

void ODSim::setNum_device(int p_num_device) {
    num_device = p_num_device;
}

Application* ODSim::getItsApplication(int key) const {
    std::map<int, Application*>::const_iterator it = itsApplication.find(key);
    if (it != itsApplication.end())
    	return (*it).second;
    else
    	return NULL;
}

void ODSim::removeItsApplication(int key) {
    itsApplication.erase(key);
}

Device* ODSim::getItsDevice(int key) const {
    std::map<int, Device*>::const_iterator it = itsDevice.find(key);
    if (it != itsDevice.end())
    	return (*it).second;
    else
    	return NULL;
}

void ODSim::removeItsDevice(int key) {
    itsDevice.erase(key);
}

FlexODSim* ODSim::getItsFlexODSim() const {
    return itsFlexODSim;
}

void ODSim::setItsFlexODSim(FlexODSim* p_FlexODSim) {
    itsFlexODSim = p_FlexODSim;
}

void ODSim::addItsApplication(int key, Application* p_Application) {
    itsApplication.insert(std::map<int, Application*>::value_type(key, p_Application));
}

void ODSim::addItsDevice(int key, Device* p_Device) {
    itsDevice.insert(std::map<int, Device*>::value_type(key, p_Device));
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/ODSim.cpp
*********************************************************************/
