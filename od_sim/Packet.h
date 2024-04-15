/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Packet
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/Packet.h
*********************************************************************/

#ifndef Packet_H
#define Packet_H

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

//## class Packet
class Packet {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    Packet();
    
    //## auto_generated
    ~Packet();
    
    ////    Operations    ////
    
    //## operation print_info()
    void print_info();
    
    ////    Additional operations    ////
    
    //## auto_generated
    unsigned long getAddress() const;
    
    //## auto_generated
    void setAddress(unsigned long p_address);
    
    //## auto_generated
    int getApp_id() const;
    
    //## auto_generated
    void setApp_id(int p_app_id);
    
    //## auto_generated
    char* getContent() const;
    
    //## auto_generated
    void setContent(char* p_content);
    
    //## auto_generated
    int getDevice_id() const;
    
    //## auto_generated
    void setDevice_id(int p_device_id);
    
    //## auto_generated
    int getLoad_updated() const;
    
    //## auto_generated
    void setLoad_updated(int p_load_updated);
    
    //## auto_generated
    Packet* getNext() const;
    
    //## auto_generated
    void setNext(Packet* p_next);
    
    //## auto_generated
    int getPriority() const;
    
    //## auto_generated
    void setPriority(int p_priority);
    
    //## auto_generated
    unsigned int getSize() const;
    
    //## auto_generated
    void setSize(unsigned int p_size);
    
    //## auto_generated
    int getTime_created() const;
    
    //## auto_generated
    void setTime_created(int p_time_created);
    
    //## auto_generated
    int getTime_sending_complete() const;
    
    //## auto_generated
    void setTime_sending_complete(int p_time_sending_complete);
    
    //## auto_generated
    int getTime_tx_app() const;
    
    //## auto_generated
    void setTime_tx_app(int p_time_tx_app);
    
    //## auto_generated
    int getTime_tx_internal() const;
    
    //## auto_generated
    void setTime_tx_internal(int p_time_tx_internal);
    
    //## auto_generated
    ePacketType getType() const;
    
    //## auto_generated
    void setType(ePacketType p_type);
    
    //## auto_generated
    int getUpdated_load(int i1) const;
    
    //## auto_generated
    void setUpdated_load(int i1, int p_updated_load);
    
    ////    Attributes    ////

protected :

    unsigned long address;		//## attribute address
    
    int app_id;		//## attribute app_id
    
    char* content;		//## attribute content
    
    int device_id;		//## attribute device_id
    
    int load_updated;		//## attribute load_updated
    
    Packet* next;		//## attribute next
    
    int priority;		//## attribute priority
    
    unsigned int size;		//## attribute size
    
    int time_created;		//## attribute time_created
    
    int time_sending_complete;		//## attribute time_sending_complete
    
    int time_tx_app;		//## attribute time_tx_app
    
    int time_tx_internal;		//## attribute time_tx_internal
    
    ePacketType type;		//## attribute type
    
    int updated_load[3];		//## attribute updated_load
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/Packet.h
*********************************************************************/
