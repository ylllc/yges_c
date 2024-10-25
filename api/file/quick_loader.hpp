/* † Yggdrasil Essence † */
/*!	@brief  Quick File Loader
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#ifndef YGES_QUICK_LOADER_HPP__
#define YGES_QUICK_LOADER_HPP__

#include "./quick_loader.h"

namespace yges{

	//! keep a loaded file image 
	/*!	@note  auto unloading at end of the instance. 
	*/
	class FileImage{
		public:
		virtual ~FileImage();

		//! load a file 
		/*!	@param path  target file
			@param shortable  allow incompleted load
			@attention  of course, an instance always created.
				call IsAvailable() to confirm this loading.
		*/
		FileImage(const char* path,bool shortable);

		//! load a file 
		/*!	@param path  target file
			@param shortable  allow incompleted load
			@return  instance pointer (or NULL)
		*/
		static FileImage* Load(const char* path,bool shortable);

		//! unload the file image. 
		inline void Unload(){
			yges_unload(&mpLoaded);
		}

		//! check available 
		inline bool IsAvailable() const{return !!mpLoaded;}
		//! file size 
		inline size_t GetFileSize() const{return mpLoaded?mpLoaded->filesize:0;}
		//! read size (may short from file size) 
		inline size_t GetReadSize() const{return mpLoaded?mpLoaded->readsize:0;}

		//! begin side of the data 
		template <typename T>
		inline const T* GetBegin() const{return reinterpret_cast<const T*>(mpLoaded?yges_loaded_bgn(mpLoaded):NULL);}
		//! end side of the data 
		template <typename T>
		inline const T* GetEnd() const{return reinterpret_cast<const T*>(mpLoaded?yges_loaded_end(mpLoaded):NULL);}

		protected:
		FileImage(YgEsLoaded* loaded);

		private:
		YgEsLoaded* mpLoaded;
	};

} // namespace yges

#endif // YGES_QUICK_LOADER_HPP__
