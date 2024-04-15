/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: FlexODSim
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/FlexODSim.cpp
*********************************************************************/

//## auto_generated
#include <iostream>
//## auto_generated
#include "FlexODSim.h"
//## package Default

//## class FlexODSim
FlexODSim::FlexODSim(int n_app) : itsApplication(), itsDevice(), itsConnMap(), itsSwitchCxl(), itsSwitchOptics() {
    //#[ operation FlexODSim(int)
    clearItsSwitchOptics();
    //#]
}

std::map<int, Application*>::const_iterator FlexODSim::getItsApplication() const {
    std::map<int, Application*>::const_iterator iter;
    iter = itsApplication.begin();
    return iter;
}

std::map<int, Application*>::const_iterator FlexODSim::getItsApplicationEnd() const {
    return itsApplication.end();
}

void FlexODSim::removeItsApplication(Application* p_Application) {
    std::map<int, Application*>::iterator pos = std::find_if(itsApplication.begin(), itsApplication.end(),OMValueCompare<const int,Application*>(p_Application));
    if (pos != itsApplication.end()) {
    	itsApplication.erase(pos);
    }
}

void FlexODSim::clearItsApplication() {
    itsApplication.clear();
}

void FlexODSim::cleanUpRelations() {
    {
        itsApplication.clear();
    }
    {
        itsConnMap.clear();
    }
    {
        itsDevice.clear();
    }
    {
        itsSwitchCxl.clear();
    }
    {
        itsSwitchOptics.clear();
    }
}

void FlexODSim::print_statistics() {
    //#[ operation print_statistics()
    //fprintf(sim_result,"\n Delay Statistics \n");
    
    /*for (int i=0; i<1000; i++)
    {
    	if (delay_statistics[i] == 0)
    		continue;
    	fprintf(sim_result,"delay: %d occurs: %d \n", i, delay_statistics[i]);
    }*/        
    
    
    Application * p_app; 
    //fprintf(sim_result,"\n RTT Delay Statistics \n");
    //for (int i=0; i<sim_param.num_app; i++)
    //{
    //	p_app = getItsApplication(i);
    //	if (p_app==0)  
    //		printf("SW ERROR null p_app %d\n", i);     
    //	p_app->print_rtt_to_file(sim_result);
    //} 
    
    /*
    std::list<Application*>::iterator p_app;    
    for (p_app = itsApplication.begin(); p_app != itsApplication.end(); ++p_app)
    {
    	if ((*p_app)==0)  
    		printf("SW ERROR null p_app\n");     
    	(*p_app)->print_rtt_to_file(sim_result);
    } 
    */  
     
    
    //fprintf(sim_result,"\n Completion Time Statistics \n");	  
    //for (int i=0; i<sim_param.num_app; i++)
    //{
    //	p_app = getItsApplication(i);
    //	if (p_app==0)  
    //		printf("SW ERROR null p_app\n");     
    	//fprintf(sim_result,"comp priority %d completion_time: %d \n", p_app->getPriority(), p_app->get_file_completion_time());
    //}           
    
    
    
                                           
    
    
    //#]
}

void FlexODSim::reinitialize(int n_app, int max_rtt_delay) {
    //#[ operation reinitialize(int,int)
    
    Application * p_app;    
    for (int i=0; i<sim_param.num_app; i++)
    {
    	p_app = getItsApplication(i);
    	if (p_app==0)  
    		printf("SW ERROR null p_app\n");     
    	p_app->reset_stats();
    }                                                
    //#]
}

void FlexODSim::start_sim() {
    //#[ operation start_sim()
    //#]
}

int FlexODSim::getSim_clock() const {
    return sim_clock;
}

void FlexODSim::setSim_clock(int p_sim_clock) {
    sim_clock = p_sim_clock;
}

ODNetConfig* FlexODSim::getNet_conf() const {
    return (ODNetConfig*) &net_conf;
}

std::map<int, Device*>::const_iterator FlexODSim::getItsDevice() const {
    std::map<int, Device*>::const_iterator iter;
    iter = itsDevice.begin();
    return iter;
}

std::map<int, Device*>::const_iterator FlexODSim::getItsDeviceEnd() const {
    return itsDevice.end();
}

void FlexODSim::removeItsDevice(Device* p_Device) {
    std::map<int, Device*>::iterator pos = std::find_if(itsDevice.begin(), itsDevice.end(),OMValueCompare<const int,Device*>(p_Device));
    if (pos != itsDevice.end()) {
    	itsDevice.erase(pos);
    }
}

void FlexODSim::clearItsDevice() {
    itsDevice.clear();
}

FlexODSim::~FlexODSim() {
    cleanUpRelations();
}

void FlexODSim::calculateConfigParam() {
    //#[ operation calculateConfigParam()
    sim_param.link_clock_per_flit = sim_param.clocks_per_usec*sim_param.flit_size*8/sim_param.link_bw_mbps+1;    
    sim_param.mem_clock_per_flit = sim_param.clocks_per_usec*sim_param.flit_size*8/sim_param.mem_bw_mbps+1;    
    sim_param.link_clock_per_req = sim_param.link_clock_per_flit/sim_param.reqs_per_flit+1;    
    sim_param.mem_clock_per_req  = sim_param.mem_clock_per_flit/sim_param.reqs_per_flit+1;  
    //#]
}

void FlexODSim::changeConnParam() {
    //#[ operation changeConnParam()
    
    char option[32];
    char value[32];
    while (1)
    {
    	printf("   [1] to print all connection \n");
    	printf("   [2] [conn_idx] [priority] to change connection priority\n");
    	printf("   [0] to run simulation with updated sim_param\n");
    	
    	//gets(option);
    	fgets(option, sizeof(option), stdin);
        option[strcspn(option,"\n")]=0;
    	int option_i[10]; 
    	char * result;
    	
    	result = strtok(option, " ");
        char parsing[32][30]; 
    	int i=0;
    	while (result != NULL)
    	{
    		option_i[i] = atoi(result);
    		//printf ("option %d : %d result:%s option:%s\n", i, option_i[i], result, option);
    		strcpy(parsing[i++], result);
    		result = strtok(NULL, " ");
    	}
    	//printf ("\n");
    	
    	
    	
    	
    	if(option_i[0] == 1)
    	{
    		print_all_conn_map();
    	}  
    	else if(option_i[0] == 2)
    	{
    		change_connection_priority(option_i[1], option_i[2]);
    	}  
    	/*else if(strcmp(option,"2") == 0)
    	{
    		printf("  Enter load_update_queue value - 0 or 1 current value is %d\n", sim_param.load_update_queue);	
    		gets(value);
    		sim_param.load_update_queue = atoi(value);
    	}
    	else if(strcmp(option,"3") == 0)
    	{
    		printf("  Enter load_update_interval value - current value is %d\n", sim_param.load_update_interval);	
    		gets(value);
    		sim_param.load_update_interval = atoi(value);
    	}
    	else if(strcmp(option,"4") == 0)
    	{
    		printf("  Enter mem_bw_mbps - current value is %d\n", sim_param.mem_bw_mbps);	
    		gets(value);
    		sim_param.mem_bw_mbps = atoi(value);
    	}
    	else if(strcmp(option,"5") == 0)
    	{
    		printf("  Enter max_num_pkt_serialize - current value is %d\n", sim_param.max_num_pkt_serialize);	
    		gets(value);
    		sim_param.max_num_pkt_serialize = atoi(value);
    	}
    	else if(strcmp(option,"6") == 0)
    	{
    		printf("  Enter link_bw_mbps - current value is %d\n", sim_param.link_bw_mbps);	
    		gets(value);
    		sim_param.link_bw_mbps = atoi(value);
    	}
    	else if(strcmp(option,"7") == 0)
    	{
    		printf("  Enter link_delay - current value is %d\n", sim_param.link_delay);	
    		gets(value);
    		sim_param.link_delay = atoi(value);
    	}
    	else if(strcmp(option,"8") == 0)
    	{
    		printf("  Enter window_size - current value is %d\n", sim_param.window_size);	
    		gets(value);
    		sim_param.window_size = atoi(value);
    	}
    	else if(strcmp(option,"9") == 0)
    	{
    		printf("  Enter file_size - current value is %d\n", sim_param.file_size);	
    		gets(value);
    		sim_param.file_size = atoi(value);
    	}
    	else if(strcmp(option,"10") == 0)
    	{
    		printf("  Enter load - current value is %d\n", sim_param.load);	
    		gets(value);
    		sim_param.load = atoi(value);
    	}      
    	else if(strcmp(option,"11") == 0)
    	{
    		printf("  Enter max_sim_clock - current value is %d\n", sim_param.max_sim_clock);	
    		gets(value);
    		sim_param.max_sim_clock = atoi(value);
    	}      
    	else if(strcmp(option,"12") == 0)
    	{
    		changeConnParam();
    	}*/      
    	if(option_i[0]==0) 
    		break;
    }  
    
    /*if (DEBUG) printf("Create CPU %d \n", sim_param.num_app);
    for (int i=0;i<sim_param.num_app; i++)
    {
    	Application * p_app = getItsApplication(i);
    	p_app->setSim_param(sim_param);	  
    }
    
    for (int i=0; i<sim_param.num_device; i++)
    {
    	Device * p_dev = getItsDevice(i);
    	p_dev->setSim_param(sim_param);
    }
    */
     
    //#]
}

