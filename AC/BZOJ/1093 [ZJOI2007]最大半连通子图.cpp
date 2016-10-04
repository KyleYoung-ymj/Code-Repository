#include <cstdio>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb push_back
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
template<class T>void rd(T &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
template<class T>inline void Max(T &a,T b){
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b){
	if(b<a)a=b;
}
const int N=(int)1e5+5,M=(int)1e6+5;
int n,mod,
	tot_edge,head[N],
	dfs_clock,pre[N],tot_scc,scc_id[N],top,stk[N];
bool vis[N];
pii edge[M],dp[N];
veci node[N];
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
inline void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
int Tarjan(int cur){
	int lowlink=pre[cur]=++dfs_clock;
	stk[top++]=cur;
	for(int i=head[cur];~i;i=edge[i].se){
		int to=edge[i].fi;
		if(!pre[to])Min(lowlink,Tarjan(to));
		else if(!scc_id[to])Min(lowlink,pre[to]);
	}
	if(lowlink==pre[cur]){
		++tot_scc;
		for(;;){
			int elm=stk[--top];
			node[tot_scc].pb(elm);
			scc_id[elm]=tot_scc;
			if(elm==cur)break;
		}
	}
	return lowlink;
}
void scc(){
	for(int i=1;i<=n;++i)
		if(!pre[i])Tarjan(i);
}
pii DP(int cur){
	if(vis[cur])return dp[cur];
	vis[cur]=true;
	dp[cur].se=1%mod;
	veci vec;
	for(int i=0;i<(int)node[cur].size();++i){
		int u=node[cur][i];
		for(int j=head[u];~j;j=edge[j].se){
			int v=edge[j].fi;
			if(scc_id[v]==cur)continue;
			vec.pb(scc_id[v]);
		}
	}
	sort(vec.begin(),vec.end());
	vec.resize(unique(vec.begin(),vec.end())-vec.begin());
	for(int i=0;i<(int)vec.size();++i){
		int to=vec[i];
		pii P=DP(to);
		if(P.fi>dp[cur].fi)dp[cur]=P;
		else if(P.fi==dp[cur].fi)mod_add(dp[cur].se,P.se);	
	}
	dp[cur].fi+=(int)node[cur].size();
	return dp[cur];
}
int main(){
	int m;
	rd(n);rd(m);rd(mod);
	memset(head,-1,n+1<<2);
	for(int u,v;m--;){
		rd(u);rd(v);
		add_edge(u,v);
	}
	scc();
	pii ans=pii(0,0);
	for(int i=1;i<=n;++i){
		pii P=DP(i);
		if(P.fi>ans.fi)ans=P;
		else if(P.fi==ans.fi)mod_add(ans.se,P.se);
	}
	printf("%d\n%d\n",ans.fi,ans.se);
	return 0;
}
/*
	
	Jul.18.16

	Tags:scc,dp
	Submissions:3

	Memory 19336kb
	Time 1628ms
	Code Length 2930B

*/
