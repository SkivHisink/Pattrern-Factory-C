#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "factory.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	/*FILE* file_pointer;
	if ((file_pointer = fopen("source.txt", "r")) == NULL) {
		return -1;
	}*/
	//Factory(file_pointer);
	//Factory(stdin);
    /*void *p=NULL;
	*/
	return Factory(argv[1]);
}
