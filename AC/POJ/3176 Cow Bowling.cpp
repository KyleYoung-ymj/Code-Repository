#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=355;
int n,num[N][N]={0},dp[N][N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=i;++j)
			scanf("%d",&num[i][j]);
	for(int i=n;i;--i)
		for(int j=1;j<=i;++j)
			dp[i][j]=num[i][j]+max(dp[i+1][j],dp[i+1][j+1]);
	printf("%d\n",dp[1][1]);
	return 0;
}
/*
	
	Dec.15.15
	
	Tags:dp
	Submissions:1
	
	Memory 1676K
	Time 32MS
	Code Length 361B
	
*/
