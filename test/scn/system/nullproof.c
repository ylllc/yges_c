/* † Yggdrasil Essence † */
/*!	@brief  Nullproof Test
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include <stddef.h>
#include <stdio.h>
#include "system/emergency_trap.h"
#include "test_nullproof/test_null_thru.h"
#include "test_nullproof/test_null_trap.h"
#include "test_nullproof/test_null_report.h"

// emergency cause of nullproof 
extern const char* YgEsEmergencyCause_Nullpo;
// indicate null reporting 
extern int Test_NullReported;

static int ExitCode_Failure=1;

//! test emergency context 
static YgEsEmergencyContext TestEmergencyContext;

//! test emergency info 
typedef struct EmergencyInfo_ EmergencyInfo;
struct EmergencyInfo_{
	int Called;
};
static EmergencyInfo TestEmergencyInfo;

static int on_emergency(YgEsEmergencyContext* ctx,const char* cause,void* info,const char* file,int line){

	// ignore from other causes 
	if(cause!=YgEsEmergencyCause_Nullpo)return 0;

	EmergencyInfo* info_c=ctx->User;
	++info_c->Called;

	return 0;
}

int main(){

	// emergency settings 
	TestEmergencyContext.Enabled=true;
	TestEmergencyContext.Hook=on_emergency;
	TestEmergencyContext.User=&TestEmergencyInfo;
	TestEmergencyInfo.Called=0;
	yges_register_emergency(&TestEmergencyContext);

	// null check only 
	test_null_thru(NULL);
	// on_emergency should not called yet 
	if(TestEmergencyInfo.Called!=0)return ExitCode_Failure;
	// not reported yet 
	if(Test_NullReported!=0)return ExitCode_Failure;

	// trap by null detection 
	test_null_trap(NULL);
	// on_emergency should called 
	if(TestEmergencyInfo.Called!=1)return ExitCode_Failure;
	// not reported yet 
	if(Test_NullReported!=0)return ExitCode_Failure;

	// not null; should not trap 
	test_null_trap(&TestEmergencyInfo);
	// on_emergency should not called now 
	if(TestEmergencyInfo.Called!=1)return ExitCode_Failure;
	// not reported yet 
	if(Test_NullReported!=0)return ExitCode_Failure;

	// report by null detection 
	test_null_report(NULL);
	// should reported now 
	if(Test_NullReported!=1)return ExitCode_Failure;

	// not null; should not report 
	test_null_report(&TestEmergencyInfo);
	// not reported now 
	if(Test_NullReported!=1)return ExitCode_Failure;

	return 0;
}
