/* † Yggdrasil Essence † */
/*!	@brief  C++ Emergency Test
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "system/emergency_trap.hpp"
#include <stdio.h>

static const char* EmergencyCause_Test="TestEmergency++";
static int ExitCode_Emergency=99;
static int ExitCode_Failure=1;

//! test Emergency class 
class TestScn_system_emergency_pp_EmergencyContext:public yges::EmergencyContext{
	protected:
	int OnHappen(const char* cause,void* info,const char* file,int line){

		if(cause!=EmergencyCause_Test)return 0;

		return ExitCode_Emergency;
	}
};

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
static void scope_emergency(){

	TestScn_system_emergency_pp_EmergencyContext emergency;

	// emergency is disabled 
	// this happening will be ignored 
	yges_happen_emergency(EmergencyCause_Test,NULL,__FILE__,__LINE__);

	// need Enable() 
	emergency.Enable();
	ExitCode_Emergency=98;
	yges_happen_emergency(EmergencyCause_Test,NULL,__FILE__,__LINE__);
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
int main(){

	scope_emergency();

	// should not step this 
	return ExitCode_Failure;
}