void FlexODSim::changeSimParam() {
    //#[ operation changeSimParam()
    
    char option[32];
    char value[32];
    while (1)
    {
    	printf("   [1] [val] to change resp_link_check:      %d\n", sim_param.resp_link_check);
    	printf("   [2] [val] to change load_update_queue:    %d\n", sim_param.load_update_queue);
    	printf("   [3] [val] to change load_update_interval: %d\n", sim_param.load_update_interval);     
    	printf("   [4] [val] to change mem_bw_gbps:          %d\n", sim_param.mem_bw_mbps/1000);
    	printf("   [5] [val] to change max_num_pkt_serialize:%d\n", sim_param.max_num_pkt_serialize);
    	printf("   [6] [val] to change link_bw_gbps:         %d\n", sim_param.link_bw_mbps/1000);
    	printf("   [7] [val] to change link_delay:           %d\n", sim_param.link_delay);    
    	printf("   [8] [val] to change window_size:          %d\n", sim_param.window_size);
    	printf("   [9] [val] to change file_size:            %d\n", sim_param.file_size);
    	printf("  [10] [val] to change load:                 %d\n", sim_param.load);   
    	printf("  [11] [val] to change max_sim_clock:        %d\n", sim_param.max_sim_clock);
    	printf("  [12] [app_idx] [priroity] to change connection priority \n");
    	printf("  [13] [app_idx] [load] to change connection load \n");
    	printf("  [14] [load_min] [load_max] [load_delta] [win_min] [win_max] [win_delta] to run batch \n");
    	printf("  [15] [load_min] [load_max] [load_delta] [membw_min_gbps] [membw_max_gbps] [membw_delta_gbps] to run batch \n");
    	printf("   [0] to run simulation with updated sim_param\n");
    	
    	//gets(option); 
    	fgets(option, sizeof(option), stdin);
        option[strcspn(option,"\n")]=0;
    	
    	int option_i[10]; 
    	char * result;
    	
    	result = strtok(option, " ");
        char parsing[5][30]; 
    	int i=0;
    	while (result != NULL)
    	{
    		option_i[i] = atoi(result);
    		printf ("option %d : %d result:%s option:%s\n", i, option_i[i], result, option);
    		strcpy(parsing[i++], result);
    		result = strtok(NULL, " ");
    	}
    	if(option_i[0] == 1)
    	{
    		sim_param.resp_link_check = option_i[1];
    	}  
    	else if(option_i[0] == 2)
    	{
    		sim_param.load_update_queue = option_i[1];
    	}
    	else if(option_i[0] == 3)
    	{
    		sim_param.load_update_interval = option_i[1];
    	}
    	else if(option_i[0] == 4)
    	{
    		sim_param.mem_bw_mbps = option_i[1]*1000;
    	}
    	else if(option_i[0] == 5)
    	{
    		sim_param.max_num_pkt_serialize = option_i[1];
    	}
    	else if(option_i[0] == 6)
    	{
    		sim_param.link_bw_mbps = option_i[1]*1000;
    	}
    	else if(option_i[0] == 7)
    	{
    		sim_param.link_delay = option_i[1];
    	}
    	else if(option_i[0] == 8)
    	{
    		sim_param.window_size = option_i[1];
    	}
    	else if(option_i[0] == 9)
    	{
    		sim_param.file_size = option_i[1];
    	}
    	else if(option_i[0] == 10)
    	{
    		sim_param.load = option_i[1];
    	}      
    	else if(option_i[0] == 11)
    	{
    		sim_param.max_sim_clock = option_i[1];
    	}      
    	else if(option_i[0] == 12)
    	{
    		change_connection_priority(option_i[1], option_i[2]);
    	}      
    	else if(option_i[0] == 13)
    	{
    		change_connection_load(option_i[1], option_i[2]);
    	}      
    	else if(option_i[0] == 14)
    	{
    		load_min = option_i[1];
    		load_max = option_i[2];
    		load_delta = option_i[3];
    		win_min = option_i[4];
    		win_max = option_i[5];
    		win_delta = option_i[6];
    	}   
    	else if(option_i[0] == 15)
    	{
    		load_min = option_i[1];
    		load_max = option_i[2];
    		load_delta = option_i[3];
    		membw_min = option_i[4]*1000;
    		membw_max = option_i[5]*1000;
    		membw_delta = option_i[6]*1000;
    	}      
    	   
    	else if(strcmp(option,"0") == 0) 
    		break;
    }  
    
    for (int i=0;i<sim_param.num_app; i++)
    {
    	Application * p_app = getItsApplication(i);
    	p_app->setSim_param(sim_param);	  
    }
    for (int i=0; i<sim_param.num_device; i++)
    {
    	Device * p_dev = getItsDevice(i);
    	p_dev->setSim_param(sim_param);
    }
    
    /*if (DEBUG) printf("Create CPU %d \n", sim_param.num_app);
    
    */
     
    //#]
}

void FlexODSim::change_connection_load(int app_idx, int load) {
    //#[ operation change_connection_load(int,int)
    
    /*ConnMap * p_c_map = getItsConnMap(c_idx);
    if (p_c_map == 0)
    {
    	printf("NO Conn Map for c_idx %d\n", c_idx);
    	return;
    }
    
    p_c_map->setPriority(prio);  
    */
    Application * p_app = getItsApplication(app_idx);  
    if (p_app == 0)
    {
    	printf("NO app idx %d\n", app_idx);
    	return;
    }
    SimParam_struct s_pr = p_app->getSim_param();
    s_pr.load = load;  
    p_app->setSim_param(s_pr);
    p_app->print_info(); 
    
    
    //#]
}

void FlexODSim::change_connection_priority(int app_idx, int prio) {
    //#[ operation change_connection_priority(int,int)
    
    /*ConnMap * p_c_map = getItsConnMap(c_idx);
    if (p_c_map == 0)
    {
    	printf("NO Conn Map for c_idx %d\n", c_idx);
    	return;
    }
    
    p_c_map->setPriority(prio);  
    */
    Application * p_app = getItsApplication(app_idx);  
    if (p_app == 0)
    {
    	printf("NO app idx %d\n", app_idx);
    	return;
    }
    p_app->setPriority(prio);
    
    //#]
}

