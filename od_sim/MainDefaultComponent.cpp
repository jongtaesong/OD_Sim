/********************************************************************
	Rhapsody	: 8.1.5 
	Login		: jongtaesong
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: DefaultConfig
//!	Generated Date	: Tue, 19, Mar 2024  
	File Path	: DefaultComponent/DefaultConfig/MainDefaultComponent.cpp
*********************************************************************/

//## auto_generated
#include "MainDefaultComponent.h"
//## auto_generated
#include "ODNetConfig.h"
//## auto_generated
#include "ODSim.h"
int main(int argc, char* argv[]) {
    int status = 0;
    if(OXF::initialize())
        {
            ODNetConfig * p_ODNetConfig;
            ODSim * p_ODSim;
            p_ODNetConfig = new ODNetConfig;
            p_ODSim = new ODSim;
            //#[ configuration DefaultComponent::DefaultConfig 
            p_ODSim->start_sim();
            //#]
            OXF::start();
            delete p_ODNetConfig;
            delete p_ODSim;
            status = 0;
        }
    else
        {
            status = 1;
        }
    return status;
}

/*********************************************************************
	File Path	: DefaultComponent/DefaultConfig/MainDefaultComponent.cpp
*********************************************************************/
