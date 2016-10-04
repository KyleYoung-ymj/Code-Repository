#include<cstdio>
int n;
int fast_mod_pow(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=1LL*res*a%n;
		a=1LL*a*a%n;
		b>>=1;
	}
	return res;
}
int main(){
//	freopen("circle.in","r",stdin);
//	freopen("circle.out","w",stdout);
	int m,k,x;
	scanf("%d %d %d %d",&n,&m,&k,&x);
	int tmp=1LL*fast_mod_pow(10,k)*m%n;
	printf("%d\n",(x+tmp)%n);
	return 0;
}
/*
	
	Oct.30.15
	Score:100
	
	Memory 692K
	Time 16MS
	Code Length 0.36K
	
*/
