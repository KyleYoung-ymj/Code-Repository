#include<cstdio>
int main(){
	int n,m,a;
	scanf("%d %d %d",&n,&m,&a);
	printf("%I64d\n",1LL*((n+a-1)/a)*((m+a-1)/a));
	return 0;
}
/*
	
	Oct.25.15
	Submit:2
	
	Time 30ms
	Memory 0KB
	
*/
