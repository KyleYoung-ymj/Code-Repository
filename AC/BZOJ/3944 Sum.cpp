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


const int M=(int)167e4,S=1305;

int n,pr[M],pr_pow[M],prime[M>>3];
ll phi[M],mu[M],memo_phi[S],memo_mu[S];
bool vis[S];

void sieve(){
	phi[1]=mu[1]=1;
	int tot_prime=0;
	rep(i,2,M){
		if(!pr[i])prime[tot_prime++]=pr_pow[i]=pr[i]=i;
		if(pr_pow[i]==i){
			phi[i]=i/pr[i]*(pr[i]-1);
			mu[i]=-(pr[i]==pr_pow[i]);
		}
		else{
			phi[i]=phi[pr_pow[i]]*phi[i/pr_pow[i]];
			mu[i]=mu[pr_pow[i]]*mu[i/pr_pow[i]];
		}
		for(int j=0,p,prod;j<tot_prime&&(p=prime[j])<=pr[i]&&(prod=i*p)<M;++j){
			pr[prod]=p;
			pr_pow[prod]=p==pr[i]?pr_pow[i]*p:p;
		}
	}
	rep(i,2,M){
		phi[i]+=phi[i-1];
		mu[i]+=mu[i-1];
	}
}

inline ll call_phi(int m){
	return m<M?phi[m]:memo_phi[n/m];
}
inline ll call_mu(int m){
	return m<M?mu[m]:memo_mu[n/m];
}

void solve(int m){
	if(m<M)return;
	int id=n/m;
	if(vis[id])return;
	vis[id]=true;
	memo_phi[id]=m*((ll)m+1)>>1;
	memo_mu[id]=1;
	for(ll i=2,last;i<=m;i=(ll)last+1){
		int val=m/i;
		last=m/val;
		if(val>=M)solve(val);
		memo_phi[id]-=(last-i+1)*call_phi(val);
		memo_mu[id]-=(last-i+1)*call_mu(val);
	}
}

int main(){
	int cas;
	for(sieve(),rd(cas);cas--;){
		rd(n);
		if(n<M){
			printf("%lld %lld\n",phi[n],mu[n]);
			continue;
		}
		memset(vis,false,S);
		solve(n);
		printf("%lld %lld\n",memo_phi[1],memo_mu[1]);
	}
	return 0;
}

/*
	
	Sept.19.16

	Tags:number theory
	Submissions:1

	Memory 41268kb
	Time 6776ms
	Code Length 3546B

*/
