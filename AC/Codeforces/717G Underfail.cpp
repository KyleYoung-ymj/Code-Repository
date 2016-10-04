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


const int N=505;

// Network Flow
const int V=N,E=(int)1e5+5;
int sink,tot_edge,head[V],que[V],flow[V],pre[V],pre_edge[V],dist[V];
bool in_que[V];
struct Edge{
	int to,nxt,cap,cost;
	Edge(){}
	Edge(int to,int nxt,int cap,int cost):to(to),nxt(nxt),cap(cap),cost(cost){}
}edge[E<<1];
void add_edge(int u,int v,int cap,int cost){
	edge[tot_edge]=Edge(v,head[u],cap,cost);
	head[u]=tot_edge++;
	edge[tot_edge]=Edge(u,head[v],0,-cost);
	head[v]=tot_edge++;
}
void init(int n){
	sink=n;
	tot_edge=0;
	memset(head,-1,n+1<<2);
}
bool SPFA(){
	int L=0,R=0;
	rep(i,0,sink+1)dist[i]=inf;
	for(dist[que[R++]=0]=0,flow[0]=inf;L!=R;){
		int u=que[L++];
		if(L==V)L=0;
		in_que[u]=false;
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].cap&&dist[v]>dist[u]+edge[i].cost){
				dist[v]=dist[u]+edge[i].cost;
				pre[v]=u;
				pre_edge[v]=i;
				flow[v]=min(flow[u],edge[i].cap);
				if(!in_que[v]){
					que[R++]=v;
					if(R==V)R=0;
					in_que[v]=true;
				}
			}
		}
	}
	return dist[sink]<inf;
}
int mincost_maxflow(){
	int cost=0;
	while(SPFA()){
		cost+=dist[sink]*flow[sink];
		for(int cur=sink;cur;cur=pre[cur]){
			edge[pre_edge[cur]].cap-=flow[sink];
			edge[pre_edge[cur]^1].cap+=flow[sink];
		}
	}
	return cost;
}

string str,sub;

int main(){
	int n,m,K;
	rd(n);
	cin>>str;
	str="$"+str+"$";
	n+=2;
	init(n+1);
	rd(m);
	for(int val;m--;){
		cin>>sub;
		rd(val);
		if(!val)continue;
		rep(i,0,n-siz(sub))if(str.substr(i,siz(sub))==sub)add_edge(i+1,i+siz(sub)+1,1,-val);
	}
	rd(K);
	rep(i,0,sink)add_edge(i,i+1,K,0);
	ptn(-mincost_maxflow());
	return 0;
}

/*
	
	Sept.28.16
	
	Tags:flow
	Submissions:2
	
	Time 15ms
	Memory 3200KB
	
*/

