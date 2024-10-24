/* † Yggdrasil Essence † */
/*!	@brief  Nullproof
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c

	@pre  define YGES_NULL_TRAP before include this to hook EmergencyTrap
	@pre  define YGES_NULL_REPORT and indicate function name before include this
		to report by null detection
*/
#ifndef YGES_NULLPROOF_H__
#define YGES_NULLPROOF_H__

//! call by reporting null detected 
/*!	@param file  caller source file
	@param line  caller line of the source file
	@return  dummy for another return value
*/
typedef int (*FYgEsNullReport)(const char* file,int line);

//! emergency cause of null trap 
extern const char* YgEsEmergencyCause_Nullpo;
//! exit code of null trap 
extern int YgEsEmergencyExit_Nullpo;

#if defined(YGES_NULL_REPORT)
// report by null 
#define yges_nullproof(p) ((p)?0:1|YGES_NULL_REPORT(__FILE__,__LINE__))
#elif defined(YGES_NULL_TRAP)
// trap by null 
#define yges_nullproof(p) ((p)?0:yges_null_trap(__FILE__,__LINE__))
#else
//! null checking 
/*!	@param p  checking pointer
	@return  exit code (0 is safe and not exit)
	@pre  define YGES_NULL_TRAP or YGES_NULL_REPORT before include this or ignored
*/
#define yges_nullproof(p) ((p)?0:YgEsEmergencyExit_Nullpo)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//! always trap (by null) 
/*!	@param file  caller source file
	@param line  caller line of the source file
	@return  exit code (but not exit)
*/
int yges_null_trap(const char* file,int line);

#ifdef __cplusplus
}
#endif

#endif // YGES_NULLPROOF_H__
