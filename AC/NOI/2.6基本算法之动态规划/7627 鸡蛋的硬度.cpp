#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=15,M=105,INF=1005;
int dp[N][M];
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int solve(int n,int m){
	if(~dp[n][m])return dp[n][m];
	int &res=dp[n][m];
	if(!m)res=0;
	else if(n==1)res=m;
	else{
		res=INF;
		for(int k=1;k<=m;++k)
			Min(res,max(solve(n-1,k-1),solve(n,m-k))+1);
	}
	return res;
}
int main(){
	int n,m;
	memset(dp,-1,sizeof(dp));
	while(~scanf("%d%d",&m,&n))
		printf("%d\n",solve(n,m));
	return 0;
}
/*
	
	Dec.25.15
	
	Tags:dp,classic
	Submissions:1
	
	Memory 260kB
	Time 0ms
	Code Length 504B
	
*/
