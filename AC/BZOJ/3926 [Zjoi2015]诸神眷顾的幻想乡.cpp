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


const int N=(int)1e5+5,L=21;

int C,col[N],tot_edge,head[N],deg[N];
pii edge[N<<1];

void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}

struct Suffix_Automaton{
	static const int NODE=N*L<<1,MAX_C=10;
	int allc,par[NODE],len[NODE],trans[NODE][MAX_C];
	int NewNode(){
		int ret=++allc;
		memset(trans[ret],0,C<<2);
		return ret;
	}
	void init(){
		allc=0;
		NewNode();
		par[1]=len[1]=0;
	}
	int extend(int c,int p){
		if(trans[p][c]){
			int q=trans[p][c];
			if(len[q]>len[p]+1){
				int nq=++allc;
				par[nq]=par[q];
				len[nq]=len[p]+1;
				memcpy(trans[nq],trans[q],C<<2);
				par[q]=nq;
				for(trans[p][c]=nq,p=par[p];trans[p][c]==q;p=par[p])trans[p][c]=nq;
				return nq;
			}
			return q;
		}
		int np=NewNode();
		len[np]=len[p]+1;
		for(;!trans[p][c];p=par[p])trans[p][c]=np;
		if(!p)par[np]=1;
		else{
			int q=trans[p][c];
			if(len[q]==len[p]+1)par[np]=q;
			else{
				int nq=++allc;
				par[nq]=par[q];
				len[nq]=len[p]+1;
				memcpy(trans[nq],trans[q],C<<2);
				par[np]=par[q]=nq;
				for(trans[p][c]=nq,p=par[p];trans[p][c]==q;p=par[p])trans[p][c]=nq;
			}
		}
		return np;
	}
	ll solve(){
		ll ans=0;
		rep(i,2,allc+1)ans+=len[i]-len[par[i]];
		return ans;
	}
}SAM;

void dfs(int cur,int par,int lst){
	int np=SAM.extend(col[cur],lst);
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son!=par)dfs(son,cur,np);
	}
}

int main(){
	int n;
	rd(n),rd(C);
	rep(i,1,n+1){
		rd(col[i]);
		head[i]=-1;
	}
	for(int i=1,u,v;i<n;++i){
		rd(u),rd(v);
		add_edge(u,v);
		add_edge(v,u);
		++deg[u],++deg[v];
	}
	SAM.init();
	rep(i,1,n+1)if(deg[i]==1)dfs(i,0,1);
	ptn(SAM.solve());
	return 0;
}

/*
	
	Sept.13.16

	Tags:tree,SAM
	Submissions:2

	Memory 208648kb
	Time 2668ms
	Code Length 3997B

*/
