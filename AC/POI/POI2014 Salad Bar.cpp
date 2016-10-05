#include <bits/stdc++.h>
#define fi first
#define se second
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
template<class T>void rd(T &x){
	x=0;
	char c;
	while(c=getchar(),c<48);
	do x=(x<<3)+(x<<1)+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_pt(T x){
	if(!x)return;
	rec_pt(x/10);
	putchar(x%10^48);
}
template<class T>void pt(T x){
	if(!x)putchar('0');
	else rec_pt(x);
}
template<class T>inline void ptn(T x){
	pt(x),putchar('\n');
}
template<class T>inline void Max(T &a,T b){
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b){
	if(b<a)a=b;
}
template<class T>T gcd(T a,T b){
	return b?gcd(b,a%b):a;
}
inline void mod_add(int &a,int b,int m=mod){
	if((a+=b)>=m)a-=m;
}
inline void mod_minus(int &a,int b,int m=mod){
	if((a-=b)<0)a+=m;
}
int mod_pow(int a,int b,int m=mod){
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}
inline int calc_inv(int x,int m=mod){
	return mod_pow(x,m-2);
}


const int N=(int)1e6+5;

char str[N];
int n,sum[N],pos[N<<1],L[N],R[N],cnt[N],arr[N],bit[N];

inline void modify(int x){
	int val=x;
	for(;x<=n;x+=lowbit(x))Max(bit[x],val);
}
int query_mx(int x){
	int res=0;
	for(;x;x-=lowbit(x))Max(res,bit[x]);
	return res;
}

int main(){
	rd(n);
	scanf("%s",str+1);
	rep(i,1,n+1)sum[i]=sum[i-1]+(str[i]=str[i]=='p'?1:-1);
	rep(i,1,n+1){
		L[i]=pos[sum[i]+1+N]+1;
		pos[sum[i]+N]=i;
		++cnt[L[i]];
	}
	rep(i,0,N<<1)pos[i]=n+1;
	pos[sum[n]+N]=n;
	per(i,0,n){
		R[i+1]=pos[sum[i]-1+N]-1;
		pos[sum[i]+N]=i;
	}
	rep(i,2,n+1)cnt[i]+=cnt[i-1];
	rep(i,1,n+1)arr[--cnt[L[i]]]=i;
	int ans=0;
	for(int i=1,j=0;i<=n;++i){
		for(;j<n&&L[arr[j]]==i;++j)modify(arr[j]);
		Max(ans,query_mx(R[i])-i+1);
	}
	ptn(ans);
	return 0;
}
/*
	
	Oct.04.16
	
	Tags:data structure,bit
	Submissions:1
	
	Memory 33928KB
	Time 132MS
	Code Length 2714B
	
*/

