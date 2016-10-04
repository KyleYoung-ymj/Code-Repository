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


const int N=405;

int n,val[N][N],lx[N],ly[N],matchx[N],matchy[N],slack[N];
bool usedx[N],usedy[N];

bool Hungary(int u,bool mark){
	usedx[u]=true;
	rep(v,0,n)if(!usedy[v]){
		int delta=lx[u]+ly[v]-val[u][v];
		if(delta)Min(slack[v],delta);
		else{
			usedy[v]=true;
			if(matchy[v]==-1||Hungary(matchy[v],mark)){
				if(mark)matchy[v]=u;
				return true;
			}
		}
	}
	return false;
}
bool adjust(){
	int delta=inf;
	rep(v,0,n)if(!usedy[v])Min(delta,slack[v]);
	rep(i,0,n){
		if(usedx[i])lx[i]-=delta;
		if(usedy[i])ly[i]+=delta;
		else slack[i]-=delta;
	}
	rep(v,0,n)if(!usedy[v]&&!slack[v]){
		usedy[v]=true;
		if(matchy[v]==-1||Hungary(matchy[v],false))return true;
	}
	return false;
}
void KM(int _n){
	rep(i,0,n){
		matchy[i]=-1;
		rep(j,0,n)Max(lx[i],val[i][j]);
	}
	rep(u,0,n){
		rep(i,0,n){
			slack[i]=inf;
			usedx[i]=usedy[i]=false;
		}
		if(Hungary(u,true))continue;
		while(!adjust());
		rep(i,0,n)usedx[i]=usedy[i]=false;
		Hungary(u,true);
	}
	ll ans=0;
	rep(v,0,n){
		ans+=val[matchy[v]][v];
		matchx[matchy[v]]=v;
	}
	ptn(ans);
	rep(u,0,_n){
		if(!val[u][matchx[u]])matchx[u]=-1;
		pt(matchx[u]+1);
		putchar(" \n"[u==_n-1]);
	}
}
int main(){
	int n,m,e;
	rd(n),rd(m),rd(e);
	::n=max(n,m),m=e;
	for(int u,v,c;m--;)rd(u),rd(v),rd(val[u-1][v-1]);
	KM(n);
	return 0;
}

/*
	
	Sept.25.16

	Memory 2342ms
	Time 1780kb
	Code Length 3.2kb

*/
