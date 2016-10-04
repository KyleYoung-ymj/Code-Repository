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


struct Network_Flow{
	static const int N=205,M=205;
	int sink,tot_edge,head[N],arc[N],que[N],dist[N];
	struct Edge{
		int to,nxt,cap;
		Edge(){}
		Edge(int to,int nxt,int cap):to(to),nxt(nxt),cap(cap){}
	}edge[M<<1];
	void add_edge(int u,int v,int c){
		edge[tot_edge]=Edge(v,head[u],c);
		head[u]=tot_edge++;
		edge[tot_edge]=Edge(u,head[v],0);
		head[v]=tot_edge++;
	}
	void init(int n){
		tot_edge=0;
		sink=n-1;
		memset(head,-1,sink+1<<2);
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
		assert(f);
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
	int solve(int n,int m){
		init(n);
		for(int u,v,c;m--;){
			rd(u),rd(v),rd(c);
			add_edge(u-1,v-1,c);
		}
		return Dinic();
	}
}nwf;

int main(){
	int n,m;
	while(~scanf("%d%d",&m,&n))ptn(nwf.solve(n,m));
	return 0;
}

/*
	
	Sept.22.16

	Problem:POJ1273
	
*/
