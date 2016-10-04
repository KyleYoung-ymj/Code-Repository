#include<cstdio>
#include<cstring>
const int M=35;
int dp[M][2];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int main(){
	int n,m,tree,ans=0;
	scanf("%d%d",&n,&m);
	memset(dp,-1,sizeof(dp));
	dp[0][0]=0;
	while(n--){
		scanf("%d",&tree);
		for(int i=m;~i;--i){
			if(~dp[i][0]){
				Max(dp[i+1][1],dp[i][0]+(tree==2));
				dp[i][0]+=tree==1;
			}
			if(~dp[i][1]){
				Max(dp[i+1][0],dp[i][1]+(tree==1));
				dp[i][1]+=tree==2;
			}
		}
	}
	for(int i=0;i<=m;++i){
		Max(ans,dp[i][0]);
		Max(ans,dp[i][1]);
	}
	printf("%d\n",ans);
	return 0;
}
/*
	
	Dec.15.15
	
	Tags:dp
	Submissions:1
	
	Memory 388K
	Time 32MS
	Code Length 544B
	
*/
