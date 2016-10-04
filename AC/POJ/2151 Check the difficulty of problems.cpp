#include<cstdio>
const int N=35;
double dp[N][N];
int main(){
	int n,m,K;
	while(~scanf("%d%d%d",&n,&m,&K),n+m+K){
		double ans1=0,ans2=1;
		for(int i=0;i<m;++i){
			double mul=1,p;
			for(int j=1;j<=n;++j){
				scanf("%lf",&p);
				dp[j-1][0]=mul;
				for(int k=1;k<=j;++k){
					dp[j][k]=dp[j-1][k-1]*p;
					if(k<j)dp[j][k]+=dp[j-1][k]*(1-p);
				}
				mul*=1-p;
			}
			double sum0=0,sum1=0;
			for(int j=1;j<K;++j)
				sum0+=dp[n][j];
			for(int j=K;j<=n;++j)
				sum1+=dp[n][j];
			ans1=ans1*(sum0+sum1)+ans2*sum1;
			ans2*=sum0;
		}
		printf("%.3f\n",ans1);
	}
	return 0;
}
/*
	
	May.10.16
	
	Tags:dp,probability
	Submissions:5
	
	Memory 192K
	Time 47MS
	Code Length 580B
	
*/
