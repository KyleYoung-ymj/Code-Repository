#include<cstdio>
const int N=1e5,mod=998244353;
int dp[N+5],fact[N+5],inv[N+5];
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}
void init(){
	fact[0]=inv[0]=1;
	for(int i=1;i<=N;++i){
		fact[i]=1ll*fact[i-1]*i%mod;
		inv[i]=fast_mod_pow(fact[i],mod-2);
	}
	int sum1=0,sum2=0,sum3=0;
	for(int i=0;i<=N;++i){
		if(!i)dp[i]=1;
		else dp[i]=1ll*fact[i-1]*((1ll*i*i%mod*sum1%mod-2ll*i*sum2%mod+sum3)%mod+mod)%mod;
		sum1=(sum1+1ll*dp[i]*inv[i])%mod;
		sum2=(sum2+1ll*i*dp[i]%mod*inv[i])%mod;
		sum3=(sum3+1ll*i*i%mod*dp[i]%mod*inv[i])%mod;
	}
}
int main(){
	init();
	int n;
	while(~scanf("%d",&n))
		printf("%d\n",dp[n]);
	return 0;
}
/*
	
	Jun.18.16
	
	Tags:math
	Submissions:1
	
	Exe.Time 62MS
	Exe.Memory 2588K
	Code Len. 726B
	
*/
