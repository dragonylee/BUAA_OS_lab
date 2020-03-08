#include<stdio.h>

int isP(int x)
{
	char s[10];
	int tot=0,i,j;
	while(x)
	{
		s[tot++]=x%10;
		x/=10;	
	}
	for(i=0,j=tot-1;i<j;i++,j--)
		if(s[i]!=s[j]) return 0;
	return 1;
}

int main()
{
	int n;
	scanf("%d",&n);
	if(isP(n)){
		printf("Y");
	}else{
		printf("N");
	}
	return 0;
}
