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


const int N=55,M=(int)4e3+5;

int arr[M],dp[N][N][M],val[N][N][M],opt[N][N][M],cnt[N][M],ans[N];

struct Unit
{
	int L,R,lim;
	inline void Rd()
	{
		rd(L),rd(R),rd(lim);
	}
}info[M];

inline void consider(int tar)
{
	rep(i,info[tar].L,info[tar].R+1)++cnt[i][info[tar].lim];
}

void rec(int i,int j,int k)
{
	if(i>j)return;
	int opt=::opt[i][j][k],val=::val[i][j][k];
	assert(opt>=i&&opt<=j);
	ans[opt]=arr[val];
	rec(i,opt-1,val);
	rec(opt+1,j,val);
}

int main()
{
	
	int n,m;
	rd(n),rd(m);
	rep(i,0,m)
	{
		info[i].Rd();
		arr[i]=info[i].lim;
	}
	sort(arr,arr+m);
	int tot=unique(arr,arr+m)-arr;
	rep(i,0,m)info[i].lim=lower_bound(arr,arr+tot,info[i].lim)-arr;
	
	per(i,1,n+1)rep(j,i,n+1)
	{
		
		rep(pos,i,j+1)memset(cnt[pos],0,tot<<2);
		rep(k,0,m)if(info[k].L>=i&&info[k].R<=j)consider(k);
		rep(pos,i,j+1)per(k,0,tot-1)cnt[pos][k]+=cnt[pos][k+1];
		
		per(k,0,tot)
		{
			int &res=dp[i][j][k],&val=::val[i][j][k],&opt=::opt[i][j][k];
			if(k<tot-1)
			{
				res=dp[i][j][k+1];
				val=::val[i][j][k+1];
				opt=::opt[i][j][k+1];
			}
			else res=-1;
			rep(pos,i,j+1)
			{
				int value=arr[k]*cnt[pos][k]+dp[i][pos-1][k]+dp[pos+1][j][k];
				if(value>res)
				{
					res=value;
					val=k;
					opt=pos;
				}
			}
		}
		
	}
	
	ptn(dp[1][n][0]);
	rec(1,n,0);
	rep(i,1,n+1)pt(ans[i]),putchar(" \n"[i==n]);
	
	return 0;
}

/*
	
	Oct.28.16
	
	Tags:dp
	Submissions:1
	
	Memory 144600KB
	Time 1168ms
	Code Length 3406B
	
*/

