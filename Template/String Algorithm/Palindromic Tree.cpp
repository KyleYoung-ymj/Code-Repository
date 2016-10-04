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
int qpow(int a,int b,int m=mod){
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}
inline int calc_inv(int x,int m=mod){
	return qpow(x,m-2);
}


const int N=(int)3e5+5;

char str[N];

// Palindromic Tree
const int S=26;
int allc,lst,len[N],fail[N],trans[N][S],cnt[N];
void init(){
	fail[0]=lst=allc=1;
	len[1]=-1;
}
void extend(int n){
	int c=str[n]-'a';
	while(n-1-len[lst]<0||str[n]!=str[n-1-len[lst]])lst=fail[lst];
	if(!trans[lst][c]){
		++allc;
		len[allc]=len[lst]+2;
		int tmp=fail[lst];
		while(n-1-len[tmp]<0||str[n]!=str[n-1-len[tmp]])tmp=fail[tmp];
		fail[allc]=trans[tmp][c];
		trans[lst][c]=allc;
	}
	++cnt[lst=trans[lst][c]];
}
void cons(){
	init();
	rep(i,0,strlen(str))extend(i);
}
ll solve(){
	ll ans=0;
	per(i,2,allc+1){
		Max(ans,(ll)len[i]*cnt[i]);
		cnt[fail[i]]+=cnt[i];
	}
	return ans;
}
int main(){
	scanf("%s",str);
	cons();
	ptn(solve());
	return 0;
}

/*
	
	Sept.14.16

	Problem:BZOJ3676
	
*/
