/* † Yggdrasil Essence † */
/*!	@brief  Emergency Test
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "system/emergency_trap.h"
#include <stdio.h>
#include <stdlib.h>

static const char* EmergencyCause_Test="TestEmergency";
static int ExitCode_Emergency=0;
static int ExitCode_Failure=1;

//! test emergency context 1 
static YgEsEmergencyContext MyEmergency1;
//! test emergency context 2 
static YgEsEmergencyContext MyEmergency2;

//! context 1 emergency info 
typedef struct TestScn_system_emergency_Emergency1Info_ TestScn_system_emergency_Emergency1Info;
struct TestScn_system_emergency_Emergency1Info_{
	int Boo;
};

//! context 2 emergency info 
typedef struct TestScn_system_emergency_Emergency2Info_ TestScn_system_emergency_Emergency2Info;
struct TestScn_system_emergency_Emergency2Info_{
	int Hoo;
};

//! user emergency info 
typedef struct TestScn_system_emergency_HappenInfo_ TestScn_system_emergency_HappenInfo;
struct TestScn_system_emergency_HappenInfo_{
	int Woo;
};

static TestScn_system_emergency_Emergency1Info Ctx1Info;
static TestScn_system_emergency_Emergency2Info Ctx2Info;

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
static int on_emergency_ctx1(YgEsEmergencyContext* ctx,const char* cause,void* info,const char* file,int line){

	// ignore from other causes 
	if(cause!=EmergencyCause_Test)return 0;

	TestScn_system_emergency_HappenInfo* info_t=info;
	++info_t->Woo;
	TestScn_system_emergency_Emergency1Info* into_c=ctx->User;
	++into_c->Boo;

	return ExitCode_Emergency;
}

/* ----------------------------------------------------------------------- */
static int on_emergency_ctx2(YgEsEmergencyContext* ctx,const char* cause,void* info,const char* file,int line){

	// ignore from other causes 
	if(cause!=EmergencyCause_Test)return 0;

	TestScn_system_emergency_HappenInfo* info_t=info;
	++info_t->Woo;
	TestScn_system_emergency_Emergency2Info* into_c=ctx->User;
	++into_c->Hoo;

	// means always continuable 
	return 0;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
static void myexit(int exitcode){

	exit(exitcode*2);
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
int main(){

	// Emergency exit function 
	gYgEsExitProc=myexit;

	// Emergency Settings 
	Ctx1Info.Boo=0;
	Ctx2Info.Hoo=0;

	MyEmergency1.Enabled=true;
	MyEmergency1.Hook=on_emergency_ctx1;
	MyEmergency1.User=&Ctx1Info;
	yges_register_emergency(&MyEmergency1);

	MyEmergency2.Enabled=false;
	MyEmergency2.Hook=on_emergency_ctx2;
	MyEmergency2.User=&Ctx2Info;
	yges_register_emergency(&MyEmergency2);

	ExitCode_Emergency=0;

	// Emergency Happened 
	TestScn_system_emergency_HappenInfo info;
	info.Woo=0;
	yges_happen_emergency(EmergencyCause_Test,&info,__FILE__,__LINE__);

	// ctx2 is disabled; calls only ctx1 
	if(Ctx1Info.Boo!=1)return ExitCode_Failure;
	if(Ctx2Info.Hoo!=0)return ExitCode_Failure;
	if(info.Woo!=1)return ExitCode_Failure;

	MyEmergency2.Enabled=true;
	yges_happen_emergency(EmergencyCause_Test,&info,__FILE__,__LINE__);

	// both ctx enabled 
	if(Ctx1Info.Boo!=2)return ExitCode_Failure;
	if(Ctx2Info.Hoo!=1)return ExitCode_Failure;
	if(info.Woo!=3)return ExitCode_Failure;

	ExitCode_Emergency=123;
	yges_remove_emergency(&MyEmergency1);
	yges_happen_emergency(EmergencyCause_Test,&info,__FILE__,__LINE__);

	// ctx1 is removed; calls only ctx2 
	if(Ctx1Info.Boo!=2)return ExitCode_Failure;
	if(Ctx2Info.Hoo!=2)return ExitCode_Failure;
	if(info.Woo!=4)return ExitCode_Failure;

	yges_register_emergency(&MyEmergency1);
	yges_happen_emergency(EmergencyCause_Test,&info,__FILE__,__LINE__);

	// ctx1 is reregistered and exit from the trap; should not step this 
	return ExitCode_Failure;
}
