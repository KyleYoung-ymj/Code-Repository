#include <bits/stdc++.h>
#define fi first
#define se second
#define y1 fsdakj
#define lson (k<<1)
#define rson (k<<1|1)
#define lowbit(x) ((x)&-(x))
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define debug(x) cout<<#x<<" = "<<(x)<<endl
#define rep(i,s,t) for(int i=(s),_t=(t);i<_t;++i)
#define per(i,s,t) for(int i=(t)-1,_s=(s);i>=s;--i)
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int inf=0x7fffffff,mod=(int)1e9+7;
const ll INF=1ll<<60;
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


const int N=(int)1e4+5,M=(int)2e3+5;

// Network Flow
const int V=N+M,E=(int)1e5+5;
int sink,tot_edge,head[V],arc[V],que[V],dist[V];
struct Edge{
	int to,nxt,cap;
	Edge(){}
	Edge(int to,int nxt,int cap):to(to),nxt(nxt),cap(cap){}
}edge[E<<1];
void add_edge(int u,int v,int cap){
	edge[tot_edge]=Edge(v,head[u],cap);
	head[u]=tot_edge++;
	edge[tot_edge]=Edge(u,head[v],0);
	head[v]=tot_edge++;
}
void init(int n){
	sink=n;
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

bool type[N];
int cost[N],tar[15];

int main(){
	int n,m,g;
	rd(n),rd(m),rd(g);
	int tot=0;
	init(n+m+1);
	rep(i,1,n+1)rd(type[i]);
	rep(i,1,n+1)rd(cost[i]);
	rep(i,1,n+1){
		if(type[i])add_edge(i,sink,cost[i]);
		else add_edge(0,i,cost[i]);
	}
	for(int i=1,type,val,cnt,flag;i<=m;++i){
		rd(type),rd(val),rd(cnt);
		rep(j,0,cnt)rd(tar[j]);
		rd(flag);
		tot+=val;
		int id=n+i;
		if(type){
			add_edge(id,sink,val+flag*g);
			rep(j,0,cnt)add_edge(tar[j],id,inf);
		}
		else{
			add_edge(0,id,val+flag*g);
			rep(j,0,cnt)add_edge(id,tar[j],inf);
		}
	}
	printf("%d\n",tot-Dinic());
	return 0;
}

/*
	
	Sept.28.16
	
	Tags:minimum cut
	Submissions:1
	
	Time 31ms
	Memory 2600KB
	
*/

