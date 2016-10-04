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


const int N=(int)1e4+5;

pii lim[N];

// Network Flow
const int V=N<<2,E=(int)1e5+5;
int sink,tot_edge,head[V],arc[V],que[V],dist[V];
struct Edge{
	int to,nxt,cap;
	Edge(){}
	Edge(int to,int nxt,int cap):to(to),nxt(nxt),cap(cap){}
}edge[E<<1];
void add_edge(int u,int v,int cap){
	if(!cap)return;
	edge[tot_edge]=Edge(v,head[u],cap);
	head[u]=tot_edge++;
	edge[tot_edge]=Edge(u,head[v],0);
	head[v]=tot_edge++;
}
void init(int n){
	sink=n;
	tot_edge=0;
	memset(head,-1,n+1<<2);
}
bool bfs(){
	int L=0,R=0;
	memset(dist,-1,sink+1<<2);
	for(dist[que[R++]=0]=0;L<R;){
		int u=que[L++];
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].cap&&dist[v]==-1)dist[que[R++]=v]=dist[u]+1;
		}
	}
	return ~dist[sink];
}
int dfs(int u,int f){
	if(u==sink)return f;
	int flow=0;
	for(int &i=arc[u];~i;i=edge[i].nxt){
		int v=edge[i].to;
		if(edge[i].cap&&dist[v]==dist[u]+1){
			int d=dfs(v,min(f,edge[i].cap));
			if(d){
				edge[i].cap-=d;
				edge[i^1].cap+=d;
				flow+=d;
				if(!(f-=d))break;
			}
		}
	}
	return flow;
}
int Dinic(){
	int flow=0;
	while(bfs()){
		memcpy(arc,head,sink+1<<2);
		flow+=dfs(0,inf);
	}
	return flow;
}

int id_mod[5],id_num[N],id_lim[N];

int main(){
	int n,m,q;
	rd(n),rd(m),rd(q);
	int tot=q;
	rep(i,0,tot)rd(lim[i].fi),rd(lim[i].se);
	lim[tot++]=pii(m,n);
	sort(lim,lim+tot);
	tot=unique(lim,lim+tot)-lim;
	rep(i,1,tot)if(lim[i].fi==lim[i-1].fi||lim[i].se<lim[i-1].se)return puts("unfair");
	int cur=1;
	rep(i,0,5)id_mod[i]=cur++;
	rep(i,1,m+1)id_num[i]=cur++;
	rep(i,0,tot)id_lim[i]=cur++;
	init(cur);
	rep(i,0,5)add_edge(0,id_mod[i],n/5);
	rep(i,1,m+1)add_edge(id_mod[i%5],id_num[i],1);
	rep(i,0,tot){
		if(!i){
			rep(j,1,lim[i].fi+1)add_edge(id_num[j],id_lim[i],1);
			add_edge(id_lim[i],sink,lim[i].se);
		}
		else{
			rep(j,lim[i-1].fi+1,lim[i].fi+1)add_edge(id_num[j],id_lim[i],1);
			add_edge(id_lim[i],sink,lim[i].se-lim[i-1].se);
		}
	}
	return puts(Dinic()==n?"fair":"unfair");
}

/*
	
	Sept.28.16
	
	Tags:flow
	Submissions:2
	
	Time 15ms
	Memory 3100KB
	
*/

