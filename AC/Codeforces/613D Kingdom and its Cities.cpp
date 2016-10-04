#include <bits/stdc++.h>
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
const int inf=0x7fffffff,mod=(int)1e9+7,dxy[]={-1,0,1,0,-1};
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

int tot_edge,head[N],dfs_clock,dfn[N],post[N],node[N],par[N],dep[N],top[N],sz[N],heavy_son[N],stk[N],dp[2][N];
bool mark[N],flag[N];
pii edge[N<<1];

void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}

void dfs(int u){
	dfn[u]=++dfs_clock;
	sz[u]=1;
	for(int i=head[u];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==par[u])continue;
		par[son]=u;
		dep[son]=dep[u]+1;
		dfs(son);
		sz[u]+=sz[son];
		if(!heavy_son[u]||sz[son]>sz[heavy_son[u]])heavy_son[u]=son;
	}
	post[u]=dfs_clock;
}

void allc_dfs(int u,int anc){
	top[u]=anc;
	if(heavy_son[u])allc_dfs(heavy_son[u],anc);
	for(int i=head[u];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==par[u]||son==heavy_son[u])continue;
		allc_dfs(son,son);
	}
}

int lca(int u,int v){
	for(;top[u]!=top[v];u=par[top[u]])if(dep[top[u]]<dep[top[v]])swap(u,v);
	if(dep[u]>dep[v])swap(u,v);
	return u;
}

inline bool cmp(int a,int b){
	return dfn[a]<dfn[b];
}

inline void remark(int m){
	rep(i,0,m)flag[node[i]]=mark[node[i]]=false;
}

int DP(bool type,int u){
	int &res=dp[type][u];
	if(res==-1){
		if(type){
			if(mark[u])res=N;
			else{
				int sum0=0,sum1=0;
				for(int i=head[u];~i;i=edge[i].se){
					int son=edge[i].fi;
					if(dep[son]<dep[u])continue;
					sum0+=min(DP(0,son),DP(1,son));
					sum1+=DP(1,son);
				}
				res=min(sum0+1,sum1);
			}
		}
		else{
			if(mark[u]){
				res=0;
				for(int i=head[u];~i;i=edge[i].se){
					int son=edge[i].fi;
					if(dep[son]<dep[u])continue;
					int tmp=DP(1,son);
					if(dep[son]>dep[u]+1)Min(tmp,DP(0,son)+1);
					res+=tmp;
				}
			}
			else{
				int sum=0,mi=inf;
				for(int i=head[u];~i;i=edge[i].se){
					int son=edge[i].fi;
					if(dep[son]<dep[u])continue;
					int tmp=DP(1,son);
					if(dep[son]>dep[u]+1)Min(tmp,DP(0,son)+1);
					sum+=tmp;
					Min(mi,DP(0,son)-tmp);
				}
				res=sum+mi;
			}
		}
	}
	return res;
}

void solve(){
	int m;
	rd(m);
	rep(i,0,m){
		rd(node[i]);
		flag[node[i]]=mark[node[i]]=true;
	}
	rep(i,0,m)if(mark[par[node[i]]]){
		remark(m);
		puts("-1");
		return;
	}
	sort(node,node+m,cmp);
	rep(i,1,m){
		int anc=lca(node[i-1],node[i]);
		if(!flag[anc]){
			node[m++]=anc;
			flag[anc]=true;
		}
	}
	if(!flag[1]){
		node[m++]=1;
		flag[1]=true;
	}
	sort(node,node+m,cmp);
	tot_edge=0;
	rep(i,0,m){
		head[node[i]]=-1;
		dp[0][node[i]]=dp[1][node[i]]=-1;
	}
	int top=0;
	stk[top++]=node[0];
	rep(i,1,m){
		int u;
		for(;;--top){
			u=stk[top-1];
			if(dfn[node[i]]<=post[u])break;
		}
		add_edge(u,node[i]);
		stk[top++]=node[i];
	}
	ptn(min(DP(0,1),DP(1,1)));
	remark(m);
}

int main(){
	int n,m;
	rd(n);
	memset(head,-1,n+1<<2);
	for(int i=1,u,v;i<n;++i){
		rd(u),rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1);
	allc_dfs(1,1);
	for(rd(m);m--;)solve();
	return 0;
}

/*
	
	Oct.02.16
	
	Tags:virtual tree,dp
	Submissions:1
	
	Time 77ms
	Memory 9200KB
	
*/

