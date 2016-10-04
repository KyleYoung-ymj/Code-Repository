#include<cstdio>
const int N=1e3+5;
double dp[N][N];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=n;~i;--i)
		for(int j=m;~j;--j){
			if(i==n&&j==m){
				dp[i][j]=0;
				continue;
			}
			dp[i][j]=1;
			dp[i][j]+=dp[i+1][j]*j*(n-i)/n/m;
			dp[i][j]+=dp[i][j+1]*i*(m-j)/n/m;
			dp[i][j]+=dp[i+1][j+1]*(n-i)*(m-j)/n/m;
			dp[i][j]/=1-1.0*i*j/n/m;
		}
	printf("%.4f\n",dp[0][0]);
	return 0;
}
/*
	
	May.09.16
	
	Tags:dp
	Submissions:3
	
	Memory 8068K
	Time 610MS
	Code Length 399B
	
*/