void FlexODSim::createConnMap(ConnMap* c_map) {
    //#[ operation createConnMap(ConnMap)
    
    char s_name[20], d_name[20], sw_name[20];
    int s_idx, d_idx, sw_idx, c_idx;  // source, destination, connection
    c_map->copyNames(s_name, d_name, sw_name);
    s_idx = c_map->getSource_idx();
    sw_idx = c_map->getSwitch_idx();
    d_idx = c_map->getDest_idx();      
    c_idx = c_map->getConn_map_index();
    
    
    if(DEBUG) printf("Create Source %s, Dest %s, Switch %s c_idx %d \n", s_name, d_name, sw_name, c_idx);
    
    Application * p_app = 0;
    SwitchCxl * p_cxl_sw = 0;
    SwitchOptics * p_op_sw = 0;
    Device * p_device = 0;
    		
    if (strncmp("CPU", s_name, 3) == 0)
    {   
    	p_app = getItsApplication( s_idx);     
    	if (p_app == 0)
    	{
    		printf("SW Error %s Not Exist\n",  s_name);  
    	}
    }
    
    if (strncmp("CXL", sw_name, 3) == 0) // CXL_SW
    {
    	p_cxl_sw = getItsSwitchCxl(sw_idx);
    	if (p_cxl_sw == 0)
    	{
    		printf("SW Error %s Not Exist\n", sw_name);	
    	}
    }
    
    else if (strncmp("OP_SW",sw_name, 5) == 0) // OP_SW
    {
    	p_op_sw = getItsSwitchOptics(sw_idx);
    	if (p_op_sw == 0)
    	{
    		printf("SW Error %s Not Exist\n", sw_name);	
    	}  
    }   
    if (strncmp("MEM",d_name, 3) == 0) // Memory
    {
    	p_device = getItsDevice(d_idx);
    	if (p_device == 0)
    	{
    		printf("SW Error %s Not Exist\n", d_name);
    	}
    }
    
    int num_conn_dev = p_app->getNum_connected_dev();
    if (num_conn_dev > 0)
    {
    	printf("%s SW Error connection already exist\n  num_conn_dev should be 1\n", s_name);
    	p_app->print_info();
    	c_map->print_info();   
    	exit(0);
    }
    
    p_app->setPriority(c_map->getPriority());      
    p_app->set_connected_dev_index(d_idx);      
    p_app->setNum_connected_dev(num_conn_dev+1);  
    p_app->createSerializer();  
    
    if(DEBUG) c_map->print_info();
    if(DEBUG) p_app->print_info();
    
    int num_conn_app = p_device->getNum_connected_app();
    p_device->setApp_idx_to_dest_port(s_idx, num_conn_app);
    p_device->setNum_connected_app(num_conn_app+1);
    
    if(DEBUG) printf("Add conn map for %s %s %s c_idx:%d \n", s_name, d_name, sw_name, c_idx);    
    addItsConnMap(c_idx, c_map);
    if (strncmp("CPU",s_name, 3) == 0 && strncmp("MEM",d_name, 3) == 0 &&  strcmp("none",sw_name) == 0)
    {
    	p_app->addItsDevice(d_idx, p_device); 
    	p_device->addItsApplication(s_idx, p_app);  
    
    	p_app->addItsConnMap(c_idx, c_map);                             
    	p_device->addItsConnMap(c_idx, c_map);                          
    	p_device->setApp_idx_to_dest_port(s_idx, c_map->getDest_port());
    
    }
    else if (strncmp("CPU",s_name, 3) == 0 && strncmp("CXL",sw_name, 3) == 0 && strncmp("MEM",d_name, 3) == 0)
    {
    	p_app->addItsSwitchCxl(sw_idx,p_cxl_sw);
    	p_cxl_sw->addItsApplication(s_idx, p_app);   
    	p_cxl_sw->addItsDevice(d_idx, p_device);   
    	p_device->addItsSwitchCxl(sw_idx, p_cxl_sw);
    	
    	p_app->addItsConnMap(c_idx, c_map);
    	p_cxl_sw->addItsConnMap(c_idx, c_map);   
    	p_device->addItsConnMap(c_idx, c_map); 
    	p_device->setApp_idx_to_dest_port(s_idx, c_map->getDest_port());  
    	p_cxl_sw->setApp_idx_to_source_port(s_idx, c_map->getSwitch_port_source());
    	//p_cxl_sw->setDest_idx_to_dest_port(d_idx, c_map->getSwitch_port_dest());
    
    }
    else if (strncmp("CPU",s_name, 3) == 0 && strncmp("OP_SW",sw_name, 5) == 0 && strncmp("MEM",d_name, 3) == 0)
    {
       	p_app->addItsSwitchOptics(sw_idx,p_op_sw);     
       	p_op_sw->addItsApplication(s_idx, p_app);   
    	p_op_sw->addItsDevice(d_idx, p_device);   
    	p_device->addItsSwitchOptics(sw_idx, p_op_sw);
       	
    	p_app->addItsConnMap(c_idx, c_map);
    	p_op_sw->addItsConnMap(c_idx, c_map);   
    	p_device->addItsConnMap(c_idx, c_map);  
    	p_device->setApp_idx_to_dest_port(s_idx, c_map->getDest_port());  
    }
      
    else
    {  
    	printf("Unexpected Unknow Case: source:%s dest:%s switch:%s \n", s_name, d_name, sw_name);
    }  
    
    
    if(DEBUG) p_app->print_info();
    if(DEBUG) p_device->print_info();
    
       
    
    
    
    	  
    //#]
}

void FlexODSim::createConnection_CPU_MEM(ConnMap*& p_c_map) {
    //#[ operation createConnection_CPU_MEM(ConnMap)
    int m_idx, s_idx;
    
    m_idx = p_c_map->getSource_idx();
    s_idx = p_c_map->getDest_idx();
    
    Application * p_app = getItsApplication(m_idx);
    Device * p_dev = getItsDevice(s_idx);
    
    
    p_app->addItsDevice(s_idx, p_dev);
    p_dev->addItsApplication(m_idx, p_app);
    
    
    //#]
}

void FlexODSim::createODElement() {
    //#[ operation createODElement()
    
    char n[20];
    
    if (DEBUG) printf("Create CPU %d \n", sim_param.num_app);
    for (int i=0;i<sim_param.num_app; i++)
    {
    	sprintf(n, "CPU-%d",i);   
    	if (DEBUG) printf("Create %s \n", n);
    	//Application * p_app = new Application(i, sim_param.flit_size, sim_param.clocks_per_usec, \
    	//							sim_param.th_high, sim_param.th_mid, sim_param.th_low, \
    	//							sim_param.delta_severe, sim_param.delta_normal, sim_param.link_bw_mbps, \
    	//							sim_param.reqs_per_flit, sim_param.window_size, sim_param.link_delay);  
    	Application * p_app = new Application(i, sim_param);
    	
    	p_app->set_name_string(n);							
    	if (DEBUG) p_app->print_info();
    	addItsApplication(i, p_app);	  
    }
    
    if (DEBUG) printf("Create %d MEM  \n", sim_param.num_device);
    for (int i=0; i<sim_param.num_device; i++)
    {
    	sprintf(n, "MEM-%d",i);   
    	if (DEBUG) printf("Create %s \n", n);
    	//Device * p_dev = new Device(n, sim_param.load_update_interval, sim_param.link_bw_mbps, sim_param.mem_bw_mbps, sim_param.flit_size, sim_param.link_delay, 0);//sim_param.num_app);
    	Device * p_dev = new Device(n, i, sim_param);//sim_param.num_app);
    	if (DEBUG) p_dev->print_info();
    	addItsDevice(i, p_dev);	  
    }
    
    if (DEBUG) printf("Create CXL Switch %d \n", sim_param.num_switch_cxl);
    for (int i=0;i<sim_param.num_switch_cxl; i++)
    {
    	sprintf(n, "CXL_SW-%d",i);   
    	SwitchCxl * p_s_cxl = new SwitchCxl(n, sim_param.link_bw_mbps, sim_param.link_delay, 0, 0, sim_param.clocks_per_usec);//sim_param.num_app, sim_param.num_device);
    	p_s_cxl->setIndex(i);
    	if (DEBUG) p_s_cxl->print_info();
    	addItsSwitchCxl(i, p_s_cxl);	  
    }   
    
    if (DEBUG) printf("Create Optical Switch %d \n", sim_param.num_switch_optics);
    for (int i=0;i<sim_param.num_switch_optics; i++)
    {
    	SwitchOptics * p_s_op = new SwitchOptics;
    	p_s_op->setIndex(i);
    	sprintf(n, "OP_SW-%d",i);   
    	p_s_op->set_name_string(n);
    	if (DEBUG) p_s_op->print_info();
    	addItsSwitchOptics(i, p_s_op);	  
    }
    
    //#]
}

