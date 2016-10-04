#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define y1 jfskav
#define pb push_back
#define lson (k<<1)
#define rson (k<<1|1)
#define lowbit(x) ((x)&-(x))
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define debug(x) cout<<#x<<" = "<<(x)<<endl
#define rep(i,s,t) for(register int i=(s),_t=(t);i<_t;++i)
#define per(i,s,t) for(register int i=(t)-1,_s=(s);i>=_s;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int mod=(int)1e9+7,inf=0x7fffffff,dxy[]={-1,0,1,0,-1};
const ll INF=1ll<<60;
const db pi=acos(-1),eps=1e-6;
template<class T>void rd(T &x){
	x=0;
	char c;
	while(c=getchar(),c<48);
	do x=(x<<3)+(x<<1)+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_pt(T x){
	if(!x)return;
	rec_pt(x/10);
	putchar(x%10^48);
}
template<class T>void pt(T x){
	if(!x)putchar('0');
	else rec_pt(x);
}
template<class T>inline void ptn(T x){
	pt(x),putchar('\n');
}
template<class T>inline void Max(T &a,T b){
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b){
	if(b<a)a=b;
}
template<class T>T gcd(T a,T b){
	return b?gcd(b,a%b):a;
}
inline void mod_add(int &a,int b,int m=mod){
	if((a+=b)>=m)a-=m;
}
inline void mod_minus(int &a,int b,int m=mod){
	if((a-=b)<0)a+=m;
}
int mod_pow(int a,int b,int m=mod){
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}
inline int calc_inv(int x,int m=mod){
	return mod_pow(x,m-2);
}


const int N=(int)1e5+5;

int tot_edge,head[N];

struct Edge{
	int to,nxt,cost;
	Edge(){}
	Edge(int to,int nxt,int cost):to(to),nxt(nxt),cost(cost){}
}edge[N<<1];

void add_edge(int u,int v,int c){
	edge[tot_edge]=Edge(v,head[u],c);
	head[u]=tot_edge++;
}

int aux[N];
struct Tree{
	static const int LG=18;
	int root,cnt_leaf,leaf[N],dep[N],mx_dep[N],val[N],sum[N],id[N],par[LG][N];
	static inline bool cmp(int a,int b){
		return aux[a]>aux[b];
	}
	void dfs(int cur){
		rep(i,1,LG)par[i][cur]=par[i-1][par[i-1][cur]];
		int &ptr=mx_dep[cur];
		ptr=cur;
		for(int i=head[cur];~i;i=edge[i].nxt){
			int son=edge[i].to;
			if(son==par[0][cur])continue;
			par[0][son]=cur;
			dep[son]=dep[cur]+edge[i].cost;
			dfs(son);
			if(dep[mx_dep[son]]>dep[ptr])ptr=mx_dep[son];
		}
		if(ptr==cur)leaf[cnt_leaf++]=cur;
	}
	void allc_dfs(int cur){
		aux[cur]=val[cur];
		for(int i=head[cur];~i;i=edge[i].nxt){
			int son=edge[i].to,c=edge[i].cost;;
			if(son==par[0][cur])continue;
			if(mx_dep[cur]==mx_dep[son])val[son]=val[cur]+c;
			else val[son]=c;
			allc_dfs(son);
		}
	}
	void init(int _root){
		root=_root;
		dep[root]=cnt_leaf=val[root]=0;
		par[0][root]=root;
		dfs(root);
		allc_dfs(root);
		sort(leaf,leaf+cnt_leaf,cmp);
		sum[0]=val[leaf[0]];
		rep(i,1,cnt_leaf){
			sum[i]=sum[i-1]+val[leaf[i]];
			id[leaf[i]]=i;
		}
	}
	int solve(int x,int y){
		--y;
		if(y>=cnt_leaf-1)return sum[cnt_leaf-1];
		if(y>=id[mx_dep[x]])return sum[y];
		int anc=x;
		per(i,0,LG)if(id[mx_dep[par[i][anc]]]>y)anc=par[i][anc];
		anc=par[0][anc];
		return sum[y]+dep[mx_dep[x]]-dep[anc]-min(val[leaf[y]],dep[mx_dep[anc]]-dep[anc]);
	}
}T[2];

int mx_dis,ID,par[N],dist[N];

void dfs(int cur){
	if(dist[cur]>mx_dis){
		mx_dis=dist[cur];
		ID=cur;
	}
	for(int i=head[cur];~i;i=edge[i].nxt){
		int son=edge[i].to;
		if(son==par[cur])continue;
		par[son]=cur;
		dist[son]=dist[cur]+edge[i].cost;
		dfs(son);
	}
}
void init(){
	dfs(1);
	T[0].init(ID);
	par[ID]=dist[ID]=mx_dis=0;
	dfs(ID);
	T[1].init(ID);
}

int main(){
	int n,m;
	rd(n),rd(m);
	memset(head,-1,n+1<<2);
	for(int i=1,u,v,c;i<n;++i){
		rd(u),rd(v),rd(c);
		add_edge(u,v,c);
		add_edge(v,u,c);
	}
	init();
	for(int i=0,x,y,last_ans;i<m;++i){
		rd(x),rd(y);
		if(i)x=(x+last_ans-1)%n+1,y=(y+last_ans-1)%n+1;
		y=(y<<1)-1;
		ptn(last_ans=max(T[0].solve(x,y),T[1].solve(x,y)));
	}
	return 0;
}

/*
	
	Sept.03.16

	Tags:tree,greedy
	Submissions:1

	Time 280ms
	Memory 23500KB

*/
