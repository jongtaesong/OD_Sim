/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Packet
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/Packet.cpp
*********************************************************************/

//## auto_generated
#include "Packet.h"
//## auto_generated
#include <iostream>
//## package Default

//## class Packet
Packet::Packet() : time_created(0), time_tx_app(0), time_tx_internal(0) {
}

Packet::~Packet() {
}

void Packet::print_info() {
    //#[ operation print_info()
    printf("    app_id:%d, dev_id:%d, priority:%d, size:%d,  type:%d \n", app_id, device_id, priority, size, type);
    printf("    time_created:%d, time_tx_app:%d, time_tx_internal:%d, sending_complete:%d, \n", 
                time_created, time_tx_app, time_tx_internal, time_sending_complete);
    //std::cout << "size:"<<size<<", time_created:"<< time_created << ", time_to_send:"<<time_to_send<<", type:"<<type<<std::endl;
    //#]
}

unsigned long Packet::getAddress() const {
    return address;
}

void Packet::setAddress(unsigned long p_address) {
    address = p_address;
}

int Packet::getApp_id() const {
    return app_id;
}

void Packet::setApp_id(int p_app_id) {
    app_id = p_app_id;
}

char* Packet::getContent() const {
    return content;
}

void Packet::setContent(char* p_content) {
    content = p_content;
}

int Packet::getDevice_id() const {
    return device_id;
}

void Packet::setDevice_id(int p_device_id) {
    device_id = p_device_id;
}

int Packet::getLoad_updated() const {
    return load_updated;
}

void Packet::setLoad_updated(int p_load_updated) {
    load_updated = p_load_updated;
}

Packet* Packet::getNext() const {
    return next;
}

void Packet::setNext(Packet* p_next) {
    next = p_next;
}

int Packet::getPriority() const {
    return priority;
}

void Packet::setPriority(int p_priority) {
    priority = p_priority;
}

unsigned int Packet::getSize() const {
    return size;
}

void Packet::setSize(unsigned int p_size) {
    size = p_size;
}

int Packet::getTime_created() const {
    return time_created;
}

void Packet::setTime_created(int p_time_created) {
    time_created = p_time_created;
}

int Packet::getTime_sending_complete() const {
    return time_sending_complete;
}

void Packet::setTime_sending_complete(int p_time_sending_complete) {
    time_sending_complete = p_time_sending_complete;
}

int Packet::getTime_tx_app() const {
    return time_tx_app;
}

void Packet::setTime_tx_app(int p_time_tx_app) {
    time_tx_app = p_time_tx_app;
}

int Packet::getTime_tx_internal() const {
    return time_tx_internal;
}

void Packet::setTime_tx_internal(int p_time_tx_internal) {
    time_tx_internal = p_time_tx_internal;
}

ePacketType Packet::getType() const {
    return type;
}

void Packet::setType(ePacketType p_type) {
    type = p_type;
}

int Packet::getUpdated_load(int i1) const {
    return updated_load[i1];
}

void Packet::setUpdated_load(int i1, int p_updated_load) {
    updated_load[i1] = p_updated_load;
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/Packet.cpp
*********************************************************************/