void FlexODSim::findConfigParam(char* conn_map_line) {
    //#[ operation findConfigParam(char*)
    
    printf("Config Param %s", conn_map_line);    
    
    char delimeter[] = ":";
    char * result;
    char parsing[5][30];
    int i=0;
    
    result = strtok(conn_map_line, delimeter);
    
    while (result != NULL)
    {
    	strcpy(parsing[i++], result);
    	result = strtok(NULL, delimeter);
    }
    
    
    if (strncmp("CPU",parsing[1], 3) == 0)  // Config Parameter for CPU
    {
    	
    	if (strncmp("th_high", parsing[2], 7) == 0)  
    		sim_param.th_high = atoi(parsing[3]);
    	else if (strncmp("th_mid",parsing[2], 6) == 0)  
    		sim_param.th_mid = atoi(parsing[3]);
    	else if (strncmp("th_low",parsing[2], 6) == 0)  
    		sim_param.th_low = atoi(parsing[3]);
    	else if (strncmp("th_high",parsing[2], 7) == 0)  
    		sim_param.th_high = atoi(parsing[3]);
    	else if (strncmp("delta_severe",parsing[2], 12) == 0)  
    		sim_param.delta_severe = atoi(parsing[3]);
    	else if (strncmp("delta_normal",parsing[2], 12) == 0)  
    		sim_param.delta_normal = atoi(parsing[3]);
    	else if (strcmp("window_size",parsing[2]) == 0)  
    		sim_param.window_size = atoi(parsing[3]);
    	else if (strcmp("file_size",parsing[2]) == 0)  
    		sim_param.file_size = atoi(parsing[3]);
    	else if (strcmp("load",parsing[2]) == 0)  
    		sim_param.load = atoi(parsing[3]);
    	else
    	{ 
    		printf("SW Error Undefined Param %s\n", parsing[2]);
    		return;
    	}
    }
    
    else if (strncmp("SYSTEM",parsing[1], 6) == 0)  // Config Parameter for CPU
    {
    	
    	if (strncmp("flit_size",parsing[2], 7) == 0)  
    		sim_param.flit_size = atoi(parsing[3]);
    	else if (strncmp("reqs_per_flit",parsing[2], 6) == 0)  
    		sim_param.reqs_per_flit = atoi(parsing[3]);
    	else if (strncmp("clocks_per_usec",parsing[2], 6) == 0)  
    		sim_param.clocks_per_usec = atoi(parsing[3]);
    	else if (strncmp("num_priority",parsing[2], 7) == 0)  
    		sim_param.num_priority = atoi(parsing[3]);
    	else if (strncmp("num_app",parsing[2], 7) == 0)  
    		sim_param.num_app = atoi(parsing[3]);
    	else if (strcmp("num_device",parsing[2]) == 0)  
    		sim_param.num_device = atoi(parsing[3]);
    	else if (strcmp("num_switch_cxl",parsing[2]) == 0)  
    		sim_param.num_switch_cxl = atoi(parsing[3]);
    	else if (strcmp("num_switch_optics",parsing[2]) == 0)  
    		sim_param.num_switch_optics = atoi(parsing[3]);
    	else if (strcmp("max_num_pkt_serialize",parsing[2]) == 0)  
    		sim_param.max_num_pkt_serialize = atoi(parsing[3]);
    	else if (strncmp("link_bw_mbps",parsing[2], 12) == 0)  
    		sim_param.link_bw_mbps = atoi(parsing[3]);
    	else if (strcmp("link_delay",parsing[2]) == 0)  
    		sim_param.link_delay = atoi(parsing[3]);
    	else if (strcmp("max_sim_clock",parsing[2]) == 0)  
    		sim_param.max_sim_clock = atoi(parsing[3]);
    	
    	else
    	{ 
    		printf("SW Error Undefined Param %s\n", parsing[2]);
    		return;
    	}
    } 
    
    else if (strncmp("MEM",parsing[1], 6) == 0)  // Config Parameter for CPU
    {
    	
    	if (strncmp("mem_bw_mbps",parsing[2], 12) == 0)  
    		sim_param.mem_bw_mbps = atoi(parsing[3]);
    	else if (strncmp("load_update_interval",parsing[2], 20) == 0)  
    		sim_param.load_update_interval = atoi(parsing[3]);
    	else if (strcmp("load_update_queue",parsing[2]) == 0)  
    		sim_param.load_update_queue = atoi(parsing[3]);   
    	else if (strcmp("resp_link_check",parsing[2]) == 0)  
    		sim_param.resp_link_check = atoi(parsing[3]);   
    	else
    	{ 
    		printf("SW Error Undefined Param %s\n", parsing[2]);
    		return;
    	}
    }   
    
    else
    { 
    	printf("SW Error Undefined Scope %s\n", parsing[1]);
    	return;
    }
    
    
    
    //#]
}

void FlexODSim::findConnMap(char* conn_map_line, ConnMap*& p_c_map) {
    //#[ operation findConnMap(char*,ConnMap)
    if(DEBUG) printf("ConnMap config %s \n", conn_map_line);    
     
    
    char delimeter[] = ":";
    char * result;
    char parsing[10][16];
    int i=0;
    
    result = strtok(conn_map_line, delimeter);
    
    while (result != NULL)
    {
    	strcpy(parsing[i++], result);
    	result = strtok(NULL, delimeter);
    }
    
    int num_param = i;  
    if(DEBUG) printf("conn map num_param:%d\n", num_param);
    
    /*for (i = 0; i<5; i++)
    {
    	printf("[%d]:%s \n", i, parsing[i]);
    }*/
    
    if (strncmp("CPU",parsing[1], 3) != 0 && strncmp("CXL",parsing[1], 3) != 0 && strncmp("OP_SW",parsing[1], 5) != 0)
    {
    	p_c_map->setValid(0);
    	return;
    }
    
    p_c_map->setValid(1);
    
    
    int s_idx, d_idx, sw_idx, conn_idx;
    
    
    if (num_param == 8) // When NO Switch is Connected
    {
    	p_c_map->setNames(parsing[1], parsing[3]);
    	s_idx = findIndex(parsing[1]);
    	d_idx = findIndex(parsing[3]);
    	p_c_map->setSource_idx(s_idx);
    	p_c_map->setDest_idx(d_idx);
    	//if(DEBUG) printf("source_idx %d dest_idx %d\n",s_idx, d_idx);  
    	
    	p_c_map->setSource_port(atoi(parsing[2]));
    	//c_map->setdest_name(0,parsing[2][0]);
    	p_c_map->setDest_port(atoi(parsing[4]));
    	p_c_map->setBandwidth(atoi(parsing[5]));
    	p_c_map->setPriority(atoi(parsing[7]));
    }
    
    else if (num_param == 11) // When Swith is Connected
    {
    	p_c_map->setNames(parsing[1], parsing[3], parsing[6]);
    	s_idx = findIndex(parsing[1]);
    	d_idx = findIndex(parsing[6]);
    	sw_idx = findIndex(parsing[3]);  
    	
    	
    	p_c_map->setSource_idx(s_idx);
    	p_c_map->setDest_idx(d_idx);
    	p_c_map->setSwitch_idx(sw_idx);
    	//printf("source_idx %d dest_idx %d switch_idx\n",s_idx, d_idx, sw_idx);  
    	
    	p_c_map->setSource_port(atoi(parsing[2]));
    	//c_map->setdest_name(0,parsing[2][0]);
    	p_c_map->setDest_port(atoi(parsing[7]));
    	p_c_map->setSwitch_port_source(atoi(parsing[4]));
    	p_c_map->setSwitch_port_dest(atoi(parsing[5]));
    	
    	p_c_map->setBandwidth(atoi(parsing[8]));
    	p_c_map->setPriority(atoi(parsing[10]));
    	
    } 
    
    p_c_map->find_set_conn_map_index();
    
    //#]
}

