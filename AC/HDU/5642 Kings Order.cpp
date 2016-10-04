#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2005,S=26,P=1e9+7;
int dp[N][S][4];
inline void mod_add(int &a,int b){
	if((a+=b)>=P)a-=P;
}
void solve(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<S;++i){
		dp[1][i][1]=1;
		dp[1][i][2]=dp[1][i][3]=0;
	}
	for(int i=2;i<=n;++i){
		for(int j=0;j<S;++j){
			dp[i][j][1]=0;
			for(int k=0;k<S;++k){
				if(k==j)continue;
				mod_add(dp[i][j][1],dp[i-1][k][1]);
				mod_add(dp[i][j][1],dp[i-1][k][2]);
				mod_add(dp[i][j][1],dp[i-1][k][3]);
			}
			dp[i][j][2]=dp[i-1][j][1];
			dp[i][j][3]=dp[i-1][j][2];
		}
	}
	int ans=0;
	for(int i=0;i<S;++i)
		for(int j=1;j<=3;++j)
			mod_add(ans,dp[n][i][j]);
	printf("%d\n",ans);
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		solve();
	}
	return 0;
}
/*
	
	Mar.13.16
	
	Tags:dp
	Submissions:1
	
	Exe.Time 62MS
	Exe.Memory 2224K
	Code Len. 1014B
	
*/
