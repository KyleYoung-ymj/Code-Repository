#include<cstdio>
const int N=505,M=35,INF=1e9+5;
int val[N],cost[N][N],dp[N][M],s[N][M];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&val[i]);
	for(int i=1;i<=n;++i){
		cost[i][i]=0;
		for(int j=i+1;j<=n;++j)
			cost[i][j]=cost[i][j-1]+val[j]-val[i+j>>1];
	}
	for(int i=1;i<=m;++i)
		for(int j=i;j<=n;++j)
			dp[i][j]=INF;
	for(int i=1;i<=n;++i){
		dp[1][i]=cost[1][i];
		s[1][i]=1;
	}
	for(int i=2;i<=m;++i){
		s[i][n+1]=n-1;
		for(int j=n;j>=i;--j)
			for(int k=s[i-1][j];k<=s[i][j+1];++k)
				if(dp[i-1][k]+cost[k+1][j]<=dp[i][j]){
					dp[i][j]=dp[i-1][k]+cost[k+1][j];
					s[i][j]=k;
				}
	}
	printf("%d\n",dp[m][n]);
	return 0;
}
/*
	
	Dec.26.15
	
	Tags:dp
	Submissions:3
	
	Memory 1004K
	Time 32MS
	Code Length 673B
	
*/
