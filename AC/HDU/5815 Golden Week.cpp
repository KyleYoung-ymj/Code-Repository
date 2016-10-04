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
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
#define rep(i,s,t) for(int i=s,_t=t;i<_t;++i)
#define per(i,s,t) for(int i=t-1,_s=s;i>=_s;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int mod=(int)1e9+7,inf=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const ll INF=1ll<<60;
const db pi=acos(-1),eps=1e-6;
template<class T>void rd(T &x){
    x=0;
    char c;
    while(c=getchar(),c<48);
    do x=(x<<3)+(x<<1)+(c^48);
        while(c=getchar(),c>47);
}
template<class T>void rec_print(T x){
    if(!x)return;
    rec_print(x/10);
    putchar(x%10^48);
}
template<class T>void print(T x){
    if(!x)putchar('0');
    else rec_print(x);
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


const int N=(int)1e3+5;

int tot_edge,tot,head[N],arr[N],par[N],ans[N];
pii es[N],edge[N<<1];
veci vec[N];
ll dp[N][N],mx[N][N];

void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
void DP(int cur){
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==par[cur])continue;
		par[son]=cur;
		DP(son);
	}
	sort(vec[cur].begin(),vec[cur].end(),greater<int>());
	int ptr=0;
	per(i,0,tot){
		for(;ptr<(int)vec[cur].size()&&vec[cur][ptr]>=arr[i];++ptr);
		dp[cur][i]=1ll*arr[i]*ptr;
		for(int j=head[cur];~j;j=edge[j].se){
			int son=edge[j].fi;
			if(son==par[cur])continue;
			dp[cur][i]+=mx[son][i];
		}
		if(i==tot-1)mx[cur][i]=dp[cur][i];
		else mx[cur][i]=max(mx[cur][i+1],dp[cur][i]);
	}
}
void dfs(int cur,int sum){
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==par[cur])continue;
		rep(j,sum,tot)if(dp[son][j]==mx[son][sum]){
			ans[son]=arr[j]-arr[sum];
			dfs(son,j);
			break;
		}
	}
}

void solve(){
	int n,m;
	rd(n),rd(m);
	tot_edge=0;
	rep(i,1,n+1){
		head[i]=-1;
		vec[i].clear();
	}
	for(int i=1,u,v;i<n;++i){
		rd(u),rd(v);
		es[i]=pii(u,v);
		add_edge(u,v);
		add_edge(v,u);
	}
	tot=0;
	for(int tar,bud;m--;){
		rd(tar),rd(bud);
		arr[tot++]=bud;
		vec[tar].pb(bud);
	}
	arr[tot++]=0;
	sort(arr,arr+tot);
	tot=unique(arr,arr+tot)-arr;
	DP(1);
	print(dp[1][0]);
	putchar('\n');
	dfs(1,0);
	rep(i,1,n){
		if(es[i].fi==par[es[i].se])print(ans[es[i].se]);
		else print(ans[es[i].fi]);
		putchar(" \n"[i==n-1]);
	}
}

int main(){
	int cas;
	for(rd(cas);cas--;)solve();
	return 0;
}
/*
	
	Aug.12.16

	Tags:dp
	Submissions:1

	Exe.Time 327MS
	Exe.Memory 17572K
	Code Len. 3120B

*/
