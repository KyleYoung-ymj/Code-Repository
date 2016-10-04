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
const int N=(int)3e5+5;
int tot,head_edge[N],head_query[N],arr[N],fa[N],par[N],ans[N];
bool vis[N];
pii dat[N<<2];
inline void add_edge(int u,int v){
	dat[tot]=pii(v,head_edge[u]);
	head_edge[u]=tot++;
}
inline void add_query(int u,int v){
	dat[tot]=pii(v,head_query[u]);
	head_query[u]=tot++;
}
int get_root(int x){
	return par[x]==x?x:par[x]=get_root(par[x]);
}
void Tarjan(int cur){
	par[cur]=cur;
	for(int i=head_edge[cur];~i;i=dat[i].se){
		int son=dat[i].fi;
		if(son==fa[cur])continue;
		fa[son]=cur;
		Tarjan(son);
		par[get_root(son)]=cur;
	}
	vis[cur]=true;
	for(int i=head_query[cur];~i;i=dat[i].se){
		int to=dat[i].fi;
		if(!vis[to])continue;
		int lca=get_root(to);
		--ans[lca];
		--ans[fa[lca]];
	}
	ans[fa[cur]]+=ans[cur];
}
int main(){
	int n;
	rd(n);
	memset(head_query,-1,n+1<<2);
	for(int i=1;i<=n;++i){
		rd(arr[i]);
		if(i>1){
			add_query(arr[i-1],arr[i]);
			add_query(arr[i],arr[i-1]);
			++ans[arr[i-1]];
			++ans[arr[i]];
		}
	}
	memset(head_edge,-1,n+1<<2);
	for(int i=1,u,v;i<n;++i){
		rd(u);rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	Tarjan(1);
	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]-(i!=arr[1]));
	return 0;
}
/*
	
	Jul.15.16

	Tags:lca
	Submissions:1

	Memory 25432kb
	Time 1036ms
	Code Length 2414B

*/
