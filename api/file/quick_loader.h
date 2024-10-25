/* † Yggdrasil Essence † */
/*!	@brief  Quick File Loader
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#ifndef YGES_QUICK_LOADER_H__
#define YGES_QUICK_LOADER_H__

#include <stddef.h>
#include <stdbool.h>

//! Loaded header block 
typedef struct YgEsLoadedHead_ YgEsLoadedHead;
//! Loaded footer block 
typedef struct YgEsLoadedFoot_ YgEsLoadedFoot;
//! Loaded instance 
typedef YgEsLoadedHead YgEsLoaded;

struct YgEsLoadedHead_{
	size_t filesize; //!< file size 
	size_t readsize; //!< read size 
};

/*!	@note loaded text file can use as standard C string
*/
struct YgEsLoadedFoot_{
	char zero[8]; //!< fill with zero 
};

#ifdef __cplusplus
extern "C" {
#endif

//! load a file 
/*!	@param path  target file
	@param shortable  allow incompleted load
	@return  header pointer of loaded file (or NULL)
*/
YgEsLoaded* yges_load(const char* path,bool shortable);

//! free YgEsLoaded file 
/*!	@param instp  pointer of stored from yges_load()
	@note  free target memory and instance pointer be NULL
*/
void yges_unload(YgEsLoaded** instp);

//! get first pointer of loaded body 
inline void* yges_loaded_bgn(YgEsLoaded* inst){
	return inst+1;
}

//! get terminate pointer of loaded body 
inline void* yges_loaded_end(YgEsLoaded* inst){
	return (char*)yges_loaded_bgn(inst)+inst->readsize;
}

//! get footer pointer of loaded body 
inline YgEsLoadedFoot* yges_loaded_foot(YgEsLoaded* inst){
	return (YgEsLoadedFoot*)((char*)yges_loaded_bgn(inst)+inst->filesize);
}

#ifdef __cplusplus
}
#endif

#endif // YGES_QUICK_LOADER_H__
