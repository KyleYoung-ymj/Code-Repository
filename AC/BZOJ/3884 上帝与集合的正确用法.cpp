#include<cstdio>
int fast_mod_pow(int a,int b,int mod){
	int res=mod==1?0:1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}
int calc_phi(int n){
	int res=n;
	for(int i=2;i*i<=n;++i){
		if(!(n%i)){
			(res/=i)*=i-1;
			while(!(n%i))n/=i;
		}
	}
	if(n^1)(res/=n)*=n-1;
	return res;
}
int solve(int p){
	if(p==1)return 0;
	int cnt=0;
	while(~p&1){
		p>>=1;
		++cnt;
	}
	int phi=calc_phi(p),
		num=(phi+(solve(phi)-cnt)%phi)%phi;
	return fast_mod_pow(2,num,p)<<cnt;
}
int main(){
	int cas,p;
	scanf("%d",&cas);
	while(cas--){
		scanf("%d",&p);
		printf("%d\n",solve(p));
	}
	return 0;
}
/*
	
	Apr.26.16
	
	Tags:Number Theory,Euler Theorem
	Submissions:1
	
	Memory 804kb
	Time 44ms
	Code Length 725B
	
*/
