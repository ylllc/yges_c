/* † Yggdrasil Essence † */
/*!	@brief  Emergency Trap
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#ifndef YGES_EMERGENCY_TRAP_HPP__
#define YGES_EMERGENCY_TRAP_HPP__

#include "./emergency_trap.h"
#include "./dontcopy.hpp"

namespace yges{

	//! emergency context 
	/*!	@brief  call OnHappen() by yges_happen_emergency() called. @n 
		@sa  YgEsEmergencyContext
		@note  calls yges_register_emergency() and
			yges_remove_emergency() automatically. @n
			starting in disabled, 
			need calling Enable() to enable. @n
	*/
	class EmergencyContext: DontCopy{
		public:
		virtual ~EmergencyContext();
		EmergencyContext();

		//! enable this 
		inline void Enable(){mCtx.Enabled=true;}
		//! disable this 
		inline void Disable(){mCtx.Enabled=false;}

		protected:

		//! call by emergency happened 
		/*!	@param cause  emergency cause (should be a global string for compare by a pointer)
			@param info  emergency info (definition by each causes)
			@param file  happened source file
			@param line  happened line of the source file
			@return  exit code (0=continuable, be ignored)
		*/
		virtual int OnHappen(const char* cause,void* info,const char* file,int line){return 0;}

		private:
		static int _on_happen(YgEsEmergencyContext* ctx,const char* cause,void* info,const char* file,int line);

		YgEsEmergencyContext mCtx;
	};

} // namespace yges

#endif // YGES_EMERGENCY_TRAP_HPP__
