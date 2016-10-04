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
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
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
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
const int N=(int)2e3+5;
int n,tot_edge,head[N],
	dfs_clock,pre[N],tot_scc,scc_id[N],top,stk[N];
char str[N];
bool vis[N];
pii edge[N*N];
veci node[N];
bitset<N>bs[N];
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
			scc_id[elm]=tot_scc;
			node[tot_scc].pb(elm);
			if(elm==cur)break;
		}
	}
	return lowlink;
}
void scc(){
	for(int i=0;i<n;++i)
		if(!pre[i])Tarjan(i);
}
int DP(int cur){
	if(vis[cur])return bs[cur].count();
	vis[cur]=1;
	for(int i=0;i<(int)node[cur].size();++i){
		int u=node[cur][i];
		bs[cur][u]=1;
		for(int j=head[u];~j;j=edge[j].se){
			int v=edge[j].fi;
			if(scc_id[u]==scc_id[v])continue;
			bs[cur]|=bs[scc_id[v]];
		}
	}
	return bs[cur].count();;
}
int main(){
	rd(n);
	for(int i=0;i<n;++i){
		head[i]=-1;
		scanf("%s",str);
		for(int j=0;j<n;++j){
			if(str[j]=='1')add_edge(i,j);
		}
	}
	scc();
	int ans=0;
	for(int i=1;i<=tot_scc;++i)
		ans+=(int)node[i].size()*DP(i);
	printf("%d\n",ans);
	return 0;
}
/*
	
	Jul.18.16

	Tags:scc,dp,bitset
	Submissions:1

	Memory 33252kb
	Time 968ms
	Code Length 2599B

*/
