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
#define pb push_back
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
template<class T>void rd(T &res){
    res=0;
    char c;
    while(c=getchar(),c<48);
    do res=(res<<3)+(res<<1)+(c^48);
        while(c=getchar(),c>47);
}
template<class T>inline void Max(T &a,T b){
    if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b){
    if(b<a)a=b;
}
inline void mod_add(int &a,int b){
    if((a+=b)>=mod)a-=mod;
}
const int N=(int)5e4+5,M=N<<1;
int tot_edge,head[N],tot;
bool vis[N];
ll _xor[N],arr[M<<1];
struct Edge{
	int to,nxt;
	ll cost;
	Edge(){}
	Edge(int to,int nxt,ll cost):to(to),nxt(nxt),cost(cost){}
}edge[M<<1];
inline void add_edge(int u,int v,ll c){
	edge[tot_edge]=Edge(v,head[u],c);
	head[u]=tot_edge++;
}
void dfs(int cur){
	vis[cur]=true;
	for(int i=head[cur];i;i=edge[i].nxt){
		int to=edge[i].to;
		if(vis[to])arr[tot++]=_xor[cur]^_xor[to]^edge[i].cost;
		else{
			_xor[to]=_xor[cur]^edge[i].cost;
			dfs(to);
		}
	}
}
void Gauss(){
	int ptr=0;
	for(ll mask=1ll<<60;mask;mask>>=1){
		int i;
		for(i=ptr;i<tot;++i)
			if(arr[i]&mask)
				break;
		if(i==tot)continue;
		swap(arr[ptr],arr[i]);
		for(int i=0;i<tot;++i)
			if(i!=ptr&&(arr[i]&mask))
				arr[i]^=arr[ptr];
		++ptr;
	}
}
int main(){
	int n,m;
	ll c;
	rd(n);rd(m);
	for(int u,v;m--;){
		rd(u);rd(v);rd(c);
		add_edge(u,v,c);
		add_edge(v,u,c);
	}
	dfs(1);
	Gauss();
	ll ans=_xor[n];
	for(int i=0;arr[i];++i)
		Max(ans,ans^arr[i]);
	printf("%lld\n",ans);
	return 0;
}
/*
	
	Jul.16.16

	Tags:math,xor
	Submissions:2

	Memory 7596kb
	Time 616ms
	Code Length 2333B

*/
