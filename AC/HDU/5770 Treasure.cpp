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
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
typedef complex<double> Com;
const int mod=(int)1e9+7,inf=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const ll INF=1ll<<60;
const double pi=acos(-1.0),eps=1e-8;
template<class T>void rd(T &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_print(T x){
	if(!x)return;
	rec_print(x/10);
	putchar(x%10^48);
}
template<class T>void print(T x){
	if(!x)putchar('0');
	else rec_print(x);
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
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}
const int N=(int)1e5+5,LG=18;
int n,tot_edge,head[N],dfs_clock,pre[N],post[N],dep[N],par[LG][N];
pii edge[N<<1];
void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
void dfs(int cur,int fa){
	par[0][cur]=fa;
	for(int i=1;i<LG;++i)
		par[i][cur]=par[i-1][par[i-1][cur]];
	pre[cur]=++dfs_clock;
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==fa)continue;
		dep[son]=dep[cur]+1;
		dfs(son,cur);
	}
	post[cur]=dfs_clock;
}
int up(int x,int step){
	for(int i=0;i<LG;++i)
		if(step>>i&1)
			x=par[i][x];
	return x;
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	u=up(u,dep[u]-dep[v]);
	if(u==v)return u;
	for(int i=LG-1;~i;--i)
		if(par[i][u]!=par[i][v]){
			u=par[i][u];
			v=par[i][v];
		}
	return par[0][u];
}
int tot_add;
struct Add{
	int pos,L,R,val;
	Add(){}
	Add(int pos,int L,int R,int val):pos(pos),L(L),R(R),val(val){}
	inline bool operator <(const Add &tmp)const{
		return pos<tmp.pos;
	}
}add[N<<3];
void add_rect(int x1,int x2,int y1,int y2,int val){
	// printf("#%d %d %d %d\n",x1,x2,y1,y2,val);//
	add[tot_add++]=Add(x1,y1,y2,val);
	if(x2<n)add[tot_add++]=Add(x2+1,y1,y2,-val);
}
struct Segment_Tree{
	#define lson (k<<1)
	#define rson (k<<1|1)
	struct Node{
		int mx,extra;
		void operator +=(int val){
			mx+=val;
			extra+=val;
		}
	}tree[N<<2];
	inline void push_up(int k){
		tree[k].mx=max(tree[lson].mx,tree[rson].mx);
	}
	void push_down(int k){
		int &val=tree[k].extra;
		if(!val)return;
		tree[lson]+=val;
		tree[rson]+=val;
		val=0;
	}
	void construct(int l,int r,int k=1){
		tree[k].mx=tree[k].extra=0;
		if(l==r)return;
		int mid=l+r>>1;
		construct(l,mid,lson);
		construct(mid+1,r,rson);
	}
	void update(int l,int r,int L,int R,int val,int k=1){
		if(l==L&&r==R){
			tree[k]+=val;
			return;
		}
		push_down(k);
		int mid=l+r>>1;
		if(R<=mid)update(l,mid,L,R,val,lson);
		else if(L>mid)update(mid+1,r,L,R,val,rson);
		else{
			update(l,mid,L,mid,val,lson);
			update(mid+1,r,mid+1,R,val,rson);
		}
		push_up(k);
	}
	inline int query_mx(){
		return tree[1].mx;
	}
}T;
void solve(){
	int m;
	rd(n);rd(m);
	tot_edge=0;
	memset(head,-1,n+1<<2);
	for(int i=1,u,v;i<n;++i){
		rd(u);rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs_clock=0;
	dfs(1,0);
	// for(int i=1;i<=n;++i){
	// 	debug(i);//
	// 	debug(pre[i]);debug(post[i]);//
	// }
	tot_add=0;
	for(int u,v,w;m--;){
		rd(u);rd(v);
		scanf("%d",&w);
		if(u==v){
			add_rect(1,n,1,n,w);
			for(int i=head[u];~i;i=edge[i].se){
				int son=edge[i].fi;
				if(dep[son]<dep[u])continue;
				add_rect(pre[son],post[son],pre[son],post[son],-w);
			}
			if(pre[u]>1)add_rect(1,pre[u]-1,1,pre[u]-1,-w);
			if(post[u]<n)add_rect(post[u]+1,n,post[u]+1,n,-w);
			if(pre[u]>1&&post[u]<n){
				add_rect(1,pre[u]-1,post[u]+1,n,-w);
				add_rect(post[u]+1,n,1,pre[u]-1,-w);
			}
			continue;
		}
		int anc=lca(u,v);
		if(anc!=u&&anc!=v)add_rect(pre[u],post[u],pre[v],post[v],w);
		else if(anc==u){
			int son=up(v,dep[v]-dep[u]-1);
			if(pre[son]>1)add_rect(1,pre[son]-1,pre[v],post[v],w);
			if(post[son]<n)add_rect(post[son]+1,n,pre[v],post[v],w);
		}
		else if(anc==v){
			int son=up(u,dep[u]-dep[v]-1);
			if(pre[son]>1)add_rect(pre[u],post[u],1,pre[son]-1,w);
			if(post[son]<n)add_rect(pre[u],post[u],post[son]+1,n,w);
		}
	}
	int ans=-inf;
	T.construct(1,n);
	sort(add,add+tot_add);
	for(int i=1,j=0;i<=n;++i){
		for(;j<tot_add&&add[j].pos==i;++j)T.update(1,n,add[j].L,add[j].R,add[j].val);
		Max(ans,T.query_mx());
	}
	printf("%d\n",ans);
}
int main(){
	int cas;
	rd(cas);
	for(int kase=1;kase<=cas;++kase){
		printf("Case #%d: ",kase);
		solve();
	}
	return 0;
}
/*
	
	Jul.29.16

	Tags:tree,segment tree
	Submissions:1

	Exe.Time 1591MS
	Exe.Memory 19400K
	Code Len. 5216B
	
*/