int FlexODSim::findIndex(char* _name) {
    //#[ operation findIndex(char*)
    char parsing[2][10];
    int idx;
    int i=0;  
    char delimeter[] = "-";
    char * result;
    result = strtok(_name, delimeter);
    
    while (result != NULL)
    {
    	strcpy(parsing[i++], result);
    	result = strtok(NULL, delimeter);
    }
    
    idx = atoi(parsing[1]);
    return idx;
    
    //#]
}

void FlexODSim::findSimParam(char* conn_map_line) {
    //#[ operation findSimParam(char*)
    
    
    
    
    //#]
}

void FlexODSim::initialize() {
    //#[ operation initialize()
    if(DEBUG) printf("\n>>>>> FlexODSim start ");
    char f_name[128];
    printf("Enter file name: (./input_file/ConnMap.txt)");
    //gets(f_name);
    fgets(f_name, sizeof(f_name), stdin);
    f_name[strcspn(f_name,"\n")]=0;
    if (strcmp(f_name,"") == 0)
    {
    	sprintf(f_name,"%s","./input_file/ConnMap.txt");
    }
         
    FILE    *fp = fopen(f_name,"r");
    int     len = 0, total = 0;
    char    buff[64] = {0,};
    
    if(fp == NULL)
    {
        printf("file name %s file open fail\n", f_name);
        return;
    }          
    
    
    
    char *p;
    while(!feof(fp))
    {
        p = fgets(buff, sizeof(buff), fp);
        if(p != NULL)  
        {      
        	//printf("\n>>>> New Line %s", p);
        	if (strncmp(p,"CONFIG",6) == 0)
        	{
        		findConfigParam(p);
        	}
        	else if (strncmp(p,"SIM",3) == 0)
        	{
        		findSimParam(p);
        	}
        	else if (strncmp(p,"#",1) == 0 || strncmp(p," ",1) == 0 || strcmp(p,"\n") == 0)
        	{
        		continue;
        	}
        	else
        	{
        		//printf("SW Error undefined line %s", p);
        		continue;
        	}
        }
    }
    
    calculateConfigParam();
    createODElement();  
    
      
    
    fp = fopen(f_name,"r");
    
    while(!feof(fp))
    {
        p = fgets(buff, sizeof(buff), fp);
        if(p != NULL)  
        {      
        	if(DEBUG) printf("\n>>>> New Line %s", p);
        	if (strncmp(p,"CONN_MAP",7) == 0)
        	{   
        		ConnMap * c_map = new ConnMap;
        		findConnMap(p, c_map); 
        		//c_map->print_info(); 
        		if (c_map->getValid())
        		{
        			createConnMap(c_map);
        		}
        	}
        	else if (strncmp(p,"#",1) == 0 || strncmp(p," ",1) == 0 || strcmp(p,"\n") == 0)
        	{
        		continue;
        	}
        	else
        	{
        		//printf("SW Error undefined line %s", p);
        		continue;
        	}
        }
    } 
    fclose(fp); 
    
    validate_conn_interface();
    
    for (int i=0; i<sim_param.num_device; i++)
    {
    	Device * p_dev = getItsDevice(i);
    	if (p_dev==0)
        	printf("SW Error NULL device for idx %d ", i);
        p_dev->init_conn_interface();    		
    }
    
    //#]
}

void FlexODSim::print_all_conn_map() {
    //#[ operation print_all_conn_map()
    for (int i=0; i<sim_param.num_app; i++)
    	for (int j=0; j<sim_param.num_device; j++)
    	{
    		int c_idx = ConnMap::find_conn_map_index(i,j);
    		ConnMap * p_c_map = getItsConnMap(c_idx);    
    		if (p_c_map == 0)
    			continue;
    		printf("c_idx:%d =====\n",c_idx);
    		p_c_map->print_info();
    		
    	}
    //#]
}

void FlexODSim::print_sim_param() {
    //#[ operation print_sim_param()
    print_sim_param(sim_param);
    //#]
}

void FlexODSim::print_sim_param(const SimParam_struct& s_) {
    //#[ operation print_sim_param(SimParam_struct)
    printf("Simulation Parameters \n");
    printf("  numbers: priority:%2d, app:%2d, device:%2d, sw_cxl:%2d, sw_optics:%2d\n",
    		  s_.num_priority, s_.num_app, s_.num_device, s_.num_switch_cxl, s_.num_switch_optics);
    printf("  window ctrl: high:%2d, mid:%2d, low:%2d, d_severe:%2d, d_normal:%2d, w_size:%3d\n",
    		  s_.th_high, s_.th_mid, s_.th_low, s_.delta_severe, s_.delta_normal, s_.window_size);
    printf("  %d clock/usec, %d B/flit, %d reqs/flit \n",
    		  s_.clocks_per_usec, s_.flit_size, s_.reqs_per_flit);
    printf("  link:   %3d Gbps, %3d clock/flit, %3d clock/req, delay %d clocks\n",
    		  s_.link_bw_mbps/1000, s_.link_clock_per_flit, s_.link_clock_per_req, s_.link_delay);
    printf("  memory: %3d Gbps, %3d clock/flit, %3d clock/req\n",
    		  s_.mem_bw_mbps/1000, s_.mem_clock_per_flit, s_.mem_clock_per_req);
    printf("  flit_size:%d, reqs_per_flit:%d, clocks_per_usec:%d\n",
    		  s_.flit_size, s_.reqs_per_flit, s_.clocks_per_usec);
    printf("  load_update: interval:%d, queue:%d, resp_link_check:%d, max_pkt_ser:%d\n",
    		  s_.load_update_interval, s_.load_update_queue, s_.resp_link_check, s_.max_num_pkt_serialize);
    printf("  max_sim_clock:%d, file_size:%d, load:%d\n",
    		  s_.max_sim_clock, s_.file_size, s_.load);
    //#]
}

