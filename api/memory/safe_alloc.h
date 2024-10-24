/* † Yggdrasil Essence † */
/*!	@brief  Safety Memory Allocator
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c

	@pre  define YGES_TRAP_CANTALLOC before include this
		to hook to report emergency
*/
#ifndef YGES_SAFE_ALLOC_H__
#define YGES_SAFE_ALLOC_H__

#include <stddef.h>
#include <stdlib.h>

//! emergency info for Out of Memory 
typedef struct YgEsEmergencyInfo_OutOfMemory_ YgEsEmergencyInfo_OutOfMemory;

//! Emergency cause: Out of Memory 
extern const char* YgEsEmergencyCause_OutOfMemory;


struct YgEsEmergencyInfo_OutOfMemory_{
	size_t size; //!< trying size 
};


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

#ifdef YGES_TRAP_CANTALLOC
#define yges_quick_alloc(size) yges_quick_alloc_trap(size,__FILE__,__LINE__)
#define yges_safe_alloc(size) yges_safe_alloc_trap(size,__FILE__,__LINE__)
#else

//! quick memory allocator 
/*!	@param size  memory size
	@return  allocated memory block (or NULL)
	@note  allocate a dirty memory block. @n
		you must fully initialize it. @n
	@note  define YGES_TRAP_CANTALLOC before include this
		to hook to report emergency
*/
#define yges_quick_alloc(size) malloc(size)

/*!	@param size  memory size
	@return  allocated memory block (or NULL)
	@note  allocate a memory block and clear to zero
	@note  define YGES_TRAP_CANTALLOC before include this
		to hook to report emergency
*/
#define yges_safe_alloc(size) yges_safe_alloc_thru(size)

#endif

#ifdef __cplusplus
extern "C" {
#endif

//! trappable yges_quick_alloc() 
void* yges_quick_alloc_trap(size_t size,const char* file,int line);

//! untrappable yges_safe_alloc() 
void* yges_safe_alloc_thru(size_t size);
//! trappable yges_safe_alloc() 
void* yges_safe_alloc_trap(size_t size,const char* file,int line);

#ifdef __cplusplus
}
#endif

#endif // YGES_SAFE_ALLOC_H__
