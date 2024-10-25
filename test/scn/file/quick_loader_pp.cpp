/* † Yggdrasil Essence † */
/*!	@brief  Quick File Loader Test
	@author  Copyright © 2024 Yggdrasil Leaves, LLC.
	@sa  https://github.com/ylllc/yges_c
*/
#include "file/quick_loader.hpp"
#include <stdio.h>
#include <string.h>

static int ExitCode_Failure=1;

//! same to test.txt 
static const char* testext="q2w3e4r5t6y7u8i9o0p-@^[\naqwsderftgyhujikolp;@:\nazsxdcfvgbhnjmk,l.;/:\n";

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
int main(int argc,char** argv){

	// load a file. 
	// it's auto unloading at end of the instance. 
	yges::FileImage file1("./test.txt",false);

	// check loading correctly. 
	if(!file1.IsAvailable())return ExitCode_Failure;

	// load a file another way. 
	// of course, need delete at your wish. 
	yges::FileImage* file2=yges::FileImage::Load("./test.txt",false);

	// check loading correctly. 
	// in failed, an instance not created. 
	if(!file2)return ExitCode_Failure;

	// check file size 
	size_t len=strlen(testext);
	if(len!=file1.GetFileSize())return ExitCode_Failure;
	if(len!=file2->GetFileSize())return ExitCode_Failure;
	// check read size 
	// (may short from file size) 
	if(len!=file1.GetReadSize())return ExitCode_Failure;
	if(len!=file2->GetReadSize())return ExitCode_Failure;

	// loaded data auto 0 terminated 
	if(*file1.GetEnd<char>())return ExitCode_Failure;
	if(*file2->GetEnd<char>())return ExitCode_Failure;

	// loaded data can use as a string directly. 
	if(strcmp(testext,file1.GetBegin<char>()))return ExitCode_Failure;
	if(strcmp(testext,file2->GetBegin<char>()))return ExitCode_Failure;

	// must unload 
	delete file2;

	// can unload immediately. 
	file1.Unload();
	if(file1.IsAvailable())return ExitCode_Failure;

	return 0;
}
