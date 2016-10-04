#include<cstdio>
const int N=15,S_MAX=1<<15,P=1e8;
int n,m,S,dp[2][S_MAX]={0};
bool cur=0,nxt=1,flag[N];
inline void mod_plus(int &a,int b){
	a=(a+b)%P;
}
void init_dfs(int c,int sum){
	if(c==m){
		dp[cur][sum]=1;
		return;
	}
	init_dfs(c+1,sum);
	if(flag[c]&&!(sum&1<<c-1))init_dfs(c+1,sum|1<<c);
}
void DP(int c,int sum){
	if(c==m){
		mod_plus(dp[nxt][sum],dp[cur][S]);
		return;
	}
	DP(c+1,sum);
	if(flag[c]&&!(S&1<<c)&&!(sum&1<<c-1))DP(c+1,sum|1<<c);
}
int main(){
	scanf("%d%d",&n,&m);
	int S_max=1<<m,ans=0;
	for(int i=0;i<m;++i)
		scanf("%d",&flag[i]);
	init_dfs(0,0);
	for(int i=1;i<n;++i){
		for(int j=0;j<S_max;++j)
			dp[nxt][j]=0;
		for(int j=0;j<m;++j)
			scanf("%d",&flag[j]);
		for(S=0;S<S_max;++S){
			if(!dp[cur][S])continue;
			DP(0,0);
		}
		cur^=1;
		nxt^=1;
	}
	for(int j=0;j<S_max;++j)
		if(dp[cur][j])mod_plus(ans,dp[cur][j]);
	printf("%d\n",ans);
	return 0;
}
/*
	
	Dec.16.15
	
	Tags:dp
	Submissions:3
	WA:the size of Array is TOO small!!
	
	Memory 
	Time 
	Code Length 
	
*/
