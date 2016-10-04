#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e4+5,M=5e3+5,INF=1e9+5;
int num[N],dp[M][N],s[M][N];
inline int calc(int x){
	return x*x;
}
int main(){
	int cas,kase=0;
	scanf("%d",&cas);
	while(cas--){
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			scanf("%d",&num[i]);
		sort(num+1,num+n+1);
		for(int i=1;i<=m;++i)
			for(int j=i;j<=n;++j)
				dp[i][j]=INF;
		for(int i=1;i<=n;++i){
			dp[1][i]=calc(num[i]-num[1]);
			s[1][i]=1;
		}
		for(int i=2;i<=m;++i){
			s[i][n+1]=n-1;
			for(int j=n;j>=i;--j)
				for(int k=s[i-1][j];k<=s[i][j+1];++k){
					int tmp=dp[i-1][k]+calc(num[j]-num[k+1]);
					if(tmp<=dp[i][j]){
						dp[i][j]=tmp;
						s[i][j]=k;
					}
				}
		}
		printf("Case %d: %d\n",++kase,dp[m][n]);
	}
	return 0;
}
/*
	
	Dec.26.15
	
	Tags:dp,mathematics
	Submissions:1
	
	Exe.Time 1934MS
	Exe.Memory 331120K
	Code Len. 806B
	
*/
