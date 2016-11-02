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
#include <string>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define y0 fjsdjv
#define y1 fjsdik
#define lson (k<<1)
#define rson (k<<1|1)
#define pb push_back
#define lowbit(x) ((x)&-(x))
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define debug(x) cout<<#x<<" = "<<(x)<<endl
#define rep(i,s,t) for(int i=(s),_t=(t);i<_t;++i)
#define per(i,s,t) for(int i=(t)-1,_s=(s);i>=_s;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int inf=0x7fffffff,mod=(int)1e9+7,dxy[]={-1,0,1,0,-1};
const ll INF=1ll<<60;
template<class T>void rd(T &x)
{
	x=0;
	char c;
	while(c=getchar(),c<48);
	do x=x*10+(c^48);
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
int mod_pow(int a,int b,int m=mod)
{
	int res=m==1?0:1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}


const int N=(int)5e4+5,LG=18;

typedef int Array[N];

int n,m,tot_edge,dfs_clock,cnt_son,cnt_leaf,par[LG][N];
Array head,par_cost,mx_lg,dfn,post,arr,node,st_node,en_node,son,leaf,st_leaf,en_leaf,rem,need;
ll dep[N],mx_dep;
bool is_leaf[N];
set<int> st;
typedef set<int>::iterator ite;

struct Edge
{
	int to,nxt,cost;
	Edge(){}
	Edge(int to,int nxt,int cost):to(to),nxt(nxt),cost(cost){}
}
edge[N<<1];

void add_edge(int u,int v,int cost)
{
	edge[tot_edge]=Edge(v,head[u],cost);
	head[u]=tot_edge++;
}

void dfs(int u)
{
	arr[dfn[u]=++dfs_clock]=u;
	Max(mx_dep,dep[u]);
	if(u>1)for(int i=1;;++i)
	{
		par[i][u]=par[i-1][par[i-1][u]];
		if(!par[i][u])
		{
			mx_lg[u]=i;
			break;
		}
	}
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(v==par[0][u])continue;
		par[0][v]=u;
		par_cost[v]=edge[i].cost;
		dep[v]=dep[u]+edge[i].cost;
		dfs(v);
	}
	post[u]=dfs_clock;
	if(dfn[u]==post[u])is_leaf[leaf[cnt_leaf++]=u]=true;
}

inline bool cmp1(int a,int b)
{
	return dfn[a]<dfn[b];
}

inline bool cmp2(int a,int b)
{
	return dep[a]>dep[b];
}

int consider(int u,ll dist)
{
	per(i,0,mx_lg[u])if(i<mx_lg[u]&&dep[u]-dep[par[i][u]]<=dist)
	{
		dist-=dep[u]-dep[par[i][u]];
		u=par[i][u];
	}
	return u;
}

void fun(int L,int R)
{
	ite l=st.lower_bound(L);
	if(l==st.end())return;
	ite r=st.upper_bound(R);
	st.erase(l,r);
}

bool judge(ll val)
{
	int cnt_rem=0,cnt_need=0;
	rep(i,0,cnt_son)
	{
		int cnt_itv=0;
		bool flag=false;
		st.clear();
		rep(j,st_leaf[i],en_leaf[i])st.insert(dfn[leaf[j]]);
		rep(j,st_node[i],en_node[i])
		{
			int u=node[j],
				v=consider(u,val);
			if(v==1)
			{
				if(!flag)
				{
					if(val-dep[u]>=par_cost[son[i]])rem[cnt_rem++]=val-dep[u];
					else flag=true;
				}
				else rem[cnt_rem++]=val-dep[u];
			}
			else if(!flag)
			{
				fun(dfn[v],post[v]);
				if(st.empty())flag=true;
			}
		}
		if(!flag)need[cnt_need++]=par_cost[son[i]];
	}
	if(!cnt_need)return true;
	if(cnt_rem<cnt_need)return false;
	sort(need,need+cnt_need,greater<int>());
	sort(rem,rem+cnt_rem,greater<int>());
	rep(i,0,cnt_need)if(rem[i]<need[i])return false;
	return true;
}

int main()
{
	rd(n);
	memset(head,-1,n+1<<2);
	for(int i=1,u,v,cost;i<n;++i)
	{
		rd(u),rd(v),rd(cost);
		add_edge(u,v,cost);
		add_edge(v,u,cost);
	}
	
	rd(m);
	rep(i,0,m)rd(node[i]);
	
	int mx_par_cost=0;
	for(int i=head[1];~i;i=edge[i].nxt)son[cnt_son++]=edge[i].to;
	if(m<cnt_son)return puts("-1"),0;
	
	dfs(1);
	rep(i,0,cnt_son)Max(mx_par_cost,par_cost[son[i]]);
	sort(node,node+m,cmp1);
	for(int i=0,j=0;i<cnt_son;++i)
	{
		st_node[i]=j;
		for(;j<m&&dfn[node[j]]<=post[son[i]];++j);
		en_node[i]=j;
		sort(node+st_node[i],node+en_node[i],cmp2);
	}
	for(int i=0,j=0;i<cnt_son;++i)
	{
		st_leaf[i]=j;
		for(;j<cnt_leaf&&dfn[leaf[j]]<=post[son[i]];++j);
		en_leaf[i]=j;
	}
	
	ll ans;
	for(ll L=0,R=mx_dep+mx_par_cost;L<=R;)
	{
		ll mid=L+R>>1;
		if(judge(mid))
		{
			ans=mid;
			R=mid-1;
		}
		else L=mid+1;
	}
	ptn(ans);
	return 0;
}

/*
	
	Nov.01.16
	
	Tags:greedy,binary search,tree,multiply
	Submissions:3
	
	Memory 5684K
	Time 234MS
	Code Length 4.6K
	
*/

