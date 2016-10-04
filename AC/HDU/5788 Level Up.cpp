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
#define lson (k<<1)
#define rson (k<<1|1)
#define Debug(x) cout<<endl<<#x<<"="<<x<<"!!!!!"<<endl<<endl
#define rep(i,s,t) for(int i=s,_t=t;i<t;++i)
#define per(i,s,t) for(int i=t-1,_s=s;i>=_s;--i)
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

const int N=(int)1e5+5,MX=(int)1e5;
int n,tot_edge,head[N],v[N],
	val[N],mid[N],mid1[N],tot,num[N],sz[N],
	dfs_clock,dfn[N],post[N],id[N],
	Tid[N];
pii edge[N<<1];
struct Chairman_Tree{
	static const int LG_N=19,M=(N<<2)+(N*LG_N);
	int allc,Lson[M],Rson[M],sum[M];
	inline void init(){
		allc=0;
	}
	void build(int &cur,int L,int R){
		sum[cur=++allc]=0;
		if(L==R)return;
		int mid=L+R>>1;
		build(Lson[cur],L,mid);
		build(Rson[cur],mid+1,R);
	}
	void construct(int oid,int &cur,int L,int R,int tar){
		cur=++allc;
		Lson[cur]=Lson[oid];
		Rson[cur]=Rson[oid];
		sum[cur]=sum[oid]+1;
		if(L==R)return;
		int mid=L+R>>1;
		if(tar<=mid)construct(Lson[oid],Lson[cur],L,mid,tar);
		else construct(Rson[oid],Rson[cur],mid+1,R,tar);
	}
	int query(int Lt,int Rt,int L,int R,int K){
		if(L==R)return L;
		int cnt=sum[Rson[Rt]]-sum[Rson[Lt]],
			mid=L+R>>1;
		if(K<=cnt)return query(Rson[Lt],Rson[Rt],mid+1,R,K);
		return query(Lson[Lt],Lson[Rt],L,mid,K-cnt);
	}
}T;
inline void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
void dfs(int cur,int par=0){
	id[dfn[cur]=++dfs_clock]=cur;
	sz[cur]=1;
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==par)continue;
		dfs(son,cur);
		sz[cur]+=sz[son];
	}
	post[cur]=dfs_clock;
}
ll ans,bit[N];
void add(int x,int va){
	for(;x;x-=lowbit(x))
		bit[x]+=va;
}
ll query(int x){
	ll res=0;
	for(;x<=MX;x+=lowbit(x))
		res+=bit[x];
	return res;
}
void solve_dfs(int cur){
	add(mid[cur],v[cur]);
	Max(ans,query(val[cur]));
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		solve_dfs(son);
	}
	add(mid[cur],-v[cur]);
}
void solve(){
	tot_edge=0;
	memset(head,-1,n+1<<2);
	rep(i,1,n+1)rd(val[i]);
	for(int i=2,fa;i<=n;++i){
		rd(fa);
		add_edge(fa,i);
	}
	dfs_clock=0;
	dfs(1);
	T.init();
	T.build(Tid[0],1,MX);
	rep(i,1,n+1)T.construct(Tid[i-1],Tid[i],1,MX,val[id[i]]);
	rep(i,1,n+1){
		if(sz[i]==1){
			mid[i]=val[i];
			v[i]=MX-val[i];
		}
		else{
			int K=sz[i]+1>>1;
			K=sz[i]+1-K;
			mid[i]=T.query(Tid[dfn[i]-1],Tid[post[i]],1,MX,K);
			mid1[i]=T.query(Tid[dfn[i]-1],Tid[post[i]],1,MX,K-1);
			v[i]=mid1[i]-mid[i];
		}
	}
	ans=0;
	solve_dfs(1);
	rep(i,1,n+1)ans+=mid[i];
	print(ans);
	putchar('\n');
}
int main(){
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	Aug.02.16
	
	Tags:data structure
	Submissions:3
	
	Exe.Time 1029MS
	Exe.Memory 40372K
	Code Len. 4036B
	
*/

