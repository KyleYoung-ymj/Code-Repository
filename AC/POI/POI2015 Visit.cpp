#include <bits/stdc++.h>
#define fi first
#define se second
#define y0 vjfuyg
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
template<class T>void rd(T &x)
{
	x=0;
	char c;
	while(c=getchar(),c<48);
	do x=(x<<3)+(x<<1)+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_pt(T x)
{
	if(!x)return;
	rec_pt(x/10);
	putchar(x%10^48);
}
template<class T>void pt(T x)
{
	if(!x)putchar('0');
	else rec_pt(x);
}
template<class T>inline void ptn(T x)
{
	pt(x),putchar('\n');
}
template<class T>inline void Max(T &a,T b)
{
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b)
{
	if(b<a)a=b;
}
template<class T>T gcd(T a,T b)
{
	return b?gcd(b,a%b):a;
}
inline void mod_add(int &a,int b,int m=mod)
{
	if((a+=b)>=m)a-=m;
}
inline void mod_minus(int &a,int b,int m=mod)
{
	if((a-=b)<0)a+=m;
}
int mod_pow(int a,int b,int m=mod)
{
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}
inline int calc_inv(int x,int m=mod)
{
	return mod_pow(x,m-2);
}


const int N=(int)5e4+5,T=300;

int tot_edge,head[N],val[N],par[N],dep[N],sz[N],son[N],top[N],stk[N],tp,dfs_clock,dfn[N],arr[N],perm[N],dp[T][N];
pii edge[N<<1];

void add_edge(int u,int v)
{
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}

void dfs(int u)
{
	rep(i,1,T)
	{
		dp[i][u]=val[u];
		if(tp>=i)dp[i][u]+=dp[i][stk[tp-i]];
	}
	stk[tp++]=u;
	sz[u]=1;
	for(int i=head[u];~i;i=edge[i].se)
	{
		int v=edge[i].fi;
		if(v==par[u])continue;
		par[v]=u;
		dep[v]=dep[u]+1;
		dfs(v);
		sz[u]+=sz[v];
		if(!son[u]||sz[v]>sz[son[u]])son[u]=v;
	}
	--tp;
}

void allc_dfs(int u)
{
	arr[dfn[u]=++dfs_clock]=u;
	if(!son[u])return;
	top[son[u]]=top[u];
	allc_dfs(son[u]);
	for(int i=head[u];~i;i=edge[i].se)
	{
		int v=edge[i].fi;
		if(v==par[u]||v==son[u])continue;
		top[v]=v;
		allc_dfs(v);
	}
}

int up(int u,int step)
{
	for(int cnt;step;step-=cnt,u=par[top[u]])
		if(!par[top[u]]||(cnt=dep[u]-dep[par[top[u]]])>step)return arr[dfn[u]-step];
	return u;
}

int lca(int u,int v)
{
	for(;top[u]!=top[v];u=par[top[u]])if(dep[top[u]]<dep[top[v]])swap(u,v);
	if(dep[u]>dep[v])swap(u,v);
	return u;
}

inline int ceiling(int a,int b)
{
	return (a+b-1)/b;
}

void consider(int u,int v,int step)
{
	int ans,anc=lca(u,v),lst=(dep[u]+dep[v]-(dep[anc]<<1))%step;
	if(step<T)
	{
		ans=0;
		if(lst&&lst<dep[v]-dep[anc])
		{
			ans=val[v];
			v=up(v,lst);
		}
		ans+=dp[step][u]+dp[step][v];
		if(!((dep[u]-dep[anc])%step))ans-=val[anc];
		
		{
			int tmp=ceiling(dep[u]-dep[anc],step)*step;
			if(tmp==dep[u]-dep[anc])tmp+=step;
			if(dep[u]>=tmp)ans-=dp[step][up(u,tmp)];
		}
		{
			int tmp=ceiling(dep[v]-dep[anc],step)*step;
			if(tmp==dep[v]-dep[anc])tmp+=step;
			if(dep[v]>=tmp)ans-=dp[step][up(v,tmp)];
		}
	}
	else
	{
		ans=val[u]+val[v];
		while(dep[u]-dep[anc]>=step)ans+=val[u=up(u,step)];
		if(lst&&lst<dep[v]-dep[anc])ans+=val[v=up(v,lst)];
		while(dep[v]-dep[anc]>=step)ans+=val[v=up(v,step)];
		if(u==v)ans-=val[u];
	}
	ptn(ans);
}

int main()
{
	int n;
	rd(n);
	rep(i,1,n+1)
	{
		rd(val[i]);
		head[i]=-1;
	}
	for(int i=1,u,v;i<n;++i)
	{
		rd(u),rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1);
	top[1]=1;
	allc_dfs(1);
	rep(i,0,n)rd(perm[i]);
	for(int i=0,step;i<n-1;++i)
	{
		rd(step);
		consider(perm[i],perm[i+1],step);
	}
	return 0;
}

/*
	
	Oct.28.16
	
	Tags:tree,dp
	Submissions:1
	
	Memory 66116KB
	Time 908MS
	Code Length 4476B
	
*/

