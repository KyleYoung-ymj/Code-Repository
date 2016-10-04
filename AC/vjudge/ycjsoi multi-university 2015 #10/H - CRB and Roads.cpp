#include <cstdio>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<ll,ll> pll;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
void rd(int &res){
    res=0;
    char c;
    while(c=getchar(),c<48);
    do res=(res<<3)+(res<<1)+(c^48);
        while(c=getchar(),c>47);
}
inline void Max(int &a,int b){
    if(b>a)a=b;
}
inline void Min(int &a,int b){
    if(b<a)a=b;
}
inline void mod_add(int &a,int b){
    if((a+=b)>=mod)a-=mod;
}
const int N=(int)2e4+5,M=(int)1e5+5;
bitset<N>bs[N];
int deg[N],que[N],tot_edge[2],head[2][N];
pii edge[2][M];
void add_edge(bool id,int u,int v){
	edge[id][tot_edge[id]]=pii(v,head[id][u]);
	head[id][u]=tot_edge[id]++;
}
void solve(){
	int n,m;
	rd(n);rd(m);
	tot_edge[0]=tot_edge[1]=0;
	for(int i=0;i<2;++i)
		memset(head[i],-1,n+1<<2);
	int u,v;
	while(m--){
		rd(u);rd(v);
		add_edge(0,u,v);
		++deg[v];
	}
	int L=0,R=0;
	for(int i=1;i<=n;++i){
		if(!deg[i])que[R++]=i;
		bs[i].reset();
		bs[i][i]=true;
	}
	while(L<R){
		int cur=que[L++];
		for(int i=head[0][cur];~i;i=edge[0][i].se){
			int to=edge[0][i].fi;
			add_edge(1,to,cur);
			if(!--deg[to])que[R++]=to;
		}
	}
	int ans=0;
	for(int i=0;i<L;++i){
		int v=que[i];
		for(int j=head[1][v];~j;j=edge[1][j].se){
			int u=edge[1][j].fi;
			ans+=bs[v][u];
			bs[v]|=bs[u];
		}
	}
	printf("%d\n",ans);
}
int main(){
	int cas;
	for(rd(cas);cas--;)solve();
	return 0;
}
/*
	
	Jul.14.16

	Tags:graph theory,toposort,bitset
	Submissions:2

	Memory(KB) 52452
	Time(ms) 2979
	Length(Bytes) 1882

*/
