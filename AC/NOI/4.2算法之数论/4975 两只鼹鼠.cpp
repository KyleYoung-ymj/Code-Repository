#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define lson (k<<1)
#define rson (k<<1|1)
#define pb push_back
#define lowbit(x) ((x)&-(x))
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define debug(x) cout<<#x<<" = "<<(x)<<endl
#define rep(i,s,t) for(int i=(s),_t=(t);i<_t;++i)
#define per(i,s,t) for(int i=(t)-1,_s=(s);i>=_s;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int inf=0x7fffffff,mod=(int)1e9+7,dxy[]={-1,0,1,0,-1};
const ll INF=1ll<<60;
template<class T>void rd(T &x)
{
	x=0;
	char c;
	while(c=getchar(),c<48);
	do x=(x<<3)+(x<<1)+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_pt(T x)
{
	if(!x)return;
	rec_pt(x/10);
	putchar(x%10^48);
}
template<class T>void pt(T x)
{
	if(!x)putchar('0');
	else rec_pt(x);
}
template<class T>inline void ptn(T x)
{
	pt(x),putchar('\n');
}
template<class T>inline void Max(T &a,T b)
{
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b)
{
	if(b<a)a=b;
}
int mod_pow(int a,int b,int m=mod)
{
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%m)if(b&1)res=(ll)res*a%m;
	return res;
}
inline int calc_inv(int x,int m=mod)
{
	return mod_pow(x,m-2,m);
}

int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}

inline int lcm(int a,int b)
{
	return a/gcd(a,b)*b;
}

void extgcd(int a,int &x,int b,int &y)// ax+by=gcd(a,b)=1
{
	if(b)
	{
		extgcd(b,y,a%b,x);
		y-=a/b*x;
	}
	else
	{
		x=1;
		y=0;
	}
}

int solve(int a,int b,int c)// return the minimal x>=0 s.t. ax+by=c (a*b!=0)
{
	int d=gcd(a,b),x,y;
	if(c%d)return -1;
	a/=d,b/=d,c/=d;
	extgcd(a,x,b,y);
	if(b<0)b*=-1;
	x*=c;
	x%=b;
	if(x<0)x+=b;
	return x;
}

int main()
{
	int n,posa,posb,ta,tb,fa,fb;
	cin>>n>>posa>>posb>>ta>>tb>>fa>>fb;
	int x=solve(ta,-tb,fb-fa);
	if(!~x)
	{
		puts("no answer");
		return 0;
	}
	int T=fa+x*ta,m=lcm(ta,tb);
	int k=solve(m<<1,-n,posb-posa-(T<<1));
	if(!~k)puts("no answer");
	else ptn(T+k*m);
	return 0;
}

/*
	
	Oct.29.16
	
	Tags:math,number theory
	Submissions:2
	
	Memory 200KB
	Time 0ms
	Code Length 2319B
	
*/

