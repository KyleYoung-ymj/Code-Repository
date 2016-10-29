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


const int N=205,M=(int)1e4+5;

bool dp[M];
bitset<N> bs[M],tmp;
int val[N],ans[N];

int main()
{
	int n,m;
	rd(n),rd(m);
	dp[0]=true;
	for(int i=0;i<n;++i)
	{
		rd(val[i]);
		per(j,0,m-val[i]+1)if(dp[j])
		{
			tmp=bs[j];
			tmp.set(i);
			if(!dp[j+val[i]])
			{
				dp[j+val[i]]=true;
				bs[j+val[i]]=tmp;
			}
			else bs[j+val[i]]&=tmp;
		}
	}
	ptn(bs[m].count());
	int cnt=0;
	rep(i,0,n)if(bs[m][i])ans[cnt++]=i;
	rep(i,0,cnt)printf("%d%c",val[ans[i]]," \n"[i==cnt-1]);
	return 0;
}

/*
	
	Oct.29.16
	
	Tags:dp
	Submissions:1
	
	Memory 664KB
	Time 35ms
	Code Length 2009B
	
*/

