/* † Yggdrasil Essence † */
/*!	@brief  Safety Memory Allocator
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "./safe_alloc.h"
#include <string.h>

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
void* yges_safe_alloc(size_t size){

	void* mem=malloc(size);
	memset(mem,0,size);	
	return mem;
}
