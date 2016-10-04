#include<cstdio>
#include<cstring>
const int LEN=25;
int n,m;
bool dp[LEN][LEN]={false};
char A[LEN],B[LEN];
int main(){
	scanf("%s%s",A+1,B+1);
	n=strlen(A+1);
	m=strlen(B+1);
	dp[0][0]=true;
	for(int i=1;A[i]=='*';++i)
		dp[i][0]=true;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(A[i]=='*')dp[i][j]=dp[i-1][j]||dp[i][j-1]||dp[i-1][j-1];
			else if(A[i]=='?')dp[i][j]=dp[i-1][j-1];
			else dp[i][j]=A[i]==B[j]&&dp[i-1][j-1];
	puts(dp[n][m]?"matched":"not matched");
	return 0;
}
/*
	
	Dec.16.15
	
	Tags:String,dp
	Submissions:2
	Bug Data:
		*??
		21
		ans:matched
		
		**?
		2
		ans:matched
	
	
	Memory 256kB
	Time 0ms
	Code Length 488B
	
*/
