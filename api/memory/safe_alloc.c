/* † Yggdrasil Essence † */
/*!	@brief  Safety Memory Allocator
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "./safe_alloc.h"
#include "../system/emergency_trap.h"
#include <string.h>

const char* YgEsEmergencyCause_OutOfMemory="Out of Memory";

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
void* yges_safe_alloc_thru(size_t size){

	void* mem=malloc(size);
	if(!mem)return NULL;
	memset(mem,0,size);	
	return mem;
}

/* ----------------------------------------------------------------------- */
void* yges_quick_alloc_trap(size_t size,const char* file,int line){

	void* mem=malloc(size);
	if(mem)return mem;

	// emergency report 
	YgEsEmergencyInfo_OutOfMemory info;
	info.size=size;
	yges_happen_emergency(YgEsEmergencyCause_OutOfMemory,&info,file,line);

	return NULL;
}

/* ----------------------------------------------------------------------- */
void* yges_safe_alloc_trap(size_t size,const char* file,int line){

	void* mem=yges_safe_alloc_thru(size);
	if(mem)return mem;

	// emergency report 
	YgEsEmergencyInfo_OutOfMemory info;
	info.size=size;
	yges_happen_emergency(YgEsEmergencyCause_OutOfMemory,&info,file,line);

	return NULL;
}
