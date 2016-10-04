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
const int N=(int)1e6+5;
int val[N],tot_edge,head[N],par[N];
ll dp[2][N];
pii edge[N<<1],loop[N];
inline void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
int get_root(int x){
	return par[x]==x?x:par[x]=get_root(par[x]);
}
inline bool same(int u,int v){
	return get_root(u)==get_root(v);
}
void unite(int u,int v){
	u=get_root(u);
	v=get_root(v);
	par[u]=v;
}
void DP(int cur,int par=0){
	dp[0][cur]=0;
	dp[1][cur]=val[cur];
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==par)continue;
		DP(son,cur);
		dp[0][cur]+=max(dp[0][son],dp[1][son]);
		dp[1][cur]+=dp[0][son];
	}
}
int main(){
	int n,tot_loop=0;
	rd(n);
	for(int i=1;i<=n;++i)
		head[par[i]=i]=-1;
	for(int i=1,tar;i<=n;++i){
		rd(val[i]);rd(tar);
		if(same(i,tar))loop[tot_loop++]=pii(i,tar);
		else{
			unite(i,tar);
			add_edge(i,tar);
			add_edge(tar,i);
		}
	}
	ll ans=0;
	for(int i=0;i<tot_loop;++i){
		DP(loop[i].fi);
		ll tmp=dp[0][loop[i].fi];
		DP(loop[i].se);
		ans+=max(tmp,dp[0][loop[i].se]);
	}
	printf("%lld\n",ans);
	return 0;
}
/*
	
	Jul.16.16

	Tags:dp
	Submissions:1

	Memory 52184kb
	Time 2008ms
	Code Length 2325B

*/
