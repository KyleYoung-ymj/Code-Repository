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
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
void rd(int &res){
    res=0;
    char c;
    while(c=getchar(),c<48);
    do res=(res<<3)+(res<<1)+(c^48);
        while(c=getchar(),c>47);
}
inline void Max(int &a,int b){
    if(b>a)a=b;
}
inline void Min(int &a,int b){
    if(b<a)a=b;
}
inline void mod_add(int &a,int b){
    if((a+=b)>=mod)a-=mod;
}
const int N=(int)1e5+5;
int tot_edge,head[N],par[N],ans[N];
bool vis[N];
pii edge[N<<1];
vector<pii>query[N];
inline void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
int get_root(int x){
	return par[x]==x?x:par[x]=get_root(par[x]);
}
void Tarjan(int cur){
	vis[par[cur]=cur]=true;
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(vis[son])continue;
		Tarjan(son);
		par[get_root(son)]=cur;
	}
	for(int i=0;i<query[cur].size();++i){
		if(!vis[query[cur][i].fi])continue;
		ans[query[cur][i].se]=get_root(query[cur][i].fi);
	}
}
int main(){
	int n,m;
	rd(n);rd(m);
	memset(head,-1,n+1<<2);
	for(int i=1,u,v;i<n;++i){
		rd(u);rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=0,u,v;i<m;++i){
		rd(u);rd(v);
		query[u].pb(pii(v,i));
		query[v].pb(pii(u,i));
	}
	Tarjan(1);
	for(int i=0;i<m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
