#include<cstdio>
const int N=2e3+5,mod=1e9+7;
int dp[2][N],pow_m[N];
void solve(){
	int n,m,ans=0;
	scanf("%d%d",&n,&m);
	bool pre=0,cur=1;
	dp[pre][0]=1;
	for(int i=1;i<n;++i)
		pow_m[i]=1ll*pow_m[i-1]*m%mod;
	for(int i=1;i<=n;++i,pre^=1,cur^=1){
		for(int j=0;j<=i;++j){
			dp[cur][j]=0;
			if(j)dp[cur][j]=1ll*dp[pre][j-1]*(m-j+1)%mod;
			if(j!=i)dp[cur][j]=(dp[cur][j]+1ll*dp[pre][j+1]*(j+1))%mod;
		}
		ans=(ans+1ll*(n+1-i)*dp[cur][i&1]%mod*pow_m[n-i])%mod;
	}
	printf("%d\n",ans);
}
int main(){
	int cas;
	scanf("%d",&cas);
	pow_m[0]=1;
	while(cas--)solve();
	return 0;
}
/*
	
	Jun.23.16
	
	Tags:dp
	Submissions:2
	
	Memory(KB) 1432KB
	Time(ms) 920ms
	Length(Bytes) 577B
	
*/
