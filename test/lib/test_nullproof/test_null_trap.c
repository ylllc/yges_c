/* † Yggdrasil Essence † */
/*!	@brief  Null Test: Trapping
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "./test_null_trap.h"
#include <stdlib.h>

// to trap by null detection 
#define YGES_NULL_TRAP
#include "system/nullproof.h"

void test_null_trap(void* src){

	if(yges_nullproof(src))return;

	// can access to src, or abend 
	if(!src)exit(YgEsEmergencyExit_Nullpo);
}
