#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e4+5;
const double eps=1e-9;
int tot_edge,head[N],deg[N];
double K[N],E[N];
struct P{
	double k1,k2,c;
	// dp[i]=k1*dp[1]+k2*dp[par[i]]+c
}dp[N];
struct Edge{
	int to,nxt;
}edge[N<<1];
void add_edge(int from,int to){
	edge[tot_edge]=(Edge){to,head[from]};
	head[from]=tot_edge++;
}
void DP(int u,int par){
	double p=(1-K[u]-E[u])/deg[u],k=0;
	dp[u].k1=K[u];
	dp[u].k2=p;
	dp[u].c=1-K[u]-E[u];
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==par)continue;
		DP(v,u);
		dp[u].k1+=p*dp[v].k1;
		k+=p*dp[v].k2;
		dp[u].c+=p*dp[v].c;
	}
	// dp[u]=k*dp[u]+k1*dp[1]+k2*dp[par[u]]+c
	k=1-k;
	dp[u].k1/=k;
	dp[u].k2/=k;
	dp[u].c/=k;
}
void solve(){
	int n;
	scanf("%d",&n);
	tot_edge=0;
	memset(head,-1,n+1<<2);
	memset(deg,0,n+1<<2);
	for(int i=1,u,v;i<n;++i){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
		++deg[u];
		++deg[v];
	}
	for(int i=1;i<=n;++i){
		scanf("%lf%lf",&K[i],&E[i]);
		K[i]/=100;
		E[i]/=100;
	}
	DP(1,-1);
	if(fabs(dp[1].k1-1)<eps)puts("impossible");
	else printf("%.6f\n",dp[1].c/(1-dp[1].k1));
}
int main(){
	int cas,kase=0;
	scanf("%d",&cas);
	while(cas--){
		printf("Case %d: ",++kase);
		solve();
	}
	return 0;
}
/*
	
	May.10.16
	
	Tags:dp,Mathematics
	Submissions:1
	
	Exe.Time 327MS
	Exe.Memory 3104K
	Code Len. 1335B
	
*/
