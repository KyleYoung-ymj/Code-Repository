#include<cstdio>
const int S_MAX=1<<20;
int dp[2][S_MAX]={0};
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int S_max=1<<m,k,tmp,ans=0;
	bool cur=0,nxt=1;
	dp[cur][0]=1;
	while(n--){
		scanf("%d",&k);
		while(k--){
			scanf("%d",&tmp);
			--tmp;
			for(int S=0;S<S_max;++S)
				if(dp[cur][S]&&!(S&1<<tmp))
					dp[nxt][S|1<<tmp]+=dp[cur][S];
		}
		for(int i=0;i<S_max;++i)
			dp[cur][i]=0;
		cur^=1;
		nxt^=1;
	}
	for(int i=0;i<S_max;++i)
		ans+=dp[cur][i];
	printf("%d\n",ans);
	return 0;
} 
/*
	
	Dec.12.15
	
	Tags:dp
	Submissions:1
	
	Memory 8604K
	Time 1172MS
	Code Length 491B
	
*/
