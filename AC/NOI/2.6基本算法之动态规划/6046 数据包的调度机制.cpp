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
const int inf=0x7fffffff,mod=(int)1e9+7,dxy[]={-1,0,1,0,-1};
const ll INF=1ll<<60;
const db pi=acos(-1),eps=1e-6;
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
    int res=1;
    for(;b;b>>=1,a=(ll)a*a%m)
        if(b&1)res=(ll)res*a%m;
    return res;
}
inline int calc_inv(int x,int m=mod)
{
    return mod_pow(x,m-2);
}


const int N=105;

int cost[N],sum[N],dp[N][N];

int DP(int L,int R)
{
	if(L>R)return 0;
	int &res=dp[L][R];
	if(res==-1)
	{
		res=inf;
		rep(i,L,R+1)Min(res,DP(L,i-1)+DP(i+1,R)+(i-L)*(sum[R]-sum[i])+(R-L)*cost[i]);
	}
	return res;
}

void solve()
{
	int n;
	rd(n);
	rep(i,1,n+1)
	{
		rd(cost[i]);
		sum[i]=sum[i-1]+cost[i];
	}
	memset(dp,-1,sizeof dp);
	ptn(DP(1,n));
}

int main()
{
	int cas;
	for(rd(cas);cas--;)solve();
	return 0;
}

/*
	
	Oct.28.16
	
	Tags:dp
	Submissions:4
	
	Memory 496KB
	Time 909ms
	Code Length 2094B
	
*/

