/* † Yggdrasil Essence † */
/*!	@brief  Null Test: Throughing
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "./test_null_thru.h"
#include <stdlib.h>

// including simply 
// yges_nullproof() checks only  
#include "system/nullproof.h"

void test_null_thru(void* src){

	if(yges_nullproof(src))return;

	// can access to src, or abend 
	if(!src)exit(YgEsEmergencyExit_Nullpo);
}
