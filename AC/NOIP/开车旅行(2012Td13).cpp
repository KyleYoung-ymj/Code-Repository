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


typedef set<pii>::iterator ite;

const int N=(int)1e5+5,LG=18;

int n,dat[N];

struct Unit
{
	int pos;
	ll a,b;
	Unit(){}
	Unit(int pos,ll a,ll b):pos(pos),a(a),b(b){}
}
arr[2][LG][N];

set<pii> st;

bool check(int a,int b,int cur)// a is closer than b
{
	if(!~b)return true;
	int dist_a=abs(dat[a]-dat[cur]),dist_b=abs(dat[b]-dat[cur]);
	if(dist_a!=dist_b)return dist_a<dist_b;
	return dat[a]<dat[b];
}

void consider(int &tar1,int &tar2,int pos,int cur)
{
	if(check(pos,tar1,cur))
	{
		tar2=tar1;
		tar1=pos;
	}
	else if(check(pos,tar2,cur))tar2=pos;
}

void init()
{
	st.insert(pii(dat[n],n));
	per(i,1,n)
	{
		if(i==n-1)
		{
			ite it=st.begin();
			arr[1][0][i]=Unit((*it).se,0,abs(dat[i]-dat[(*it).se]));
		}
		else
		{
			ite it=st.upper_bound(pii(dat[i],0)),it_;
			bool flag=it!=st.begin();
			if(flag)it_=--it,++it;
			int tar1=-1,tar2=-1;
			if(it!=st.end())
			{
				consider(tar1,tar2,(*it).se,i);
				if(++it!=st.end())consider(tar1,tar2,(*it).se,i);
			}
			if(flag)
			{
				consider(tar1,tar2,(*it_).se,i);
				if(it_--!=st.begin())consider(tar1,tar2,(*it_).se,i);
			}
			arr[0][0][i]=Unit(tar2,abs(dat[i]-dat[tar2]),0);
			arr[1][0][i]=Unit(tar1,0,abs(dat[i]-dat[tar1]));
		}
		st.insert(pii(dat[i],i));
	}
	
	rep(i,1,LG)rep(k,0,2)rep(j,1,n+1)
	{
		int nxt=arr[k][i-1][j].pos;
		if(i==1)arr[k][i][j]=Unit(arr[k^1][i-1][nxt].pos,arr[k][i-1][j].a+arr[k^1][i-1][nxt].a,arr[k][i-1][j].b+arr[k^1][i-1][nxt].b);
		else arr[k][i][j]=Unit(arr[k][i-1][nxt].pos,arr[k][i-1][j].a+arr[k][i-1][nxt].a,arr[k][i-1][j].b+arr[k][i-1][nxt].b);
	}
	
}

pll solve(int s,int lim)
{
	if(!arr[0][0][s].pos||arr[0][0][s].a+arr[0][0][s].b>lim)return pll(0,0);
	ll sum0=0,sum1=0;
	sum0+=arr[0][0][s].a;
	sum1+=arr[0][0][s].b;
	s=arr[0][0][s].pos;
	per(i,0,LG)if(arr[1][i][s].pos&&sum0+sum1+arr[1][i][s].a+arr[1][i][s].b<=lim)
	{
		sum0+=arr[1][i][s].a;
		sum1+=arr[1][i][s].b;
		s=arr[1][i][s].pos;
	}
	return pll(sum0,sum1);
}

pll res[N];

bool equ(pii A,pii B)
{
	if(!A.se||!B.se)return !A.se&&!B.se;
	return (ll)A.fi*B.se==(ll)A.se*B.fi;
}

bool check2(int a,int b)// arr[a] is better than arr[b]
{
	if(equ(res[a],res[b]))return dat[a]>dat[b];
	return (ll)res[a].fi*res[b].se<(ll)res[a].se*res[b].fi;
}

void pre_solve()
{
	int lim;
	rd(lim);
	rep(i,1,n+1)res[i]=solve(i,lim);
	int ans=1;
	rep(i,2,n+1)if(check2(i,ans))ans=i;
	ptn(ans);
}

int main()
{
	rd(n);
	rep(i,1,n+1)scanf("%d",&dat[i]);
	init();
	pre_solve();
	int m;
	rd(m);
	for(int s,lim;m--;)
	{
		rd(s),rd(lim);
		pll ans=solve(s,lim);
		pt(ans.fi),putchar(' '),ptn(ans.se);
	}
	return 0;
}

/*
	
	Oct.31.16
	
	Tags:data structure,multiply
	Submissions:2
	
	Memory 90532K
	Time 531MS
	Code Length 4.43K
	
*/

