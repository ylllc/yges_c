/* † Yggdrasil Essence † */
/*!	@brief  Emergency Trap
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "./emergency_trap.h"
#include <stdlib.h>

FYgEsExitProc gYgEsExitProc=NULL;

static YgEsEmergencyContext* EmergencyStack=NULL;

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
void yges_register_emergency(YgEsEmergencyContext* src){

	if(!src)return;

	// link to EmergencyStack 
	src->_next=NULL;
	if(EmergencyStack)EmergencyStack->_next=src;
	else EmergencyStack=src;
}

/* ----------------------------------------------------------------------- */
void yges_remove_emergency(YgEsEmergencyContext* src){

	if(!src)return;

	YgEsEmergencyContext* prev=NULL;
	for(YgEsEmergencyContext* ctx=EmergencyStack;ctx;prev=ctx,ctx=ctx->_next){
		if(ctx!=src)continue;

		// unchain it 
		if(prev)prev->_next=ctx->_next;
		else EmergencyStack=ctx->_next;
		ctx->_next=NULL;
	}
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
int yges_happen_emergency(const char* cause,void* info,const char* file,int line){

	// true to exit 
	int exitcode=0;

	// call traps in chained 
	for(YgEsEmergencyContext* ctx=EmergencyStack;ctx;ctx=ctx->_next){
		if(!ctx->Enabled)continue;
		int code=ctx->Hook(ctx,cause,info,file,line);
		if(!exitcode)exitcode=code;
	}

	if(exitcode){
		if(gYgEsExitProc)gYgEsExitProc(exitcode);
		else exit(exitcode);
	}

	return exitcode;
}
