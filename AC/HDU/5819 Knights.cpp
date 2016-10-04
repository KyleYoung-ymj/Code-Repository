#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <string>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define y1 kjfasiv
#define pb push_back
#define lson (k<<1)
#define rson (k<<1|1)
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
#define Debug(x) cout<<endl<<#x<<"="<<x<<"!!!!!"<<endl<<endl
#define rep(i,s,t) for(int i=s,_t=t;i<t;++i)
#define per(i,s,t) for(int i=t-1,_s=s;i>=_s;--i)
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
typedef complex<db> Com;
const int mod=(int)1e9+7,inf=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const ll INF=1ll<<60;
const db pi=acos(-1.0),eps=1e-8;
template<class T>void rd(T &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
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
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}

const int N=(int)1e3+5;
int p,pow_p[N],dp[2][N];
bool dir[N];
inline int inv(int x){
	return fast_mod_pow(x,mod-2);
}
inline void init(){
	p=inv(2);
	pow_p[0]=1;
	rep(i,1,N)pow_p[i]=1ll*pow_p[i-1]*p%mod;
}
int solve(){
	int n;
	rd(n);
	rep(i,1,n+1)rd(dir[i]);
	bool pre=0,cur=1;
	dp[pre][1]=1;
	rep(i,2,n){
		if(dir[i])rep(j,1,i+1)dp[cur][j]=dp[pre][j-1];
		else{
			dp[cur][i]=0;
			per(j,1,i)dp[cur][j]=1ll*p*(dp[cur][j+1]+dp[pre][j])%mod;
			rep(j,1,i)mod_add(dp[cur][1],1ll*dp[pre][j]*pow_p[j]%mod);
		}
		pre^=1,cur^=1;
	}
	int ans=0;
	rep(i,1,n)ans=(ans+1ll*dp[pre][i]*pow_p[i])%mod;
	return ans;
}
int main(){
	int cas;
	init();
	rd(cas);
	rep(i,1,cas+1)printf("Case #%d: %d\n",i,solve());
	return 0;
}
/*
	
	Aug.10.16

	Tags:dp,probability
	Submissions:2

	Exe.Time 62MS
	Exe.Memory 1576K
	Code Len. 2445B

*/
