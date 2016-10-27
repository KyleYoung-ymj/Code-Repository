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


const int M=(int)1e6+5;

int n,tot;
char str[M];
pii itv[3*M];

void consider(int L,int R)
{
	if(L<=R)itv[tot++]=pii(L,R);
	else
	{
		itv[tot++]=pii(0,R);
		itv[tot++]=pii(L,n-1);
	}
}

int main()
{
	int m,a,b,p;
	rd(n),rd(a),rd(b),rd(p),rd(m);
	scanf("%s",str);
	for(int i=0,L,R,val;i<m;++i)
	{
		if(str[i]=='1')L=0,R=p-1;
		else L=p,R=n-1;
		L=((L-(ll)i*a)%n+n)%n;
		R=((R-(ll)i*a)%n+n)%n;
		consider(L,R);
		if(i<m-1)
		{
			val=((ll)(n-1-i)*a+b)%n;
			itv[tot++]=pii(val,val);
		}
	}
	sort(itv,itv+tot);
	int ans=0;
	for(int i=0,j,mx;i<tot;i=j+1)
	{
		for(j=i,mx=itv[i].se;j<tot-1&&itv[j+1].fi<=mx+1;)Max(mx,itv[++j].se);
		ans+=mx-itv[i].fi+1;
	}
	ptn(n-ans);
	return 0;
}

/*
	
	Oct.27.16
	
	Tags:math
	Submissions:2
	
	Memory 26120KB
	Time 1072ms
	Code Length 2722B
	
*/

