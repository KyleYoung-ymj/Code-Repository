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


const int N=125;

int tot_edge,head[N],match[N];
pii edge[N*N];
bool mark[N];

void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}

bool Hungary(int u){
	for(int i=head[u];~i;i=edge[i].se){
		int v=edge[i].fi;
		if(mark[v])continue;
		mark[v]=true;
		if(!match[v]||Hungary(match[v])){
			match[v]=u;
			return true;
		}
	}
	return false;
}

int bipartite_match(int n){
	int res=0;
	rep(u,1,n+1){
		memset(mark,false,n+1);
		res+=Hungary(u);
	}
	return res;
}

void solve(){
	int n,m;
	rd(n),rd(m);
	tot_edge=0;
	memset(head,-1,n+1<<2);
	memset(match,0,n+1<<2);
	for(int u,v;m--;){
		rd(u),rd(v);
		add_edge(u,v);
	}
	ptn(n-bipartite_match(n));
}

int main(){
	int cas;
	for(rd(cas);cas--;)solve();
	return 0;
}

/*
	
	Sept.26.16

	Tags:bipartite match
	Submissions:1

	Memory 780K
	Time 0MS
	Code Length 2564B

*/
