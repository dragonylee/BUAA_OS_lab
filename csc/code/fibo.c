#include <fibo.h>

int fibo(int n)
{
	int a=1,b=1,c,i;
	if(n==1) return 1;
	for(i=2;i<=n;i++)
	{
		c=a+b;
		a=b,b=c;
	}	
	return a;
}

