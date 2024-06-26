//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfEvent
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2008. All Rights Reserved.
//


#ifndef IOxfEvent_H
#define IOxfEvent_H

//## dependency MISRA_Cpp_Types
#include "OXFMISRA_Cpp_Types.h"
//## dependency Types
#include "OXFTypes.h"
//## link destination
class IOxfReactive;

//## package Design::oxf::Core::CoreAPI

//## class IOxfEvent
// An event (signal/message) interface.
// Events are used for synchronous and asynchronous messaging.
class RP_FRAMEWORK_DLL IOxfEvent {
public :

    // An event id attribute type
    //## type ID
    typedef Rhp_int16_t ID;
    
    ////    Constructors and destructors    ////
    
    // Virtual destructor to enable polymorphic deletion
    //## operation ~IOxfEvent()
    inline virtual ~IOxfEvent(void) {
        //#[ operation ~IOxfEvent()
        //#]
    }
    
    ////    Operations    ////
    
    // destroy the event
    //## operation destroy()
    virtual void destroy(void) = 0;
    
    //## operation isFrameworkEvent() const
    virtual bool isFrameworkEvent(void) const = 0;
    
    // check if the event is a sub-type of an event with the specified id
    // Argument const ID eventId :
    // The event id to test
    //## operation isTypeOf(ID) const
    virtual bool isTypeOf(const ID eventId) const = 0;
    
    ////    Additional operations    ////
    
    //## auto_generated
    virtual ID getId(void) const = 0;
    
    //## auto_generated
    virtual void setId(ID p_id) = 0;
    
    //## auto_generated
    virtual void * getPort(void) const = 0;
    
    //## auto_generated
    virtual void setPort(void * const p_port) = 0;
    
    //## auto_generated
    virtual bool getSynchronous(void) const = 0;
    
    //## auto_generated
    virtual void setSynchronous(bool p_synchronous) = 0;
    
    //## auto_generated
    virtual IOxfReactive* getDestination(void) const = 0;
    
    //## auto_generated
    virtual void setDestination(IOxfReactive* p_IOxfReactive) = 0;
    
};

#endif
//
//! Log: $Log$
//


