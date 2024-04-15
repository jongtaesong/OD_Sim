#ifndef OMOSCONFIG_H
#define OMOSCONFIG_H "$Id: omosconfig.h 1.19 2007/03/26 13:54:21 ilvler Exp $"
//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/osconfig/Linux/rcs/omosconfig.h $
//	file version:	$Revision: 1.19 $
//
//	purpose:	 	Linux adaptor OS configuration file
//
//
//	author(s):		Amos Ortal
//
//	date started:	July 2002
//
//	date changed:	$Date: 2007/03/26 13:54:21 $
//	last change by:	$Author: ilvler $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2002, 2008. All Rights Reserved.
//

//////////////////////////////////
// flags
//////////////////////////////////

#define OM_CATCH_SIGBUS
#define OM_STD_IFSTREAM_CREATION
#define OM_OS_SSTREAM_FILE_NAME
#define OM_STL
#define OM_USE_STL_STRING_STREAM
#define OM_NO_TYPENAME_SUPPORT
#define OM_NEED_THROW_IN_NEW_OPERATOR
#define OM_OPTIMIZE_REACTIVE_ACTIVE_DESTRUCTION
#define OM_NO_SEM_TIMEDWAIT_SUPPORT
// #define OM_USE_TIMEOUT_LATENCY_CORRECTION
#ifdef OM_USE_TIMEOUT_LATENCY_CORRECTION
#include <sys/time.h>
#define OM_GET_CURRENT_TIME \
static OxfTimeUnit OMGetTimeOfDay () \
{ \
	struct timeval tv; \
	gettimeofday(&tv,NULL); \
	return (tv.tv_sec*1000 + tv.tv_usec/1000); \
}
#else
#define OM_GET_CURRENT_TIME 
#endif

// #define OM_TIMER_CORRECTION_NEEDED

// -lrt library should be added to application link command, 
// if the next definition is not commented out 
// #define OM_USE_SYSTEM_TIMER


// if user wants to implement LinuxThread::suspend
//	and LinuxThread::resume services, he should uncomment the 
//	following definition
//#define OM_POSIX_THREAD_SUSPEND_RESUME_SUPPORT
// Linux exit() calls destructors of global objects.
// It allows to avoid hanging application while quit command
#define NO_NOTIFY_DESTRUCTOR_IN_END_APPLICATION 

#ifdef __GNUC__
#define OMUseNullBlockContainer

#else // !__GNUC__
#define HAS_EXP_NOT_CATCHING_SIGNALS
#endif // __GNUC__

//////////////////////////////////
// includes
//////////////////////////////////
#include <unistd.h>
#include <stdio.h>

#ifdef _WINDU_SOURCE
// Needed for smooth porting to UNIX under Bristol
#include <windu_platform.h>
#endif

//////////////////////////////////
// Macros
//////////////////////////////////
#define OMitoa(val,str,radix) sprintf(str,"%d",(int)val)

#define OM_SEARCH_ENV(name,searchpath,path) 
#include <pthread.h>

#ifdef OMOMATE
typedef  long long gen_ptr;
#else
typedef  void * gen_ptr;
#endif
typedef pthread_t OMOSHandle;
typedef enum {OMPwrModeNone = 0}  OMPowerMode_t;

#endif // OMOSCONFIG_H

//$Log: omosconfig.h $
//Revision 1.19  2007/03/26 13:54:21  ilvler
//99600 - usage of iostream for x2String implementation forbidden again.
//Revision 1.18  2007/03/11 12:51:33  ilgiga
//Change copyright comment
//Revision 1.17  2007/03/01 16:23:29  ilgiga
//Telelogic instead of i-Logix
//Revision 1.16  2006/07/06 06:20:09  eldad
//Allow use of streams for serialization methods in omCom in Linux and Cygwin
//Revision 1.15.1.1  2006/06/13 10:14:56  eldad
//Duplicate revision
//Revision 1.14  2006/04/04 08:30:36  vova
//Spelling fixed
//Revision 1.13  2006/03/20 12:22:52  amos
//Replace UseNullBlockContainter with OMUseNullBlockContainer
//Revision 1.12  2005/03/28 15:24:27  vova
//Commented out OM_POSIX_THREAD_SUSPEND_RESUME_SUPPORT  added
//Revision 1.11  2004/08/17 13:53:21  vova
//74625,72921: endApplication hanging : no need to notify about object destruction
//Revision 1.10  2004/08/04 11:27:58  amos
//Add OM_NEED_THORW_IN_NEW_OPERATOR compilation flag to enable thorw() in the new operators
//Revision 1.8  2004/05/11 14:24:18  vova
//Linux sstream file name usage
//Revision 1.6  2004/04/18 07:44:52  yaniv
//Linux
//Revision 1.4  2004/01/21 08:26:41  eldad
//Fix build
//Revision 1.3  2004/01/19 14:00:21  eldad
//OM_SEARCH_ENV
//Revision 1.2  2003/01/09 12:31:47  Eldad
//Fix b#61053
//Revision 1.1  2002/07/09 11:25:38  amos
//Initial revision
