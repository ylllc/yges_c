/* † Yggdrasil Essence † */
/*!	@brief  Quick File Loader Test
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "file/quick_loader.h"
#include <stdio.h>
#include <string.h>

static int ExitCode_Failure=1;

//! same to test.txt 
static const char* testext="q2w3e4r5t6y7u8i9o0p-@^[\naqwsderftgyhujikolp;@:\nazsxdcfvgbhnjmk,l.;/:\n";

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
int main(int argc,char** argv){

	// load a file 
	YgEsLoaded* file=yges_load("./test.txt",false);

	// check file size 
	size_t len=strlen(testext);
	if(len!=file->filesize)return ExitCode_Failure;
	// check read size 
	// (may short from file size) 
	if(len!=file->readsize)return ExitCode_Failure;

	// loaded data auto 0 terminated 
	if(*(char*)yges_loaded_end(file))return ExitCode_Failure;

	// loaded data referable from yges_loaded_bgn(file) 
	// and can use as a string directly. 
	if(strcmp(testext,yges_loaded_bgn(file)))return ExitCode_Failure;

	// unload 
	yges_unload(&file);

	return 0;
}
