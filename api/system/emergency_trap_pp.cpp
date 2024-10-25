/* † Yggdrasil Essence † */
/*!	@brief  Emergency Trap
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "./emergency_trap.hpp"


namespace yges{

	/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
	EmergencyContext::~EmergencyContext(){
		yges_remove_emergency(&mCtx);
	}

	/* ------------------------------------------------------------------- */
	EmergencyContext::EmergencyContext(){
		mCtx.Enabled=false;
		mCtx.Hook=&EmergencyContext::_on_happen;
		mCtx.User=this;
		yges_register_emergency(&mCtx);
	}

	/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
	int EmergencyContext::_on_happen(YgEsEmergencyContext* ctx,const char* cause,void* info,const char* file,int line){

		EmergencyContext* self=reinterpret_cast<EmergencyContext*>(ctx->User);
		return self->OnHappen(cause,info,file,line);
	}

} // namespace yges