void FlexODSim::run_sim() {
    //#[ operation run_sim()
    // define all simulation configuration    
    
    
    sim_clock = 0;    
    calculateConfigParam();
    
    
    
    
    // LD related
    
      
    
    
    int load_update_interval = 100*sim_param.link_clock_per_flit;     
    int rtt_delay_max = 10000;
    
    int link_prop_delay = 0;  
    //int max_num_pkt_serialize = 2;   
    //MaxNumPktSerialize = sim_param.max_num_pkt_serialize;   
    
    net_conf.setSwitch_type(1); //(0:cxl,1:optic)
    
    //printf("\nlk_bw: %d Gbps, mem_bw: %d Gbps, %d clks/us, FlitSize: %d , Req/Flit: %d\n", 
    //		link_bw_mbps/1000, MemBWMbps/1000, clocks_per_micro_second, flit_size, req_per_flit);
    //printf("q_size_ovld_count: %d , max_pkt_serialize: %d , Switch: %d (0:cxl,1:optic) \n\n", 
    //        LoadUpdateQ, max_num_pkt_serialize, net_conf.getSwitch_type());
    
    //initialize(&sim_clock, num_app, load_update_interval, flit_size, clocks_per_micro_second, rtt_delay_max, link_bw_mbps, MemBWMbps, throt_load_threshold_high, throt_load_threshold_mid, throt_load_threshold_low, throt_delta_high, throt_delta_low, req_per_flit, window_size, link_prop_delay );
                                 
    //sim_clock_max = 12500; //file_size*req_per_flit*200/flit_size; //1000000;   
    //sim_clock_max = WindowSize*1*LinkClocksPerFlit;
    
    // FlitSize = 100; defined in initialize()
    
          
    char file_name[50];             
    
    
    
    //sprintf(file_name, "./output_file/Sim_File_Summary.txt");
    //sim_result3 = fopen(file_name, "w+");  
  
    /*
    fprintf(sim_result3, "lk_bw: %d Mbps, mem_bw: %d Mbps, %d clks/us, FlitSize: %d , Req/Flit: %d\n", 
    		link_bw_mbps/1000, MemBWMbps/1000, clocks_per_micro_second, flit_size, req_per_flit);
    printf("sim_clock_max:%d, LinkClkPerFlit:%d, LinkClkPerReq:%d, MemClkPerFlit:%d, MemClkPerReq:%d\n", 
            sim_clock_max, LinkClocksPerFlit, LinkClocksPerReq, MemClocksPerFlit, MemClocksPerReq);
    fprintf(sim_result3, "LinkClkPerFlit:%d, LinkClkPerReq:%d, MemClkPerFlit:%d, MemClkPerReq:%d\n", 
            LinkClocksPerFlit, LinkClocksPerReq, MemClocksPerFlit, MemClocksPerReq);
    fprintf(sim_result3, "threshold_high:%d, threshold_mid:%d, threshold_low:%d, delta_high:%d, delta_low:%d\n", 
            throt_load_threshold_high, throt_load_threshold_mid, throt_load_threshold_low, throt_delta_high, throt_delta_low);
    fprintf(sim_result3, "q_size_ovld_count:%d, max_pkt_serialize:%d, Switch:%d(0:cxl,1:optic) \n\n", 
            LoadUpdateQ, max_num_pkt_serialize, net_conf.getSwitch_type());
    */
    
    
    Application * p_app;    
    Device * p_device;          
    
    
    /*                              
    
    for (MemBWMbps = 100000; MemBWMbps < 501000; MemBWMbps = MemBWMbps+50000)
    for (MaxNumPktSerialize = 5; MaxNumPktSerialize <6; MaxNumPktSerialize = MaxNumPktSerialize+1)
    for (StrictPriority = 0; StrictPriority <1; StrictPriority = StrictPriority+1)
    for (IsMultiReturnLinks = 1; IsMultiReturnLinks <2; IsMultiReturnLinks = IsMultiReturnLinks+1)
    for (RespLinkCheck =0; RespLinkCheck <2; RespLinkCheck = RespLinkCheck+1)
    for (LoadUpdateQ =20; LoadUpdateQ <21; LoadUpdateQ = LoadUpdateQ+1)       
    for (IsThrottled = 0; IsThrottled <2; IsThrottled++)
    for (IsFlowControlled = 0; IsFlowControlled <2; IsFlowControlled++)      
    for (WindowSize = 100; WindowSize < 1010; WindowSize = WindowSize+100)
    for (int load = 100; load < 101; load = load+5)
    //for (LoadUpdateOption =0; LoadUpdateOption <1; LoadUpdateOption = LoadUpdateOption+1)
    //for (int load = 100; load < 101; load = load+10)
    */
    {  
    	int load_update_interval = 100*sim_param.link_clock_per_flit;     
    	
    	//max_num_pkt_serialize =  MaxNumPktSerialize;
    	if (DEBUG) print_sim_param();
    	//sprintf(file_name, "./output_file/Sim_Result_Load_%d_q_%d_ck_%d.txt", sim_param.load, sim_param.load_update_queue, sim_param.resp_link_check);
    	//sim_result = fopen(file_name, "w+"); 
    	//fprintf(sim_result, "lk_bw: %d Gbps, mem_bw: %d Gbps, %d req/flit, max_serial: %d pkts\n", 
    	//					 sim_param.link_bw_mbps/1000, sim_param.mem_bw_mbps/1000, sim_param.reqs_per_flit, sim_param.max_num_pkt_serialize);  
    		
    
    	if (itsApplication.size() == 0)
    	{
    		printf("!!!!!!!!!!! SW ERROR no app is added\n");     
    	}
    	printf("App Reinit ... num_app %d\n", sim_param.num_app);   
    	for (int i=0; i<sim_param.num_app; i++)
    	{
    		//(*p_app)->GEN(evGlobalClock(sim_clock));
    		p_app = getItsApplication(i);
    		if (p_app==0)  
    			printf("start_sim SW ERROR null p_app %d\n", i);     
    		//p_app->reinit(sim_param.load, sim_param.file_size, sim_param.link_delay, sim_param.window_size);
    		p_app->reinit(sim_param);
    	}
    	
    	printf("Device Reinit ... num_device %d\n", sim_param.num_device);    
    	
    	for (int i=0; i<sim_param.num_device; i++)
    	{
    		p_device = getItsDevice(i);
    		if (p_device==0)  
    			printf("SW ERROR null p_app\n");     
    	
    		p_device->reinit(sim_param);      
    	}
    	printf("Switch CXL Reinit ... num_sw %d\n", sim_param.num_switch_cxl);              
    	for (int i=0; i<sim_param.num_switch_cxl; i++)
    	{
    		SwitchCxl * p_sw_cxl = getItsSwitchCxl(i);
    		if (p_sw_cxl==0)  
    			printf("SW ERROR null p_app\n");     
    	
    		p_sw_cxl->reinit(sim_param.num_app, sim_param.link_delay); 
    	}
    	
    	     
    	
    	
    
    	print_sim_param();
    		
    	for (sim_clock = 0; sim_clock<sim_param.max_sim_clock; sim_clock++)
    	{ 
    		if (DEBUG) printf("sim_clock: %d  sim_param.max_sim_clock:%d\n", sim_clock, sim_param.max_sim_clock); 
    		if (DEBUG) printf("Process Device ... %d\n", sim_clock);
    		for (int i=0; i<sim_param.num_device; i++)
    		{
    			p_device = getItsDevice(i);
    			if (p_device==0)  
    				printf("SW ERROR null p_app\n");     
    			p_device->process_clock(sim_clock);
    		}		
    		
    		//cxl_switch->print_info();
    		if (DEBUG) printf("Process Switch ... \n");
    	    for (int i=0; i<sim_param.num_switch_cxl; i++)
    		{
    			SwitchCxl * p_sw_cxl = getItsSwitchCxl(i);
    			if (p_sw_cxl==0)  
    				printf("SW ERROR null p_switch_cxl \n");     
    		
    			p_sw_cxl->process_clock(sim_clock); 
    		}
    		if (DEBUG) printf("Process App ... \n");  
    		for (int i=0; i<sim_param.num_app; i++)
    		{  
    			p_app = getItsApplication(i);
    			if (p_app==0)  
    				printf("SW ERROR null p_app\n"); 
    			p_app->process_clock(sim_clock);     	 
    		}
    	}         
    	print_statistics();  
    	printf ("---------------------------------------------------------------------\n");
    	printf ("app->dev| load | pri | pkts |comp time|avg_delay d1|   d2   |   d3   \n");
    	printf ("---------------------------------------------------------------------\n");
    
    	for (int i=0; i<sim_param.num_app; i++)
    	{
    		p_app = getItsApplication(i);
    		if (p_app==0)  
    			printf("SW ERROR null p_app\n");     
    		SimParam_struct s_p = p_app->getSim_param();
    		int prio = p_app->getPriority();
    		p_app->write_file_completion_time(s_p.resp_link_check, s_p.load_update_queue, s_p.max_num_pkt_serialize);
    		p_app->write_stats_and_reset(i, prio, sim_clock);   
    
    	} 
    	printf ("---------------------------------------------------------------------\n");
    	
    	//fclose(sim_result);
    }   
    //fclose(sim_result3);   
    
    //#]
}

