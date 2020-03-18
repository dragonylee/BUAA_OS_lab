#include <asm/asm.h>
#include <pmap.h>
#include <env.h>
#include <printf.h>
#include <kclock.h>
#include <trap.h>


void mips_init()
{
	printf("init.c:\tmips_init() is called\n");


	//for your degree,don't delete these.
	//------------|
	#ifdef FTEST
	FTEST();
	#endif

	#ifdef PTEST
	ENV_CREATE(PTEST);
	#endif
	//-----------|

	printf("\n___test___\n\n");

    printf("hello,%d\n", 123);
    printf("hello,%d\n", -123);
    printf("%-10ld\n",-2);
    printf("%010X\n",15);
    printf("%b\n",127);
    printf("%u\n",-1);

	panic("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
}
