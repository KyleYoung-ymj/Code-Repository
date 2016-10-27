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


const int N=(int)1e6+5;

int n,arr[N];
bool dp[2][2][N],pre[2][2][N];

bool check(bool i,bool j,bool a,bool b)
{
	int cur,flip;
	cur=i?arr[n]>>1:arr[n];
	flip=a?arr[1]:arr[1]>>1;
	if(j)swap(cur,flip);
	if(cur<flip)return false;
	cur=j?arr[1]>>1:arr[1];
	flip=b?arr[2]:arr[2]>>1;
	if(a)swap(cur,flip);
	return cur>=flip;
}

void rec_print(bool a,bool b,int id)
{
	if(id>1)rec_print(pre[a][b][id],a,id-1);
	if(id==n)ptn(b?1:n);
	else pt(b?id+1:id),putchar(' ');
}

bool solve(bool a,bool b)
{
	memset(dp,false,N<<2);
	dp[a][b][2]=true;
	rep(i,2,n)rep(j,0,2)rep(k,0,2)if(dp[j][k][i])rep(t,0,2)if(!dp[k][t][i+1])
	{
		// consider the i-th people
		int cur,flip;
		cur=j?arr[i]>>1:arr[i];
		flip=t?arr[i+1]:arr[i+1]>>1;
		if(k)swap(cur,flip);
		if(cur>=flip)
		{
			dp[k][t][i+1]=true;
			pre[k][t][i+1]=j;
		}
	}
	rep(i,0,2)rep(j,0,2)if(dp[i][j][n]&&check(i,j,a,b))
	{
		rec_print(i,j,n);
		return true;
	}
	return false;
}

int main()
{
	rd(n);
	rep(i,1,n+1)
	{
		rd(arr[i]);
		arr[i]<<=1;
	}
	rep(i,0,2)rep(j,0,2)if(solve(i,j))return 0;
	return puts("NIE");
}

/*
	
	Oct.26.16
	
	Tags:dp
	Submissions:1
	
	Memory 44548KB
	Time 296MS
	Code Length 3153B
	
*/

