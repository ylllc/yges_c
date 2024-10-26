/* † Yggdrasil Essence † */
/*!	@brief  Don't Copy
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#ifndef YGES_DONTCOPY_HPP__
#define YGES_DONTCOPY_HPP__

namespace yges{

	class DontCopy{
		protected:
		// can construct from only inherited class 
		inline DontCopy(){}

		private:
		// inherited class cannot copy 
		inline DontCopy(const DontCopy& src){}
		// inherited class cannot substitute 
		inline const DontCopy& operator=(const DontCopy& src){return *this;}
	};

} // namespace yges

#endif // YGES_DONTCOPY_HPP__
