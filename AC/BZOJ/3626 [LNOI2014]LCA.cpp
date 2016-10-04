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
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<ll,ll> pll;
const int mod=201314,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
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
const int N=(int)5e4+5;
int n,tot_son,head[N],
	dep[N],par[N],
	allc,sz[N],heavy_son[N],top[N],Tid[N];
ll bit0[N],bit1[N],ans[N];
pii son[N];
piii query[N];
struct Ope{
	int pos,tar,sgn,id;
	Ope(){}
	Ope(int pos,int tar,int sgn,int id):pos(pos),tar(tar),sgn(sgn),id(id){}
	inline bool operator <(const Ope &tmp)const{
		return pos<tmp.pos;
	}
}ope[N<<1];
inline void add_son(int u,int v){
	son[tot_son]=pii(v,head[u]);
	head[u]=tot_son++;
}
void dfs(int cur){
	sz[cur]=1;
	for(int i=head[cur];~i;i=son[i].se){
		int to=son[i].fi;
		par[to]=cur;
		dep[to]=dep[cur]+1;
		dfs(to);
		sz[cur]+=sz[to];
		if(!heavy_son[cur]||sz[to]>sz[heavy_son[cur]])
			heavy_son[cur]=to;
	}
}
void allc_dfs(int cur,int anc){
	top[cur]=anc;
	Tid[cur]=++allc;
	if(heavy_son[cur])allc_dfs(heavy_son[cur],anc);
	for(int i=head[cur];~i;i=son[i].se){
		int to=son[i].fi;
		if(to==heavy_son[cur])continue;
		allc_dfs(to,to);
	}
}
void add(ll *bit,int x,int v){
	for(;x<=n;x+=lowbit(x))
		bit[x]+=v;
}
ll sum(ll *bit,int x){
	ll res=0;
	for(;x;x-=lowbit(x))
		res+=bit[x];
	return res;
}
void add_interval(int L,int R){
	add(bit0,L,1);
	add(bit0,R+1,-1);
	add(bit1,L,1-L);
	add(bit1,R+1,R);
}
inline ll query_sum(int x){
	return sum(bit0,x)*x+sum(bit1,x);
}
inline ll query_interval_sum(int L,int R){
	return query_sum(R)-query_sum(L-1);
}
void Add(int u){
	for(;top[u];u=par[top[u]])
		add_interval(Tid[top[u]],Tid[u]);
	add_interval(1,Tid[u]);
}
ll Query(int u){
	ll res=0;
	for(;top[u];u=par[top[u]])
		res+=query_interval_sum(Tid[top[u]],Tid[u]);
	return res+query_interval_sum(1,Tid[u]);
}
int main(){
	int m;
	rd(n);rd(m);
	memset(head,-1,n<<2);
	for(int i=1,fa;i<n;++i){
		rd(fa);
		add_son(fa,i);
	}
	dep[0]=1;
	dfs(0);
	allc_dfs(0,0);
	int tot=0;
	for(int i=0;i<m;++i){
		rd(query[i].se.fi);rd(query[i].se.se);
		rd(query[i].fi);
		ope[tot++]=Ope(query[i].se.se,query[i].fi,1,i);
		if(query[i].se.fi)ope[tot++]=Ope(query[i].se.fi-1,query[i].fi,-1,i);
	}
	sort(ope,ope+tot);
	for(int i=0,j=0;i<n&&j<tot;++i){
		Add(i);
		for(;j<tot&&ope[j].pos==i;++j)
			ans[ope[j].id]+=ope[j].sgn*Query(ope[j].tar);
	}
	for(int i=0;i<m;++i)
		printf("%d\n",(int)(ans[i]%mod));
	return 0;
}
/*
	
	Jul.13.16

	Tags:HLD,bit
	Submissions:2

	Memory 6456kb
	Time 640ms
	Code Length 3522B

*/
