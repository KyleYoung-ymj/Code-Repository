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


const int N=(int)1e6+5,M=N<<1;

char str[N];
int sum[3][N],A[N],B[N],C[N],arr[N];

inline bool cmp(int a,int b)
{
	return A[a]<A[b];
}

struct Unit
{
	
	int mx[2],mi[2];
	
	inline Unit()
	{
		mx[0]=mx[1]=mi[0]=mi[1]=-1;
	}
	
	void update(int pos)
	{
		
		if(pos>mx[0])
		{
			if(~mx[0]&&C[mx[0]]!=C[pos])mx[1]=mx[0];
			mx[0]=pos;
		}
		else if(C[pos]!=C[mx[0]]&&pos>mx[1])mx[1]=pos;
		
		if(!~mi[0]||pos<mi[0])
		{
			if(~mi[0]&&C[mi[0]]!=C[pos])mi[1]=mi[0];
			mi[0]=pos;
		}
		else if(C[pos]!=C[mi[0]]&&(!~mi[1]||pos<mi[1]))mi[1]=pos;
		
	}
	
	int query(int pos)
	{
		int res=0;
		if(~mx[0]&&C[pos]!=C[mx[0]])Max(res,abs(pos-mx[0]));
		if(~mx[1]&&C[pos]!=C[mx[1]])Max(res,abs(pos-mx[1]));
		if(~mi[0]&&C[pos]!=C[mi[0]])Max(res,abs(pos-mi[0]));
		if(~mi[1]&&C[pos]!=C[mi[1]])Max(res,abs(pos-mi[1]));
		return res;
	}
	
}
bit[2][M];

inline void update(Unit *bit,int x,int pos)
{
	for(;x<M;x+=lowbit(x))bit[x].update(pos);
}

int query(Unit *bit,int x,int pos)
{
	int res=0;
	for(;x;x-=lowbit(x))Max(res,bit[x].query(pos));
	return res;
}

int main()
{
	int n,ans=1;
	rd(n);
	scanf("%s",str+1);
	for(int i=1,pre=1;i<=n;++i)
	{
		rep(j,0,3)sum[j][i]=sum[j][i-1];
		if(str[i]=='B')++sum[0][i];
		else if(str[i]=='C')++sum[1][i];
		else ++sum[2][i];
		if(str[i]!=str[i-1])pre=i;
		else Max(ans,i-pre+1);
		A[i]=sum[0][i]-sum[1][i]+N;
		B[i]=sum[1][i]-sum[2][i]+N;
		C[i]=sum[2][i]-sum[0][i]+N;
		arr[i]=i;
	}
	A[0]=B[0]=C[0]=N;
	sort(arr,arr+n+1,cmp);
	for(int i=0,j=0;i<=n;i=++j)
	{
		for(;j<n&&A[arr[j+1]]==A[arr[i]];++j);
		rep(k,i,j+1)
		{
			Max(ans,query(bit[0],B[arr[k]]-1,arr[k]));
			Max(ans,query(bit[1],M-B[arr[k]]-1,arr[k]));
		}
		rep(k,i,j+1)
		{
			update(bit[0],B[arr[k]],arr[k]);
			update(bit[1],M-B[arr[k]],arr[k]);
		}
	}
	ptn(ans);
	return 0;
}

/*
	
	Nov.01.16
	
	Tags:data structure
	Submissions:5
	
	Memory 92524KB
	Time 832MS
	Code Length 3815B
	
*/

