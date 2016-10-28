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


const int N=(int)5e5+5;

int tot_edge,head[N],par[N],dep[N],dia,ID,ID_,tot,path[N],id[N],mx_dep[N],mx_dep_id[N],pre_mx[N],pre_mx_dia[N],pre_mx_pos[N],suf_mx[N],suf_mx_dia[N],suf_mx_pos[N];
pii edge[N<<1],pre[N],suf[N];
bool mark[N],ban[N];

void add_edge(int u,int v)
{
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}

void dfs(int u)
{
	if(dep[u]>=dia)
	{
		dia=dep[u];
		ID=u;
	}
	for(int i=head[u];~i;i=edge[i].se)
	{
		int v=edge[i].fi;
		if(v==par[u]||ban[v])continue;
		par[v]=u;
		dep[v]=dep[u]+1;
		dfs(v);
	}
}

void redfs(int u)
{
	if(dep[u]>=mx_dep[id[u]])
	{
		mx_dep[id[u]]=dep[u];
		mx_dep_id[id[u]]=u;
	}
	for(int i=head[u];~i;i=edge[i].se)
	{
		int v=edge[i].fi;
		if(v==par[u]||mark[v])continue;
		par[v]=u;
		dep[v]=dep[u]+1;
		id[v]=id[u];
		redfs(v);
	}
}

int calc(pii &tar)
{
	par[tar.fi]=dep[tar.fi]=0;
	dfs(tar.fi);
	for(int cnt=dep[tar.se]>>1;cnt--;)tar.se=par[tar.se];
	return tar.se;
}

void consider_mi()
{
	pre[0]=pii(path[0],path[0]);
	rep(i,1,tot)
	{
		int tmp=mx_dep[i]-i;
		if(tmp>pre_mx[i-1])
		{
			pre_mx[i]=tmp;
			pre_mx_pos[i]=i;
		}
		else
		{
			pre_mx[i]=pre_mx[i-1];
			pre_mx_pos[i]=pre_mx_pos[i-1];
		}
		tmp=i+mx_dep[i]+pre_mx[i-1];
		if(tmp>pre_mx_dia[i-1])
		{
			pre_mx_dia[i]=tmp;
			pre[i]=pii(mx_dep_id[i],mx_dep_id[pre_mx_pos[i-1]]);
		}
		else
		{
			pre_mx_dia[i]=pre_mx_dia[i-1];
			pre[i]=pre[i-1];
		}
	}
	
	suf_mx[tot-1]=tot-1+mx_dep[tot-1];
	suf_mx_pos[tot-1]=tot-1;
	suf[tot-1]=pii(path[tot-1],path[tot-1]);
	per(i,0,tot-1)
	{
		int tmp=mx_dep[i]+i;
		if(tmp>suf_mx[i+1])
		{
			suf_mx[i]=tmp;
			suf_mx_pos[i]=i;
		}
		else
		{
			suf_mx[i]=suf_mx[i+1];
			suf_mx_pos[i]=suf_mx_pos[i+1];
		}
		tmp=mx_dep[i]-i+suf_mx[i+1];
		if(tmp>suf_mx_dia[i+1])
		{
			suf_mx_dia[i]=tmp;
			suf[i]=pii(mx_dep_id[i],mx_dep_id[suf_mx_pos[i+1]]);
		}
		else
		{
			suf_mx_dia[i]=suf_mx_dia[i+1];
			suf[i]=suf[i+1];
		}
	}
	
	int ans=inf,ans_pos;
	rep(i,0,tot-1)// cut the edge (path[i],path[i+1])
	{
		int res=max(pre_mx_dia[i],suf_mx_dia[i+1]);
		Max(res,(pre_mx_dia[i]+1>>1)+(suf_mx_dia[i+1]+1>>1)+1);
		if(res<ans)
		{
			ans=res;
			ans_pos=i;
		}
	}
	printf("%d %d %d %d %d\n",ans,path[ans_pos],path[ans_pos+1],calc(pre[ans_pos]),calc(suf[ans_pos+1]));
}

void consider(int &ans,int &a,int &b,int &c,int &d,int u)
{
	for(int i=head[u];~i;i=edge[i].se)
	{
		int v=edge[i].fi;
		if(mark[v])continue;
		par[v]=dia=dep[v]=0;
		dfs(v);
		par[ID]=dep[ID]=0;
		dfs(ID);
		if(dia+tot>ans)
		{
			ans=dia+tot;
			a=u,b=v;
			c=path[0],d=ID;
		}
	}
}

void consider_mx()
{
	int ans=0,a,b,c,d;
	rep(i,0,tot-1)
	{
		int len=pre_mx_dia[i]+suf_mx_dia[i+1]+1;
		if(len>ans)
		{
			ans=len;
			a=path[i],b=path[i+1];
			c=pre[i].fi,d=suf[i+1].fi;
		}
	}
	rep(i,0,tot)ban[path[i]]=true;
	rep(i,1,tot-1)consider(ans,a,b,c,d,path[i]);
	printf("%d %d %d %d %d\n",ans,a,b,c,d);
}

int main()
{
	int n;
	rd(n);
	memset(head,-1,n+1<<2);
	for(int i=1,u,v;i<n;++i)
	{
		rd(u),rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1);
	par[ID_=ID]=dep[ID]=0;
	dfs(ID);
	for(int u=ID;;u=par[u])
	{
		mark[path[tot++]=u]=true;
		if(!par[u])break;
	}
	rep(i,0,tot)
	{
		dep[path[i]]=0;
		id[path[i]]=i;
		redfs(path[i]);
	}
	consider_mi();
	consider_mx();
	return 0;
}

/*
	
	Oct.28.16
	
	Tags:diameter
	Submissions:3
	
	Memory 67004KB
	Time 780MS
	Code Length 5618B
	
*/

