/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: ConnMap
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/ConnMap.cpp
*********************************************************************/

//## auto_generated
#include "ConnMap.h"
//## auto_generated
#include <iostream>
//## package Default

//## class ConnMap
ConnMap::ConnMap() {
}

ConnMap::~ConnMap() {
}

void ConnMap::copyNames(char* m_name, char* s_name, char* sw_name) {
    //#[ operation copyNames(char*,char*,char*)
    sprintf(m_name, "%s", source_name);
    sprintf(s_name, "%s", dest_name);
    sprintf(sw_name, "%s", switch_name);
    
    //#]
}

int ConnMap::find_conn_map_index() {
    //#[ operation find_conn_map_index()
    return source_idx*100+dest_idx;
    //#]
}

int ConnMap::find_conn_map_index(int s_idx, int d_idx) {
    //#[ operation find_conn_map_index(int,int)
    return s_idx*100+d_idx;
    //#]
}

int ConnMap::find_set_conn_map_index() {
    //#[ operation find_set_conn_map_index()
    conn_map_index = find_conn_map_index();
    return conn_map_index;
    //#]
}

void ConnMap::print_info() {
    //#[ operation print_info()
    printf("CommInfo Valid: %d c_idx:%d priority:%d\n", valid, conn_map_index, priority);
    
    printf("Source name:%s, idx:%d, port:%d \n",source_name, source_idx, source_port);
    printf("Dest   name:%s, idx:%d, port:%d, Bandwidth:%d \n", dest_name, dest_idx, dest_port, bandwidth);   
    printf("Switch name:%s, idx:%d, s_port:%d, d_port:%d \n", switch_name, switch_idx, switch_port_source, switch_port_dest);
    //#]
}

void ConnMap::setNames(char* m_name, char* s_name) {
    //#[ operation setNames(char*,char*)
    sprintf(source_name, "%s", m_name);
    sprintf(dest_name, "%s", s_name);
    sprintf(switch_name, "none");    
    //#]
}

void ConnMap::setNames(char* s_name, char* sw_name, char* d_name) {
    //#[ operation setNames(char*,char*,char*)
    sprintf(source_name, "%s", s_name);
    sprintf(switch_name, "%s", sw_name);     
    sprintf(dest_name, "%s", d_name);     
    
    
    //#]
}

int ConnMap::getBandwidth() const {
    return bandwidth;
}

void ConnMap::setBandwidth(int p_bandwidth) {
    bandwidth = p_bandwidth;
}

int ConnMap::getConn_map_index() const {
    return conn_map_index;
}

void ConnMap::setConn_map_index(int p_conn_map_index) {
    conn_map_index = p_conn_map_index;
}

int ConnMap::getDest_idx() const {
    return dest_idx;
}

void ConnMap::setDest_idx(int p_dest_idx) {
    dest_idx = p_dest_idx;
}

char ConnMap::getDest_name(int i1) const {
    return dest_name[i1];
}

void ConnMap::setDest_name(int i1, char p_dest_name) {
    dest_name[i1] = p_dest_name;
}

int ConnMap::getDest_port() const {
    return dest_port;
}

void ConnMap::setDest_port(int p_dest_port) {
    dest_port = p_dest_port;
}

int ConnMap::getPriority() const {
    return priority;
}

void ConnMap::setPriority(int p_priority) {
    priority = p_priority;
}

int ConnMap::getSource_idx() const {
    return source_idx;
}

void ConnMap::setSource_idx(int p_source_idx) {
    source_idx = p_source_idx;
}

char ConnMap::getSource_name(int i1) const {
    return source_name[i1];
}

void ConnMap::setSource_name(int i1, char p_source_name) {
    source_name[i1] = p_source_name;
}

int ConnMap::getSource_port() const {
    return source_port;
}

void ConnMap::setSource_port(int p_source_port) {
    source_port = p_source_port;
}

int ConnMap::getSwitch_idx() const {
    return switch_idx;
}

void ConnMap::setSwitch_idx(int p_switch_idx) {
    switch_idx = p_switch_idx;
}

char ConnMap::getSwitch_name(int i1) const {
    return switch_name[i1];
}

void ConnMap::setSwitch_name(int i1, char p_switch_name) {
    switch_name[i1] = p_switch_name;
}

int ConnMap::getSwitch_port_dest() const {
    return switch_port_dest;
}

void ConnMap::setSwitch_port_dest(int p_switch_port_dest) {
    switch_port_dest = p_switch_port_dest;
}

int ConnMap::getSwitch_port_source() const {
    return switch_port_source;
}

void ConnMap::setSwitch_port_source(int p_switch_port_source) {
    switch_port_source = p_switch_port_source;
}

int ConnMap::getValid() const {
    return valid;
}

void ConnMap::setValid(int p_valid) {
    valid = p_valid;
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/ConnMap.cpp
*********************************************************************/
