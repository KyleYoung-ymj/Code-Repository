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


const int N=(int)1e3+5;

int n,m,tot;
char A[N][N],B[N][N];
pii pos[N*N];

inline bool in(int x,int y)
{
	return x<n&&y<m;
}

bool check()
{
	rep(i,0,n)rep(j,0,m)if(A[i][j]=='x')return false;
	return true;
}

bool paint(int x,int y)
{
	rep(i,0,tot)
	{
		int dx=x+pos[i].fi,dy=y+pos[i].se;
		if(!in(dx,dy)||A[dx][dy]=='.')return false;
		A[dx][dy]='.';
	}
	return true;
}

bool solve()
{
	int a,b;
	rd(n),rd(m),rd(a),rd(b);
	rep(i,0,n)scanf("%s",A[i]);
	tot=0;
	pii mi(-1,-1);
	rep(i,0,a)
	{
		scanf("%s",B[i]);
		rep(j,0,b)if(B[i][j]=='x')
		{
			if(~mi.fi)pos[tot++]=pii(i-mi.fi,j-mi.se);
			else mi=pii(i,j);
		}
	}
	if(mi.fi==-1)return check();
	rep(i,0,n)rep(j,0,m)if(A[i][j]=='x'&&!paint(i,j))return false;
	return true;
}

int main()
{
	int cas;
	for(rd(cas);cas--;)puts(solve()?"TAK":"NIE");
	return 0;
}

/*
	
	Oct.26.16
	
	Tags:implementation
	Submissions:2
	
	Memory 11564KB
	Time 92ms
	Code Length 2903B
	
*/

