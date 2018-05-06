#include<stdio.h>
#include<gmp.h>
#include<stdlib.h>
#include "diffiehellman.c"

int main()
{
	char ** res=diffiehellman();
	printf("alice computes secret key %s\n",res[0]);
	printf("bob computes secret key %s\n",res[1]);
	return 0;
}
	
