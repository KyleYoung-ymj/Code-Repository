#include<cstdio>
const int N=1005;
typedef unsigned long long ull;
const ull INF=1LL<<60;
int num[N]={0};
ull mul[N][N]={0},val[N][N]={0},dp[N][N],s[N][N];
int main(){
	int n,m;
	while(~scanf("%d%d",&n,&m)&&n){
		++m;
		for(int i=1;i<=n;++i)
			scanf("%d",&num[i]);
		for(int i=1;i<n;++i)
			for(int j=i+1;j<=n;++j)
				mul[i][j]=mul[i][j-1]+num[i]*num[j];
		for(int i=n-1;i;--i)
			for(int j=i+1;j<=n;++j)
				val[i][j]=val[i+1][j]+mul[i][j];
		for(int i=1;i<=m;++i)
			for(int j=i+1;j<=n;++j)
				dp[i][j]=INF;
		for(int i=1;i<=n;++i){
			dp[1][i]=val[1][i];
			s[i][1]=1;
		}
		for(int i=2;i<=m;++i){
			s[i][n+1]=n-1;
			for(int j=n;j>i;--j)
				for(int k=s[i-1][j];k<=s[i][j+1];++k)
					if(dp[i-1][k]+val[k+1][j]<=dp[i][j]){
						dp[i][j]=dp[i-1][k]+val[k+1][j];
						s[i][j]=k;
					}
		}
		printf("%llu\n",dp[m][n]);
	}
	return 0;
}
/*
	
	Dec.26.15
	
	Tags:dp
	Submissions:1
	
	Exe.Time 124MS
	Exe.Memory 25500K
	Code Len. 879B
	
*/
