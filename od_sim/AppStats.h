/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: AppStats
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/AppStats.h
*********************************************************************/

#ifndef AppStats_H
#define AppStats_H

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

//## class AppStats
class AppStats {
    ////    Constructors and destructors    ////
    
public :

    //## operation AppStats(int,int)
    AppStats(int app_id_, int dev_id_);
    
    ////    Additional operations    ////
    
    ////    Attributes    ////
    
    ////    Framework operations    ////
    
    ////    Framework    ////
    
    //## operation ~AppStats()
    ~AppStats();

protected :

    int file_flit_size_to_send;		//## attribute file_flit_size_to_send

public :

    //## operation print_info()
    void print_info();
    
    //## operation update_rtt_delay_stats(int,int,int)
    void update_rtt_delay_stats(int pri, int t_create, int t_current);
    
    //## auto_generated
    int getNum_sim_packets() const;
    
    //## auto_generated
    void setNum_sim_packets(int p_num_sim_packets);

protected :

    int file_flit_size_to_rcv;		//## attribute file_flit_size_to_rcv
    
    int num_sim_packets;		//## attribute num_sim_packets

public :

    //## auto_generated
    AppStats();
    
    //## operation add_file_flit_size_to_rcv(int)
    void add_file_flit_size_to_rcv(int inc);
    
    //## operation add_file_flit_size_to_send(int)
    void add_file_flit_size_to_send(int inc);
    
    //## operation add_sim_value_sum_delay(int,int,int,int)
    void add_sim_value_sum_delay(int t1, int t2, int t3, int clk);
    
    //## operation check_histo_with_total_packets(int)
    void check_histo_with_total_packets(int n_pkts);
    
    //## operation increase_num_sim_packets(int)
    void increase_num_sim_packets(int inc);
    
    //## operation print_rtt_to_file(FILE *)
    void print_rtt_to_file(FILE * p_file);
    
    //## operation reset(int,int)
    void reset(int f_size, int flt_size);
    
    //## operation write_file_completion_time(int,int,int,int,int,int,int,int)
    void write_file_completion_time(int clk, int a_id, int pri, int multi, int return_ck, int load, int cnt_q, int ser_q);
    
    //## operation write_stats_and_reset(int,int,SimParam_struct,int)
    void write_stats_and_reset(int app_id, int prio, const SimParam_struct& s_pr, int clk);
    
    //## auto_generated
    int getApp_idx() const;
    
    //## auto_generated
    void setApp_idx(int p_app_idx);
    
    //## auto_generated
    int getDev_idx() const;
    
    //## auto_generated
    void setDev_idx(int p_dev_idx);
    
    //## auto_generated
    int getFile_completion_time() const;
    
    //## auto_generated
    void setFile_completion_time(int p_file_completion_time);
    
    //## auto_generated
    int getFile_flit_size_to_rcv() const;
    
    //## auto_generated
    void setFile_flit_size_to_rcv(int p_file_flit_size_to_rcv);
    
    //## auto_generated
    int getFile_flit_size_to_send() const;
    
    //## auto_generated
    void setFile_flit_size_to_send(int p_file_flit_size_to_send);
    
    //## auto_generated
    int getSim_value_max_delay() const;
    
    //## auto_generated
    void setSim_value_max_delay(int p_sim_value_max_delay);
    
    //## auto_generated
    unsigned long getSim_value_rtt_delay_histo(int i1) const;
    
    //## auto_generated
    void setSim_value_rtt_delay_histo(int i1, unsigned long p_sim_value_rtt_delay_histo);
    
    //## auto_generated
    unsigned long getSim_value_sum_delay_created() const;
    
    //## auto_generated
    void setSim_value_sum_delay_created(unsigned long p_sim_value_sum_delay_created);
    
    //## auto_generated
    unsigned long getSim_value_sum_delay_internal() const;
    
    //## auto_generated
    void setSim_value_sum_delay_internal(unsigned long p_sim_value_sum_delay_internal);
    
    //## auto_generated
    unsigned long getSim_value_sum_delay_rtt() const;
    
    //## auto_generated
    void setSim_value_sum_delay_rtt(unsigned long p_sim_value_sum_delay_rtt);

protected :

    int app_idx;		//## attribute app_idx
    
    int dev_idx;		//## attribute dev_idx
    
    int file_completion_time;		//## attribute file_completion_time
    
    int sim_value_max_delay;		//## attribute sim_value_max_delay
    
    unsigned long sim_value_rtt_delay_histo[RttDelayMax];		//## attribute sim_value_rtt_delay_histo
    
    unsigned long sim_value_sum_delay_created;		//## attribute sim_value_sum_delay_created
    
    unsigned long sim_value_sum_delay_internal;		//## attribute sim_value_sum_delay_internal
    
    unsigned long sim_value_sum_delay_rtt;		//## attribute sim_value_sum_delay_rtt
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/AppStats.h
*********************************************************************/
