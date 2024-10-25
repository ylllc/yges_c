/* † Yggdrasil Essence † */
/*!	@brief  Emergency Trap
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#ifndef YGES_EMERGENCY_TRAP_H__
#define YGES_EMERGENCY_TRAP_H__

#include <stddef.h>
#include <stdbool.h>

//! emergency settings and work area 
typedef struct YgEsEmergencyContext_ YgEsEmergencyContext;

//! emergency exit hook 
typedef void (*FYgEsExitProc)(int exitcode);
extern FYgEsExitProc gYgEsExitProc;

//! emergency function type 
/*!	@param ctx  source context
	@param cause  emergency cause (should be a global string for compare by a pointer)
	@param info  emergency info (definition by each causes)
	@param file  happened source file
	@param line  happened line of the source file
	@return  exit code (0=continuable, be ignored)
*/
typedef int (*FYgEsEmergency)(YgEsEmergencyContext* ctx,const char* cause,void* info,const char* file,int line);

struct YgEsEmergencyContext_{
	YgEsEmergencyContext* _next; //!< chained one (don't write) 
	bool Enabled; //!< means this trap is callable (can rewrite) 
	FYgEsEmergency Hook; //!< calling function (can rewrite) 
	void* User; //!< user pointer (can rewrite) 
};

#ifdef __cplusplus
extern "C" {
#endif

//! register a memory emergincy settings 
/*!	@note src->Hook is called on failed memory allocation. @n

	@attention YgEsMemoryEmergency place on global memory as possible. @n
		or must call yges_remove_memory_emergency() before destruct it. @n
*/
void yges_register_emergency(YgEsEmergencyContext* ctx);

//! remove a memory emergincy settings 
/*!	@note generally, write false to src->enabled to ignore it. @n
		call this for YgEsMemoryEmergency placed on nonglobal memory 
		before destructing. @n
*/
void yges_remove_emergency(YgEsEmergencyContext* ctx);

//! call by emergency happened 
/*	@param cause  emergency cause (should be a global string for compare by a pointer)
	@param info  emergency info (definition by each causes)
	@param file  happened source file
	@param line  happened line of the source file
	@return exit code (but not exit yet)
*/
int yges_happen_emergency(const char* cause,void* info,const char* file,int line);

#ifdef __cplusplus
}
#endif

#endif // YGES_EMERGENCY_TRAP_H__
