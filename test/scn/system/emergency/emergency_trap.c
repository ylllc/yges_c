/* † Yggdrasil Essence † */
/*!	@brief  Emergency Test
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "system/emergency_trap.h"
#include <stdio.h>
#include <stdlib.h>

static const char* EmergencyTest_Cause="TestEmergency";
static int ExitCode_Emergency=0;
static int ExitCode_Failure=1;

//! test emergency context 1 
static YgEsEmergencyContext TestEmergencyContext1;
//! test emergency context 2 
static YgEsEmergencyContext TestEmergencyContext2;

//! context 1 emergency info 
typedef struct EmergencyCtx1Info_ EmergencyCtx1Info;
struct EmergencyCtx1Info_{
	int Boo;
};

//! context 2 emergency info 
typedef struct EmergencyCtx2Info_ EmergencyCtx2Info;
struct EmergencyCtx2Info_{
	int Hoo;
};

//! user emergency info 
typedef struct EmergencyTestInfo_ EmergencyTestInfo;
struct EmergencyTestInfo_{
	int Woo;
};

static EmergencyCtx1Info Ctx1Info;
static EmergencyCtx2Info Ctx2Info;

static int on_emergency_ctx1(YgEsEmergencyContext* ctx,const char* cause,void* info,const char* file,int line){

	// ignore from other causes 
	if(cause!=EmergencyTest_Cause)return 0;

	EmergencyTestInfo* info_t=info;
	++info_t->Woo;
	EmergencyCtx1Info* into_c=ctx->User;
	++into_c->Boo;

	return ExitCode_Emergency;
}

static int on_emergency_ctx2(YgEsEmergencyContext* ctx,const char* cause,void* info,const char* file,int line){

	// ignore from other causes 
	if(cause!=EmergencyTest_Cause)return 0;

	EmergencyTestInfo* info_t=info;
	++info_t->Woo;
	EmergencyCtx2Info* into_c=ctx->User;
	++into_c->Hoo;

	// means always continuable 
	return 0;
}

static void myexit(int exitcode){

	exit(exitcode*2);
}

int main(){

	// Emergency exit function 
	gYgEsExitProc=myexit;

	// Emergency Settings 
	Ctx1Info.Boo=0;
	Ctx2Info.Hoo=0;

	TestEmergencyContext1.Enabled=true;
	TestEmergencyContext1.Hook=on_emergency_ctx1;
	TestEmergencyContext1.User=&Ctx1Info;
	yges_register_emergency(&TestEmergencyContext1);

	TestEmergencyContext2.Enabled=false;
	TestEmergencyContext2.Hook=on_emergency_ctx2;
	TestEmergencyContext2.User=&Ctx2Info;
	yges_register_emergency(&TestEmergencyContext2);

	ExitCode_Emergency=0;

	// Emergency Happened 
	EmergencyTestInfo info;
	info.Woo=0;
	yges_happen_emergency(EmergencyTest_Cause,&info,__FILE__,__LINE__);

	// ctx2 is disabled; calls only ctx1 
	if(Ctx1Info.Boo!=1)return ExitCode_Failure;
	if(Ctx2Info.Hoo!=0)return ExitCode_Failure;
	if(info.Woo!=1)return ExitCode_Failure;

	TestEmergencyContext2.Enabled=true;
	yges_happen_emergency(EmergencyTest_Cause,&info,__FILE__,__LINE__);

	// both ctx enabled 
	if(Ctx1Info.Boo!=2)return ExitCode_Failure;
	if(Ctx2Info.Hoo!=1)return ExitCode_Failure;
	if(info.Woo!=3)return ExitCode_Failure;

	ExitCode_Emergency=123;
	yges_remove_emergency(&TestEmergencyContext1);
	yges_happen_emergency(EmergencyTest_Cause,&info,__FILE__,__LINE__);

	// ctx1 is removed; calls only ctx2 
	if(Ctx1Info.Boo!=2)return ExitCode_Failure;
	if(Ctx2Info.Hoo!=2)return ExitCode_Failure;
	if(info.Woo!=4)return ExitCode_Failure;

	yges_register_emergency(&TestEmergencyContext1);
	yges_happen_emergency(EmergencyTest_Cause,&info,__FILE__,__LINE__);

	// ctx1 is reregistered and exit from the trap; should not step this 
	return ExitCode_Failure;
}