void FlexODSim::run_sim_batch_membw() {
    //#[ operation run_sim_batch_membw()
    SimParam_struct s_pr;
    //for (int m=50; m<51; m=m+10)
    for (int l=0; l<2; l++)
    {
    	for (int i=load_min; i<load_max+1; i=i+load_delta)
    	{
    		for (int k=membw_min; k<membw_max+1; k=k+membw_delta)
    		{
    			for (int j=0; j<sim_param.num_app; j++)
    			{
    				Application * p_app = getItsApplication(j); 
    				s_pr = p_app->getSim_param();
    				s_pr.load = i;
    				s_pr.mem_bw_mbps = k;
    				s_pr.resp_link_check = l;  
    				//s_pr.window_size = m;   
    				p_app->setSim_param(s_pr);
    			}   
    			for (int j=0; j<sim_param.num_device; j++)
    			{
    				Device * p_dev = getItsDevice(j); 
    				p_dev->setSim_param(s_pr);   
    			}
    			sim_param = s_pr;
    			printf("Run Batch Simulation =====> check:%d mem_bw:%d, load:%d \n", l, k, i);
    			run_sim();
    		}
    	}
    }
    load_min = 0;
    load_max = 0;
    load_delta = 0;
    membw_min = 0;
    membw_max = 0;
    membw_delta = 0;
          
    
    //#]
}

void FlexODSim::run_sim_batch_win() {
    //#[ operation run_sim_batch_win()
    SimParam_struct s_pr;
    for (int l=0; l<2; l++)
    {
    	for (int i=load_min; i<load_max+1; i=i+load_delta)
    	{
    		for (int k=win_min; k<win_max+1; k=k+win_delta)
    		{
    			for (int j=0; j<sim_param.num_app; j++)
    			{
    				Application * p_app = getItsApplication(j); 
    				s_pr = p_app->getSim_param();
    				s_pr.load = i;
    				s_pr.window_size = k;  
    				s_pr.resp_link_check = l;    
    				p_app->setSim_param(s_pr);
    			}
    			sim_param = s_pr;
    			run_sim();
    		}
    	}
    }
    load_min = 0;
    load_max = 0;
    load_delta = 0;
    win_min = 0;
    win_max = 0;
    win_delta = 0;
          
    
    //#]
}

void FlexODSim::validate_conn_interface() {
    //#[ operation validate_conn_interface()
    for (int i=0; i<sim_param.num_app; i++)
    	for (int j=0; j<sim_param.num_device; j++)
    	{
    		int c_idx = ConnMap::find_conn_map_index(i,j);
    		ConnMap * p_c_map = getItsConnMap(c_idx);    
    		if (p_c_map == 0)
    			continue;
    		for (int ii=0; ii<sim_param.num_app; ii++)
    			for (int jj=0; jj<sim_param.num_device; jj++)
    			{
    				if (i == ii && j==jj)
    					continue;
    				int c_idx2 = ConnMap::find_conn_map_index(ii,jj);
    				ConnMap * p_c_map2 = getItsConnMap(c_idx2);
    				if (p_c_map2 == 0)
    					continue;
    				if(DEBUG) printf("validate cpu-%d mem-%d vs cpu-%d mem-%d \n", i,j,ii,jj);	   
    				validate_conn_map_pair(p_c_map, p_c_map2);    
    			}
    	}
    //#]
}

void FlexODSim::validate_conn_map_pair(ConnMap* p_c_map_1, ConnMap* p_c_map_2) {
    //#[ operation validate_conn_map_pair(ConnMap,ConnMap)
    char s_name_1[20], d_name_1[20], sw_name_1[20];
    char s_name_2[20], d_name_2[20], sw_name_2[20];
    p_c_map_1->copyNames(s_name_1, d_name_1, sw_name_1);
    p_c_map_2->copyNames(s_name_2, d_name_2, sw_name_2);
    
    
    if (strcmp(sw_name_1, "none") == 0)
    {
    	if ((p_c_map_1->getDest_port() == p_c_map_2->getDest_port()) &&
    	    (p_c_map_1->getDest_idx() == p_c_map_2->getDest_idx()))
    	{
    		printf("SW ERROR duplicate dest port\n");
    		p_c_map_1->print_info();
    	    p_c_map_2->print_info(); 
    	    printf("SW ERROR ... terminate\n");
    	    exit(0);
    		
    	} 		
    } 
    
    if (strcmp(s_name_1, s_name_2) == 0)
    {
    	printf("SW ERROR duplicate source\n");
    	p_c_map_1->print_info();
        p_c_map_2->print_info(); 
        printf("SW ERROR ... terminate\n");
        exit(0);
    }   
    
    if ((strncmp(sw_name_1, "CXL_SW", 6) == 0) && 
        (strncmp(sw_name_2, "CXL_SW", 6) == 0) && 
        (p_c_map_1->getSwitch_port_source() == p_c_map_2->getSwitch_port_dest() ||
         p_c_map_2->getSwitch_port_source() == p_c_map_1->getSwitch_port_dest()))
    {
    	printf("SW ERROR duplicate switch source port and dest port\n");
    	p_c_map_1->print_info();
        p_c_map_2->print_info(); 
        printf("SW ERROR ... terminate\n");
        exit(0);
    }   
    
    
    if ((strncmp(sw_name_1, "CXL_SW", 6) == 0) && 
        (strncmp(sw_name_2, "CXL_SW", 6) == 0))
        if ((p_c_map_1->getSwitch_port_source() == p_c_map_2->getSwitch_port_source()) &&
            (p_c_map_1->getSwitch_idx() == p_c_map_2->getSwitch_idx()))
        {
    		printf("SW ERROR mismatch duplicated switch port source\n");
    		p_c_map_1->print_info();
    	    p_c_map_2->print_info(); 
    	    printf("SW ERROR ... terminate\n");
    	    exit(0);
    	}    
    	
    if ((strncmp(sw_name_1, "CXL_SW", 6) == 0) && 
        (strncmp(sw_name_2, "CXL_SW", 6) == 0))
    {	
        if ((p_c_map_1->getDest_port() == p_c_map_2->getDest_port()) &&
         	(p_c_map_1->getDest_idx() == p_c_map_2->getDest_idx()) &&
            ((p_c_map_1->getSwitch_idx() != p_c_map_2->getSwitch_idx()) ||
         	 (p_c_map_1->getSwitch_port_dest() != p_c_map_2->getSwitch_port_dest())))
     	{
    		printf("SW ERROR mismatch switch port dest and dest port\n");
    		p_c_map_1->print_info();
    	    p_c_map_2->print_info(); 
    	    printf("SW ERROR ... terminate\n");
    	    exit(0);
    	}
    	if ((p_c_map_1->getDest_port() != p_c_map_2->getDest_port() ||
         	 p_c_map_1->getDest_idx()  != p_c_map_2->getDest_idx()) &&
            (p_c_map_1->getSwitch_idx()       == p_c_map_2->getSwitch_idx() &&
         	 p_c_map_1->getSwitch_port_dest() == p_c_map_2->getSwitch_port_dest()))
     	{
    		printf("SW ERROR mismatch -- same switch dest port should connect to same device port\n");
    		printf(" dest port : %d %d \n", p_c_map_1->getDest_port(), p_c_map_2->getDest_port());
    		printf(" dest index : %d %d \n", p_c_map_1->getDest_idx(), p_c_map_2->getDest_idx());
    		printf(" switch index : %d %d \n", p_c_map_1->getSwitch_idx(), p_c_map_2->getSwitch_idx());
    		printf(" switch port dest : %d %d \n", p_c_map_1->getSwitch_port_dest(), p_c_map_2->getSwitch_port_dest());
    		p_c_map_1->print_info();
    	    p_c_map_2->print_info(); 
    	    printf("SW ERROR ... terminate\n");
    	    exit(0);
    	}      
    }	
    
    
    
    //#]
}

