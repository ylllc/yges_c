#include "memory/safe_alloc.h"
#include <stdio.h>
#include <string.h>

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
int main(int argc,char** argv){

	int exitcode=0;

	// alloc 
	size_t size=1000000000;
	int i,a=0;

	char* p=yges_safe_alloc(size);
	if(!p){
		fprintf(stderr,"cant alloc %lu bytes\n",size);
		return 1;
	}

	// already zero cleared 
	for(i=a=0;i<size;++i)a|=p[i];
	if(a){
		fprintf(stderr,"not zero cleared\n");
		exitcode=1;
	}

	// free 
	// pointer is NULL after freed 
	yges_safe_free(&p);
	if(p){
		fprintf(stderr,"not freed\n");
		exitcode=1;
	}

	return exitcode;
}
