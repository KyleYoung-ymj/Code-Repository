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
#define lowbit(x) ((x)&(-x))
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define debug(x) cout<<#x<<"="<<(x)<<endl
#define rep(i,s,t) for(register int i=(s),_t=(t);i<_t;++i)
#define per(i,s,t) for(register int i=(t)-1,_s=(s);i>=_s;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int mod=(int)1e6+3,inf=0x7fffffff,dx[]={-1,0,1,0,-1};
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
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
inline void mod_minus(int &a,int b){
	if((a-=b)<0)a+=mod;
}
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)res=(ll)res*a%mod;
	return res;
}
inline int calc_inv(int x){
	return fast_mod_pow(x,mod-2);
}

const int N=(int)1e6+5;

int pw[N];

void init(){
	pw[0]=1;
	rep(i,1,N)if((pw[i]=pw[i-1]<<1)>=mod)pw[i]-=mod;
}
void solve(){
	int a,b;
	rd(a),rd(b);
	if(!a||!b){
		puts("0");
		return;
	}
	int n=a+b,m=b,
		cnt=0,
		ans=0;
	for(int k=m;;){
		++cnt;
		mod_add(ans,pw[gcd(k,n)]);
		if(!k)break;
		if((k+=m)>=n)k-=n;
	}
	ans=(ll)ans*calc_inv(cnt)%mod;
	ans=(pw[n]-ans)%mod;
	if(ans<0)ans+=mod;
	ptn(ans);
}

int main(){
	int cas;
	init();
	for(rd(cas);cas--;)solve();
	return 0;
}
/*
	
	Aug.20.16

	Tags:Polya
	Submissions:3

	TIME 0.88
	MEM 7.2M

*/