int FlexODSim::getLoad_delta() const {
    return load_delta;
}

void FlexODSim::setLoad_delta(int p_load_delta) {
    load_delta = p_load_delta;
}

int FlexODSim::getLoad_max() const {
    return load_max;
}

void FlexODSim::setLoad_max(int p_load_max) {
    load_max = p_load_max;
}

int FlexODSim::getLoad_min() const {
    return load_min;
}

void FlexODSim::setLoad_min(int p_load_min) {
    load_min = p_load_min;
}

int FlexODSim::getMembw_delta() const {
    return membw_delta;
}

void FlexODSim::setMembw_delta(int p_membw_delta) {
    membw_delta = p_membw_delta;
}

int FlexODSim::getMembw_max() const {
    return membw_max;
}

void FlexODSim::setMembw_max(int p_membw_max) {
    membw_max = p_membw_max;
}

int FlexODSim::getMembw_min() const {
    return membw_min;
}

void FlexODSim::setMembw_min(int p_membw_min) {
    membw_min = p_membw_min;
}

SimParam_struct FlexODSim::getSim_param() const {
    return sim_param;
}

void FlexODSim::setSim_param(SimParam_struct p_sim_param) {
    sim_param = p_sim_param;
}

int FlexODSim::getWin_delta() const {
    return win_delta;
}

void FlexODSim::setWin_delta(int p_win_delta) {
    win_delta = p_win_delta;
}

int FlexODSim::getWin_max() const {
    return win_max;
}

void FlexODSim::setWin_max(int p_win_max) {
    win_max = p_win_max;
}

int FlexODSim::getWin_min() const {
    return win_min;
}

void FlexODSim::setWin_min(int p_win_min) {
    win_min = p_win_min;
}

Application* FlexODSim::getItsApplication(int key) const {
    std::map<int, Application*>::const_iterator it = itsApplication.find(key);
    if (it != itsApplication.end())
    	return (*it).second;
    else
    	return NULL;
}

void FlexODSim::removeItsApplication(int key) {
    itsApplication.erase(key);
}

std::map<int, ConnMap*>::const_iterator FlexODSim::getItsConnMap() const {
    std::map<int, ConnMap*>::const_iterator iter;
    iter = itsConnMap.begin();
    return iter;
}

std::map<int, ConnMap*>::const_iterator FlexODSim::getItsConnMapEnd() const {
    return itsConnMap.end();
}

void FlexODSim::clearItsConnMap() {
    itsConnMap.clear();
}

void FlexODSim::removeItsConnMap(ConnMap* p_ConnMap) {
    std::map<int, ConnMap*>::iterator pos = std::find_if(itsConnMap.begin(), itsConnMap.end(),OMValueCompare<const int,ConnMap*>(p_ConnMap));
    if (pos != itsConnMap.end()) {
    	itsConnMap.erase(pos);
    }
}

ConnMap* FlexODSim::getItsConnMap(int key) const {
    std::map<int, ConnMap*>::const_iterator it = itsConnMap.find(key);
    if (it != itsConnMap.end())
    	return (*it).second;
    else
    	return NULL;
}

void FlexODSim::addItsConnMap(int key, ConnMap* p_ConnMap) {
    itsConnMap.insert(std::map<int, ConnMap*>::value_type(key, p_ConnMap));
}

void FlexODSim::removeItsConnMap(int key) {
    itsConnMap.erase(key);
}

Device* FlexODSim::getItsDevice(int key) const {
    std::map<int, Device*>::const_iterator it = itsDevice.find(key);
    if (it != itsDevice.end())
    	return (*it).second;
    else
    	return NULL;
}

void FlexODSim::removeItsDevice(int key) {
    itsDevice.erase(key);
}

std::map<int, SwitchCxl*>::const_iterator FlexODSim::getItsSwitchCxl() const {
    std::map<int, SwitchCxl*>::const_iterator iter;
    iter = itsSwitchCxl.begin();
    return iter;
}

std::map<int, SwitchCxl*>::const_iterator FlexODSim::getItsSwitchCxlEnd() const {
    return itsSwitchCxl.end();
}

void FlexODSim::clearItsSwitchCxl() {
    itsSwitchCxl.clear();
}

void FlexODSim::removeItsSwitchCxl(SwitchCxl* p_SwitchCxl) {
    std::map<int, SwitchCxl*>::iterator pos = std::find_if(itsSwitchCxl.begin(), itsSwitchCxl.end(),OMValueCompare<const int,SwitchCxl*>(p_SwitchCxl));
    if (pos != itsSwitchCxl.end()) {
    	itsSwitchCxl.erase(pos);
    }
}

SwitchCxl* FlexODSim::getItsSwitchCxl(int key) const {
    std::map<int, SwitchCxl*>::const_iterator it = itsSwitchCxl.find(key);
    if (it != itsSwitchCxl.end())
    	return (*it).second;
    else
    	return NULL;
}

void FlexODSim::addItsSwitchCxl(int key, SwitchCxl* p_SwitchCxl) {
    itsSwitchCxl.insert(std::map<int, SwitchCxl*>::value_type(key, p_SwitchCxl));
}

void FlexODSim::removeItsSwitchCxl(int key) {
    itsSwitchCxl.erase(key);
}

std::map<int, SwitchOptics*>::const_iterator FlexODSim::getItsSwitchOptics() const {
    std::map<int, SwitchOptics*>::const_iterator iter;
    iter = itsSwitchOptics.begin();
    return iter;
}

std::map<int, SwitchOptics*>::const_iterator FlexODSim::getItsSwitchOpticsEnd() const {
    return itsSwitchOptics.end();
}

void FlexODSim::clearItsSwitchOptics() {
    itsSwitchOptics.clear();
}

void FlexODSim::removeItsSwitchOptics(SwitchOptics* p_SwitchOptics) {
    std::map<int, SwitchOptics*>::iterator pos = std::find_if(itsSwitchOptics.begin(), itsSwitchOptics.end(),OMValueCompare<const int,SwitchOptics*>(p_SwitchOptics));
    if (pos != itsSwitchOptics.end()) {
    	itsSwitchOptics.erase(pos);
    }
}

SwitchOptics* FlexODSim::getItsSwitchOptics(int key) const {
    std::map<int, SwitchOptics*>::const_iterator it = itsSwitchOptics.find(key);
    if (it != itsSwitchOptics.end())
    	return (*it).second;
    else
    	return NULL;
}

void FlexODSim::addItsSwitchOptics(int key, SwitchOptics* p_SwitchOptics) {
    itsSwitchOptics.insert(std::map<int, SwitchOptics*>::value_type(key, p_SwitchOptics));
}

void FlexODSim::removeItsSwitchOptics(int key) {
    itsSwitchOptics.erase(key);
}

void FlexODSim::addItsApplication(int key, Application* p_Application) {
    itsApplication.insert(std::map<int, Application*>::value_type(key, p_Application));
}

void FlexODSim::addItsDevice(int key, Device* p_Device) {
    itsDevice.insert(std::map<int, Device*>::value_type(key, p_Device));
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/FlexODSim.cpp
*********************************************************************/
