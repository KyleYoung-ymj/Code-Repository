#include<cstdio>
#include<algorithm>
using namespace std;
const int LEN=8,N=10;
int digit[LEN],dp[LEN][N]={0};
void pre_pro(){
	for(int i=0;i<N;++i)
		if(i==4)dp[1][i]=0;//WA
		else dp[1][i]=1;
	for(int i=1;i<LEN;++i)
		for(int j=0;j<N;++j){
			if(j==4)continue;
			for(int k=0;k<N;++k){
				if(k==4||k==2&&j==6)continue;
				dp[i][j]+=dp[i-1][k];
			}
		}
}
int solve(int n){
	int res=0,len=0;
	while(n){
		digit[len++]=n%10;
		n/=10;
	}
	reverse(digit,digit+len);
	for(int i=0;i<len;++i){
		for(int j=0;j<digit[i];++j){
			if(j==2&&i&&digit[i-1]==6)continue;
			res+=dp[len-i][j];
		}
		if(digit[i]==4||digit[i]==2&&i&&digit[i-1]==6)return res;
	}
	return res+1;//WA:if return didn't occur then n itself satisfies the require  
}
int main(){
	int n,m;
	pre_pro();
	while(~scanf("%d%d",&n,&m)&&n+m)
		printf("%d\n",solve(m)-solve(n-1));
	return 0;
}
/*
	
	Feb.16.16
	
	Tags:dp,classical
	Submissions:3
	
	Exe.Time 15MS
	Exe.Memory 1408K
	Code Len. 821B
	
*/
