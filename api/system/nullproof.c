/* † Yggdrasil Essence † */
/*!	@brief  Nullproof
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "./nullproof.h"
#include "./emergency_trap.h"

const char* YgEsEmergencyCause_Nullpo="Null Pointer Trap";
int YgEsEmergencyExit_Nullpo=-100;

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
int yges_null_trap(const char* file,int line){

	int exitcode=yges_happen_emergency(YgEsEmergencyCause_Nullpo,NULL,file,line);
	return exitcode?exitcode:YgEsEmergencyExit_Nullpo;
}
