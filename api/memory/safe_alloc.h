/* † Yggdrasil Essence † */
/*!	@brief  Safety Memory Allocator
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#ifndef YGES_SAFE_ALLOC_H__
#define YGES_SAFE_ALLOC_H__

#include <stddef.h>
#include <stdlib.h>

//! safety memory freer 
/*!	@param memp  target var pointer of stored instance pointer
	@note  free target memory and instance pointer be NULL
*/
#define yges_safe_free(memp) { \
		if(*memp){ \
			free(*memp); \
			*memp=NULL; \
		} \
	}


#ifdef __cplusplus
extern "C" {
#endif

//! safety mamory allocator 
/*!	@param size  memory size
	@return  allocated memory block (or NULL)
	@note  allocate a memory block and clear to zero
*/
void* yges_safe_alloc(size_t size);

#ifdef __cplusplus
}
#endif

#endif // YGES_SAFE_ALLOC_H__
