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


const int N=(int)1e6+5;

int tot,arr[N],num[N],cnt[N];
ll sum[N];
char str[5];

struct Ope
{
	bool type;
	int a,b;
	void input()
	{
		scanf("%s",str);
		type=str[0]=='Z';
		rd(a),rd(b);
	}
}
ope[N];

template<class T>inline void add(T *bit,int x,int val)
{
	for(;x<=tot;x+=lowbit(x))bit[x]+=val;
}

template<class T>T query(T *bit,int x)
{
	T res=0;
	for(;x;x-=lowbit(x))res+=bit[x];
	return res;
}

int main()
{
	int n,m;
	rd(n),rd(m);
	num[tot++]=0;
	rep(i,0,m)
	{
		ope[i].input();
		num[tot++]=ope[i].b;
	}
	sort(num,num+tot);
	tot=unique(num,num+tot)-num;
	rep(i,1,n+1)
	{
		arr[i]=1;
		add(cnt,tot,1);
	}
	rep(i,0,m)
	{
		int a=ope[i].a,b=lower_bound(num,num+tot,ope[i].b)-num+1;
		if(ope[i].type)
		{
			int K=query(cnt,tot+1-b);
			ll rem=query(sum,b-1);
			puts(rem>=(ll)num[b-1]*(a-K)?"TAK":"NIE");
		}
		else
		{
			add(cnt,tot+1-arr[a],-1);
			add(sum,arr[a],-num[arr[a]-1]);
			arr[a]=b;
			add(cnt,tot+1-arr[a],1);
			add(sum,arr[a],num[arr[a]-1]);
		}
	}
	return 0;
}

/*
	
	Nov.01.16
	
	Tags:data structure
	Submissions:1
	
	Memory 32956KB
	Time 1080MS
	Code Length 2937B
	
*/

