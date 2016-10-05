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


const int N=(int)1e3+5,M=(int)2e3+5;

struct Network_Flow{
	static const int V=N,E=(int)1e5+5;
	int sink,tot_edge,head[V],arc[V],dist[V],que[V];
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
		for(int i=head[u];~i;i=edge[i].nxt){
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
}nwf;

int n,m,in[N],out[N];

int id[N][N];

struct Edge{
	int u,v,a,b;
	void Rd(){
		rd(u),rd(v),rd(a),rd(b);
		if(a>b){
			swap(u,v);
			swap(a,b);
		}
	}
}edge[M];

struct Graph{
	int tot_edge,head[N],top,stk[M];
	bool mark[M];
	struct Edge{
		int to,nxt;
		Edge(){}
		Edge(int to,int nxt):to(to),nxt(nxt){}
	}edge[M];
	void add_edge(int u,int v){
		edge[tot_edge]=Edge(v,head[u]);
		head[u]=tot_edge++;
	}
	void init(){
		tot_edge=0;
		memset(head,-1,n+1<<2);
		memset(mark,false,M);
	}
	void dfs(int u){
		for(int &i=head[u];~i;i=edge[i].nxt)if(!mark[i]){
			int v=edge[i].to;
			mark[i]=true;
			dfs(v);
			stk[top++]=id[u][v];
			if(i==-1)break;
		}
	}
	void find_Euler_Cycle(int ans){
		top=0;
		dfs(1);
		assert(top==m);
		int cur=1;
		per(i,0,top){
			if(::edge[stk[i]].u==cur){
				cur=::edge[stk[i]].v;
				assert(::edge[stk[i]].a<=ans);
			}
			else{
				assert(::edge[stk[i]].v==cur);
				cur=::edge[stk[i]].u;
				assert(::edge[stk[i]].b<=ans);
			}
			pt(stk[i]+1),putchar(" \n"[!i]);
		}
		assert(cur==1);
	}
}G;

bool judge(int val){
	nwf.init(n+1);
	memset(in,0,n+1<<2);
	memset(out,0,n+1<<2);
	rep(i,0,m){
		int u=edge[i].u,v=edge[i].v,a=edge[i].a,b=edge[i].b;
		if(b<=val)nwf.add_edge(u,v,1);
		++out[u],++in[v];
	}
	int tot=0;
	rep(i,1,n+1){
		if(in[i]+out[i]&1)return false;
		if(in[i]>out[i]){
			int delta=in[i]-out[i]>>1;
			tot+=delta;
			nwf.add_edge(i,n+1,delta);
		}
		else if(in[i]<out[i]){
			int delta=out[i]-in[i]>>1;
			nwf.add_edge(0,i,delta);
		}
	}
	return nwf.Dinic()==tot;
}

int from[M];

int main(){
	rd(n),rd(m);
	int L=0,R=0,ans=-1;
	rep(i,0,m){
		edge[i].Rd();
		id[edge[i].u][edge[i].v]=id[edge[i].v][edge[i].u]=i;
		Max(L,edge[i].a);
		Max(R,edge[i].b);
	}
	while(L<=R){
		int mid=L+R>>1;
		if(judge(mid)){
			ans=mid;
			R=mid-1;
		}
		else L=mid+1;
	}
	if(ans==-1)puts("NIE");
	else{
		ptn(ans);
		judge(ans);
		rep(u,1,n+1)for(int i=nwf.head[u];~i;i=nwf.edge[i].nxt){
			int v=nwf.edge[i].to;
			if(v<=n&&!nwf.edge[i].cap){
				assert(!from[id[u][v]]);
				from[id[u][v]]=v;
			}
		}
		G.init();
		rep(i,0,m){
			int u=edge[i].u,v=edge[i].v,a=edge[i].a,b=edge[i].b;
			if(b<=ans){
				if(from[i]==u)G.add_edge(u,v);
				else G.add_edge(v,u);
			}
			else G.add_edge(u,v);
		}
		G.find_Euler_Cycle(ans);
	}
	return 0;
}

/*
	
	Oct.02.16
	
	Tags:flow,Euler Circuit
	Submissions:9
	
	Memory 8084KB
	Time 12ms
	Code Length 5812B
	
*/

