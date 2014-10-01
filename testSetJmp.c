/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#include <setjmp.h>
#include <stdio.h>

void func1(jmp_buf* buf){
	static int called = 0;

	printf("Func1!\n");
	if (!called){
		++called;
		longjmp(*buf,5);
	}
}

void func2(void){
	printf("Func2!\n");
}

void main()
{
	jmp_buf buf;
	if (0 == setjmp(buf) ){
		func1(&buf);
	};

	func2();
	func1(&buf);
}
