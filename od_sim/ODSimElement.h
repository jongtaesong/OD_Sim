/*********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: ODSimElement
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/ODSimElement.h
*********************************************************************/

#ifndef ODSimElement_H
#define ODSimElement_H

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

//## class ODSimElement
class ODSimElement {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    ODSimElement();
    
    //## auto_generated
    virtual ~ODSimElement();
    
    ////    Operations    ////
    
    //## operation add_name_string(char*)
    void add_name_string(char* name_);
    
    //## operation get_name_string()
    char* get_name_string();
    
    //## operation print_info()
    virtual void print_info() = 0;
    
    //## operation process_clock(int)
    virtual void process_clock(int clk);
    
    //## operation set_name_string(char*)
    void set_name_string(char* name_);
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getIndex() const;
    
    //## auto_generated
    void setIndex(int p_index);
    
    //## auto_generated
    char getName(int i1) const;
    
    //## auto_generated
    void setName(int i1, char p_name);
    
    ////    Attributes    ////

protected :

    int index;		//## attribute index
    
    char name[40];		//## attribute name
};

#endif
/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/ODSimElement.h
*********************************************************************/
