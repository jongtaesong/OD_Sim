/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: ODSimElement
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/ODSimElement.cpp
*********************************************************************/

//## auto_generated
#include "ODSimElement.h"
//## auto_generated
#include <iostream>
//## package Default

//## class ODSimElement
ODSimElement::ODSimElement() {
}

ODSimElement::~ODSimElement() {
}

void ODSimElement::add_name_string(char* name_) {
    //#[ operation add_name_string(char*)
    char temp[40];
    sprintf(name, "%s-%s", name, name_);
    
    //#]
}

char* ODSimElement::get_name_string() {
    //#[ operation get_name_string()
    return name;
    
    //#]
}

void ODSimElement::process_clock(int clk) {
    //#[ operation process_clock(int)
    //#]
}

void ODSimElement::set_name_string(char* name_) {
    //#[ operation set_name_string(char*)
    sprintf(name, "%s", name_);
    
    //#]
}

int ODSimElement::getIndex() const {
    return index;
}

void ODSimElement::setIndex(int p_index) {
    index = p_index;
}

char ODSimElement::getName(int i1) const {
    return name[i1];
}

void ODSimElement::setName(int i1, char p_name) {
    name[i1] = p_name;
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/ODSimElement.cpp
*********************************************************************/
