#include<cstdio>
const int S_MAX=1<<11;
typedef unsigned long long ull;
int m,S;
ull dp[2][S_MAX];
bool cur=0,nxt=1;
void pre_dfs(int c,int sum){
	if(c==m){
		dp[cur][sum]=1;
		return;
	}
	pre_dfs(c+1,sum);
	if(c<m-1)pre_dfs(c+2,sum|3<<c);
}
void transition(int c,int sum){
	if(c==m){
		dp[nxt][sum]+=dp[cur][S];
		return;
	}
	if(!(S&1<<c))transition(c+1,sum|1<<c);
	else{
		transition(c+1,sum);
		if(c<m-1&&S&1<<c+1)transition(c+2,sum|3<<c);//Pay attention if the next block must be covered vertically
	}
}
int main(){
	int n;
	while(~scanf("%d%d",&n,&m)&&n&&m){
		if(n*m&1){
			puts("0");
			continue;
		}
		int S_max=1<<m;
		for(S=0;S<S_max;++S)
			dp[cur][S]=0;
		pre_dfs(0,0);
		for(int i=1;i<n;++i){
			for(S=0;S<S_max;++S)
				dp[nxt][S]=0;
			for(S=0;S<S_max;++S)
				if(dp[cur][S])
					transition(0,0);
			cur^=1;
			nxt^=1;
		}
		printf("%llu\n",dp[cur][S_max-1]);
	}
	return 0;
}
/*
	
	Dec.17.15
	
	Tags:dp
	Submissions:2
	WA:Using "%I64u"
	
	Memory 256kB
	Time 0ms
	Code Length 831B
	
*/
