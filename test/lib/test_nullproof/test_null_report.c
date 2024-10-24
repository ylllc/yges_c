/* † Yggdrasil Essence † */
/*!	@brief  Null Test: Reporting
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "./test_null_report.h"
#include <stdlib.h>
#include <stdio.h>

// to trap by null detection 
#define YGES_NULL_REPORT null_reporting
#include "system/nullproof.h"

int Test_NullReported=0;

static int null_reporting(const char* file,int line){

//	printf("null detected in %s:%d\n",file,line);

	++Test_NullReported;
	return 0;
}

void test_null_report(void* src){

	if(yges_nullproof(src))return;

	// can access to src, or abend 
	if(!src)exit(YgEsEmergencyExit_Nullpo);
}
