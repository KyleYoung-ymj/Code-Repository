#include<cstdio>
#include<cstring>
const int N=1e4+5,LG=16,P=1e9+7;
int fact[N],inv[N],dp[LG][N];
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%P){
		if(b&1)res=1ll*res*a%P;
	}
	return res;
}
void init(){
	fact[0]=inv[0]=1;
	for(int i=1;i<N;++i){
		fact[i]=1ll*fact[i-1]*i%P;
		inv[i]=fast_mod_pow(fact[i],P-2);
	}
}
inline int C(int n,int m){
	return 1ll*fact[n]*inv[m]%P*inv[n-m]%P;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=P)a-=P;
}
int main(){
	int n,m,K;
	scanf("%d%d%d",&n,&m,&K);
	int tot=n-m;
	m>>=1;
	++K;
	init();
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(int i=0;i<LG-1;++i){
		int amt=1<<i;
		for(int j=0;j<=tot;++j){
			if(!dp[i][j])continue;
			for(int k=0;k<=m;k+=K){
				int nxt=j+k*amt;
				if(nxt>tot)break;
				mod_add(dp[i+1][nxt],1ll*dp[i][j]*C(m,k)%P);
			}
		}
	}
	int ans=0;
	for(int i=0;i<=tot;++i)
		mod_add(ans,1ll*dp[LG-1][i]*C(n-m-i,m)%P);
	if((ans=C(n,m<<1)-ans)<0)ans+=P;
	printf("%d\n",ans);
	return 0;
}
/*
	
	May.24.16
	
	Tags:Game Theory,Mathematics,dp
	Submissions:2
	
	Memory 1508kb
	Time 144ms
	Code Length 1122B
	
*/
