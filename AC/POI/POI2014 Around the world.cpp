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


const int N=(int)1e6+5<<1;

int arr[N],pre[N],cnt[N];
ll sum[N];

int main()
{
	int n,m,mx=0;
	rd(n),rd(m);
	rep(i,1,n+1)
	{
		rd(arr[i]);
		Max(mx,arr[i]);
		sum[i]=sum[i-1]+arr[i];
		arr[i+n]=arr[i];
	}
	rep(i,n+1,(n<<1)+1)sum[i]=sum[i-1]+arr[i];
	for(ll lim;m--;)
	{
		rd(lim);
		if(lim<mx)
		{
			puts("NIE");
			continue;
		}
		rep(i,0,(n<<1)+1)pre[i]=i,cnt[i]=0;
		for(int i=n,j=0;;++i)
		{
			for(;sum[i]-sum[j]>lim;++j);
			cnt[i]=cnt[j]+1;
			if(i-(pre[i]=pre[j])>=n)
			{
				ptn(cnt[i]);
				break;
			}
		}
	}
	return 0;
}

/*
	
	Oct.19.16
	
	Tags:implementation
	
	Memory 40764KB
	Time 2288MS
	Code Length 2493B
	
*/
