/* † Yggdrasil Essence † */
/*!	@brief  Memory Emergency Test
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "system/emergency_trap.h"
#include <stdio.h>
#include <string.h>

// trap enabled 
#define YGES_TRAP_CANTALLOC
#include "memory/safe_alloc.h"

static int ExitCode_Failure=1;
static int ExitCode_Emergency=74;

//! test emergency context 
static YgEsEmergencyContext TestEmergencyContext;

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
static int on_emergency_ctx(YgEsEmergencyContext* ctx,const char* cause,void* info,const char* file,int line){

fprintf(stderr,"emergency: %s (%s:%d)\n",cause,file,line);

	// ignore from other causes 
	if(cause!=YgEsEmergencyCause_OutOfMemory)return 0;

	// will be exited 
	return ExitCode_Emergency;
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
int main(int argc,char** argv){

	// Emergency settings 
	TestEmergencyContext.Enabled=false;
	TestEmergencyContext.Hook=on_emergency_ctx;
	TestEmergencyContext.User=NULL;
	yges_register_emergency(&TestEmergencyContext);

	// generally 
	ExitCode_Emergency=75;
	void* p=yges_quick_alloc(100);
	yges_safe_free(&p);

	// should be null; trap is disabled 
	ExitCode_Emergency=76;
	p=yges_quick_alloc(-1);
	if(p)return ExitCode_Failure;

	// should be trapped 
	ExitCode_Emergency=77;
	TestEmergencyContext.Enabled=true;
	yges_safe_alloc(-1);

	// should not step this 
	ExitCode_Emergency=78;
	return ExitCode_Failure;
}
