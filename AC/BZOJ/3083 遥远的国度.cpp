#include <cstdio>
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
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<ll,ll> pll;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double eps=1e-8;
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
const int N=(int)1e5+5,LG=18;
int n,tot_edge,head[N],val[N],
	dfs_clock,pre[N],post[N],id[N],
	dep[N],par[N][LG],sz[N],heavy_son[N],top[N],
	root;
pii edge[N<<1];
struct Segment_Tree{
	#define lson (k<<1)
	#define rson (k<<1|1)
	struct Node{
		int L,R,mi,same;
		Node(){}
		Node(int L,int R,int mi,int same):L(L),R(R),mi(mi),same(same){}
	}tree[N<<2];
	inline void push_up(int k){
		tree[k].mi=min(tree[lson].mi,tree[rson].mi);
	}
	void push_down(int k){
		if(tree[k].same==-1)return;
		tree[lson].mi=tree[rson].mi=tree[lson].same=tree[rson].same=tree[k].same;
		tree[k].same=-1;
	}
	void build(int L=1,int R=n,int k=1){
		tree[k]=Node(L,R,0,-1);
		if(L==R){
			tree[k].mi=val[id[L]];
			return;
		}
		int mid=L+R>>1;
		build(L,mid,lson);
		build(mid+1,R,rson);
		push_up(k);
	}
	void modify(int L,int R,int v,int k=1){
		if(tree[k].L==L&&tree[k].R==R){
			tree[k].mi=tree[k].same=v;
			return;
		}
		int mid=tree[k].L+tree[k].R>>1;
		push_down(k);
		if(R<=mid)modify(L,R,v,lson);
		else if(L>mid)modify(L,R,v,rson);
		else{
			modify(L,mid,v,lson);
			modify(mid+1,R,v,rson);
		}
		push_up(k);
	}
	int query(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R)
			return tree[k].mi;
		int mid=tree[k].L+tree[k].R>>1;
		push_down(k);
		if(R<=mid)return query(L,R,lson);
		if(L>mid)return query(L,R,rson);
		return min(query(L,mid,lson),query(mid+1,R,rson));
	}
}T;
inline void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
void dfs(int cur,int fa=0,int depth=0){
	par[cur][0]=fa;
	for(int i=1;i<LG;++i)
		par[cur][i]=par[par[cur][i-1]][i-1];
	dep[cur]=depth++;
	sz[cur]=1;
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==fa)continue;
		dfs(son,cur,depth);
		sz[cur]+=sz[son];
		if(!heavy_son[cur]||sz[son]>sz[heavy_son[cur]])
			heavy_son[cur]=son;
	}
}
void allc_dfs(int cur,int anc){
	id[pre[cur]=++dfs_clock]=cur;
	top[cur]=anc;
	if(heavy_son[cur])allc_dfs(heavy_son[cur],anc);
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==par[cur][0]||son==heavy_son[cur])continue;
		allc_dfs(son,son);
	}
	post[cur]=dfs_clock;
}
void modify(int u,int v,int tar){
	for(;top[u]!=top[v];u=par[top[u]][0]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		T.modify(pre[top[u]],pre[u],tar);
	}
	if(dep[u]>dep[v])swap(u,v);
	T.modify(pre[u],pre[v],tar);
}
int up(int x,int step){
	for(int i=0;i<LG;++i)
		if(step&1<<i)
			x=par[x][i];
	return x;
}
int query(int tar){
	if(!(pre[root]>=pre[tar]&&pre[root]<=post[tar]))
		return T.query(pre[tar],post[tar]);
	if(root==tar)return T.query(1,n);
	int son=up(root,dep[root]-dep[tar]-1),
		mi=INF;
	if(pre[son]>1)Min(mi,T.query(1,pre[son]-1));
	if(post[son]<n)Min(mi,T.query(post[son]+1,n));
	return mi;
}
int main(){
	int m;
	rd(n);rd(m);
	memset(head,-1,n+1<<2);
	for(int i=1,u,v;i<n;++i){
		rd(u);rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;++i)
		rd(val[i]);
	rd(root);
	dfs(1);
	allc_dfs(1,1);
	T.build();
	for(int ope,u,v,tar;m--;){
		rd(ope);
		if(ope==1)rd(root);
		else if(ope==2){
			rd(u);rd(v);rd(tar);
			modify(u,v,tar);
		}
		else{
			rd(tar);
			printf("%d\n",query(tar));
		}
	}
	return 0;
}
/*
	
	Jul.14.16

	Tags:HLD,dfs clock
	Submissions:3

	Memory 25836kb
	Time 3776ms
	Code Length 4613B

*/
