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
#define y0 vjfuyg
#define y1 jfskav
#define pb push_back
#define lson (k<<1)
#define rson (k<<1|1)
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
const db pi=acos(-1),eps=1e-6;
template<class T>void rd(T &x)
{
	x=0;
	char c;
	while(c=getchar(),c<48);
	do x=x*10+(c^48);
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
template<class T>T gcd(T a,T b)
{
	return b?gcd(b,a%b):a;
}
inline void mod_add(int &a,int b,int m=mod)
{
	if((a+=b)>=m)a-=m;
}
inline void mod_minus(int &a,int b,int m=mod)
{
	if((a-=b)<0)a+=m;
}
int mod_pow(int a,int b,int m=mod)
{
	int res=m==1?0:1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}


const int N=1005;

struct Bigint
{
	static const int BASE=(int)1e4,LEN=(int)1e3+5;
	int len,num[LEN];
	Bigint()
	{
		len=1;
		memset(num,0,sizeof num);
	}
	inline void operator =(int rhs)
	{
		num[0]=rhs;
	}
	Bigint operator *(int rhs)const
	{
		Bigint res;
		res.len=len;
		rep(i,0,res.len)
		{
			res.num[i]+=num[i]*rhs;
			if(res.num[i]>=BASE)
			{
				res.num[i+1]+=res.num[i]/BASE;
				res.num[i]%=BASE;
			}
		}
		if(res.num[res.len])++res.len;
		return res;
	}
	inline void operator *=(int rhs)
	{
		*this=*this*rhs;
	}
	Bigint operator /(int rhs)const
	{
		Bigint res;
		res.len=len;
		int pre=0;
		per(i,0,len)
		{
			if(pre)pre*=BASE;
			res.num[i]=(pre+=num[i])/rhs;
			pre-=res.num[i]*rhs;
		}
		if(res.len>1&&!res.num[res.len-1])--res.len;
		return res;
	}
	bool operator >(const Bigint &rhs)const
	{
		if(len!=rhs.len)return len>rhs.len;
		per(i,0,len)if(num[i]!=rhs.num[i])return num[i]>rhs.num[i];
		return false;
	}
	void print()
	{
		pt(num[len-1]);
		per(i,0,len-1)printf("%04d",num[i]);
		putchar('\n');
	}
};

pii dat[N];

bool cmp(const pii &A,const pii &B)
{
	return (ll)A.fi*A.se<(ll)B.fi*B.se;
}

int main()
{
	int n,a,b;
	rd(n),rd(a),rd(b);
	rep(i,0,n)rd(dat[i].fi),rd(dat[i].se);
	sort(dat,dat+n,cmp);
	Bigint prod,ans;
	prod=a,ans=0;
	rep(i,0,n)
	{
		Max(ans,prod/dat[i].se);
		prod*=dat[i].fi;
	}
	ans.print();
	return 0;
}

/*
	
	Oct.31.16
	
	Tags:greedy,high-precision
	Submissions:4
	
	Memory 804K
	Time 31MS
	Code Length 3.22K
	
*/

