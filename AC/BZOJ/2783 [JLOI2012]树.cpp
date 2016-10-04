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
typedef vector<int> veci;
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
const int N=(int)1e5+5;
int K,tot_edge,head[N],val[N];
ll ans;
pii edge[N];
map<int,int>cnt;
inline void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
void dfs(int cur,int sum){
	if(sum>=K&&cnt.find(sum-K)!=cnt.end())
		ans+=cnt[sum-K];
	++cnt[sum];
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		dfs(son,sum+val[son]);
	}
	--cnt[sum];
}
int main(){
	int n;
	rd(n);rd(K);
	for(int i=1;i<=n;++i){
		head[i]=-1;
		rd(val[i]);
	}
	for(int i=1,u,v;i<n;++i){
		rd(u);rd(v);
		add_edge(u,v);
	}
	cnt[0]=1;
	dfs(1,val[1]);
	printf("%lld\n",ans);
	return 0;
}
/*
	
	Jul.18.16

	Tags:map
	Submissions:1

	Memory 7480kb
	Time 324ms
	Code Length 1837B

*/
