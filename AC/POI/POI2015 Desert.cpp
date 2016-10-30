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
#define rep(i,s,t) for(int i=(s),_t=(t);i<_t;++i)
#define per(i,s,t) for(int i=(t)-1,_s=(s);i>=_s;--i)
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
	int res=m==1?0:1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}


const int N=(int)1e5+5,M=(int)2e5+5,NODE=(N<<2)+M,E=7e6+5;

int arr[N],id[N],pos[N],tot_edge,head[NODE],deg[NODE],que[NODE],lim[NODE];
bool mark[NODE];

struct Edge
{
	int to,nxt;
	bool cost;
	Edge(){}
	Edge(int to,int nxt,int cost):to(to),nxt(nxt),cost(cost){}
}
edge[E];

void add_edge(int u,int v,bool c)
{
	++deg[v];
	edge[tot_edge]=Edge(v,head[u],c);
	head[u]=tot_edge++;
}

struct Segment_Tree
{
	int id[NODE],allc;
	void cons(int L,int R,int k=1)
	{
		id[k]=++allc;
		if(L==R)
		{
			::id[L]=id[k];
			return;
		}
		int mid=L+R>>1;
		cons(L,mid,lson);
		cons(mid+1,R,rson);
		add_edge(id[lson],id[k],0);
		add_edge(id[rson],id[k],0);
	}
	void add(int L,int R,int l,int r,int tar,int k=1)
	{
		if(L==l&&R==r)return add_edge(id[k],tar,1);
		int mid=l+r>>1;
		if(R<=mid)add(L,R,l,mid,tar,lson);
		else if(L>mid)add(L,R,mid+1,r,tar,rson);
		else
		{
			add(L,mid,l,mid,tar,lson);
			add(mid+1,R,mid+1,r,tar,rson);
		}
	}
}
smt;

int main()
{
	int n,info,m;
	rd(n),rd(info),rd(m);
	memset(head,-1,sizeof head);
	for(int pos,val;info--;)
	{
		rd(pos),rd(val);
		arr[pos]=val;
	}
	smt.cons(1,n);
	int tot=smt.allc+1;
	for(int i=0,L,R,amt;i<m;++i,++tot)
	{
		rd(L),rd(R),rd(amt);
		rep(i,0,amt)
		{
			rd(pos[i]);
			add_edge(tot,id[pos[i]],0);
			if(i&&pos[i-1]<pos[i]-1)smt.add(pos[i-1]+1,pos[i]-1,1,n,tot);
		}
		if(pos[0]>L)smt.add(L,pos[0]-1,1,n,tot);
		if(pos[amt-1]<R)smt.add(pos[amt-1]+1,R,1,n,tot);
	}
	int L=0,R=0;
	rep(i,1,n+1)
	{
		lim[id[i]]=arr[i]?arr[i]:1;
		if(!deg[id[i]])que[R++]=id[i];
	}
	while(L<R)
	{
		int u=que[L++];
		mark[u]=true;
		for(int i=head[u];~i;i=edge[i].nxt)
		{
			int v=edge[i].to;
			Max(lim[v],lim[u]+edge[i].cost);
			if(!--deg[v])que[R++]=v;
		}
	}
	rep(i,1,tot)if(!mark[i])return puts("NIE"),0;
	rep(i,1,n+1)if(lim[id[i]]>(int)1e9||arr[i]&&lim[id[i]]>arr[i])return puts("NIE"),0;
	puts("TAK");
	rep(i,1,n+1)pt(lim[id[i]]),putchar(" \n"[i==n]);
	return 0;
}

/*

	Oct.30.16
	
	Tags:graph theory,toposort,segment tree
	Submissions:3
	
	Memory 97208KB
	Time 240MS
	Code Length 3950B
	
*/

