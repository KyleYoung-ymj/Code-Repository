#include <bits/stdc++.h>
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


const int N=(int)1e3+5;

char str[N];

struct Bigint
{
	static const int BASE=(int)1e4;
	int len,num[N];
	Bigint()
	{
		len=1;
		memset(num,0,sizeof num);
	}
	void input()
	{
		scanf("%s",str);
		len=0;
		for(int i=strlen(str);i>0;i-=4,++len)
			rep(j,max(0,i-4),i)num[len]=num[len]*10+(str[j]^48);
	}
	void output()
	{
		pt(num[len-1]);
		per(i,0,len-1)printf("%04d",num[i]);
		putchar('\n');
	}
	Bigint operator -(const Bigint &rhs)const
	{
		Bigint res=*this;
		rep(i,0,res.len)
		{
			res.num[i]-=rhs.num[i];
			if(res.num[i]<0)
			{
				--res.num[i+1];
				res.num[i]+=BASE;
			}
		}
		while(res.len>1&&!res.num[res.len-1])--res.len;
		return res;
	}
}
A,B;

int main()
{
	A.input(),B.input();
	(A-B).output();
	return 0;
}

/*
	
	Oct.31.16
	
	Tags:bigint
	Submissions:1
	
	Memory 200KB
	Time 0ms
	Code Length 2233B
	
*/

