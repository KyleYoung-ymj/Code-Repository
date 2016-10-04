#include<cstdio>
const int N=1e6+5;
typedef unsigned long long ull;
const ull B=1e9+7;
int n,m,num[N];
ull pat;
int solve(){
	if(n<m)return -1;
	ull hash=0,pow=1;
	for(int i=1;i<=m;++i){
		hash=hash*B+num[i];
		pow*=B;
	}
	for(int i=1;i+m<=n+1;++i){
		if(hash==pat)return i;
		if(i+m<=n)hash=hash*B+num[i+m]-num[i]*pow;
	}
	return -1;
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			scanf("%d",&num[i]);
		pat=0;
		for(int i=1;i<=m;++i){
			int tmp;
			scanf("%d",&tmp);
			pat=pat*B+tmp;
		}
		printf("%d\n",solve());
	}
	return 0;
}
/*
	
	Nov.27.15
	Submit:5
	
	Memory 5312KB
	Time 1357ms
	Code Length 594B
	
*/
