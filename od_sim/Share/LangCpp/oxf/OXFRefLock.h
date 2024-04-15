//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OXFRefLock
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2008. All Rights Reserved.
//


#ifndef OXFRefLock_H
#define OXFRefLock_H

//## class OXFRefLock
#include "OMResourceGuard.h"
//## dependency OXFRefManager
#include "OXFRefManager.h"
//## package Design::oxf::Services::Guards::DllGuards

//## class OXFRefLock

//#[ ignore
#ifdef FRAMEWORK_DLL

//#]


// enter-exit guard for OXFRefManager
typedef OMResourceGuard<OXFRefManager> OXFRefLock;


//#[ ignore

#endif // FRAMEWORK_DLL
//#]

//## package Design::oxf::Services::Guards::DllGuards

//## class OXFRefLock

//#[ ignore
#ifdef FRAMEWORK_DLL

//#]




//#[ ignore

#endif //FRAMEWORK_DLL
//#]

#endif
//
//! Log: $Log$
//


