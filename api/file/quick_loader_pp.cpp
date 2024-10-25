/* † Yggdrasil Essence † */
/*!	@brief  Quick File Loader
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "./quick_loader.hpp"

namespace yges{

	/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
	FileImage::~FileImage(){

		Unload();
	}

	/* ------------------------------------------------------------------- */
	FileImage::FileImage(YgEsLoaded* loaded){

		mpLoaded=loaded;
	}

	/* ------------------------------------------------------------------- */
	FileImage::FileImage(const char* path,bool shortable){

		mpLoaded=yges_load(path,shortable);
	}

	/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
	FileImage* FileImage::Load(const char* path,bool shortable){

		YgEsLoaded* img=yges_load(path,shortable);
		if(!img)return NULL;
		return new FileImage(img);
	}

} // namespace yges
