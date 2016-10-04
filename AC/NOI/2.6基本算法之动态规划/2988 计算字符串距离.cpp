#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int LEN=1005;
int n,m,dp[LEN][LEN];
char A[LEN],B[LEN];
int main(){
	int cas;
	scanf("%d",&cas);
	for(int i=0;i<LEN;++i)
		dp[i][0]=dp[0][i]=i;
	while(cas--){
		scanf("%s%s",A+1,B+1);
		n=strlen(A+1);
		m=strlen(B+1);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(A[i]==B[j])dp[i][j]=dp[i-1][j-1];
				else dp[i][j]=min(min(dp[i-1][j],dp[i-1][j-1]),dp[i][j-1])+1;
		printf("%d\n",dp[n][m]);
	}
	return 0;
}
/*
	
	Dec.16.15
	
	Tags:dp,String
	Submissions:2
	dist("ab","a")=dist("a","ab")=1
	
	Memory 4212kB
	Time 20ms
	Code Length 517B
	
*/
