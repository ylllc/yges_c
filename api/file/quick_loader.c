/* † Yggdrasil Essence † */
/*!	@brief  Quick File Loader
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "./quick_loader.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
YgEsLoaded* yges_load(const char* path,bool shortable){

	YgEsLoaded* inst=NULL;
	struct stat st;
	FILE* fp;

	// detect file size 
	if(stat(path,&st)==-1)return NULL;
	fp=fopen(path,"rb");
	if(fp==NULL)return NULL;

	inst=malloc(sizeof(YgEsLoadedHead)+st.st_size+sizeof(YgEsLoadedFoot));
	if(inst){
		// try read 
		inst->filesize=st.st_size;
		inst->readsize=fread(yges_loaded_bgn(inst),1,inst->filesize,fp);
	}

	fclose(fp);
	if(!shortable && inst->readsize<inst->filesize){
		// reject incompleted load 
		yges_unload(&inst);
	}
	if(!inst)return NULL;

	// cleanup footer and misloaded area
	memset((char*)yges_loaded_bgn(inst)+inst->readsize,0,inst->filesize-inst->readsize+sizeof(YgEsLoadedFoot));
	return inst;
}

/* ----------------------------------------------------------------------- */
void yges_unload(YgEsLoaded** instp){
	if(!*instp)return;
	free(*instp);
	*instp=NULL;
}
