#include<cstdio>
const int N=2e3+5,mod=258280327;
int pow_p[N],dp[N][N];
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}
int inv(int x){
	return fast_mod_pow(x,mod-2);
}
void solve(){
	int n,x,y;
	scanf("%d%d%d",&n,&x,&y);
	x=y-x;
	int p=1ll*x*inv(y)%mod;
	pow_p[0]=1;
	for(int i=1;i<=n;++i)
		pow_p[i]=1ll*pow_p[i-1]*p%mod;
	dp[1][0]=1;
	for(int i=2;i<=n;++i){
		for(int j=0;j<i;++j){
			dp[i][j]=1ll*dp[i-1][j-1]*pow_p[j-1]%mod;
			if(j<i-1)dp[i][j]=((dp[i][j]+1ll*dp[i-1][j]*(1-pow_p[j]))%mod+mod)%mod;
		}
	}
	for(int k=0,inv_n=inv(n);k<n;++k){
		int ans=0;
		for(int i=1;i<=n;++i)
			ans=(ans+1ll*dp[i][k]*pow_p[k])%mod;
		printf("%d%c",(int)(1ll*ans*inv_n%mod)," \n"[k==n-1]);
	}
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--)solve();
	return 0;
}
/*
	
	Jun.21.16
	
	Tags:dp of probability
	Submissions:1
	
	Memory(KB) 17124KB
	Time(ms) 546ms
	Length(Bytes) 830B
	
*/
