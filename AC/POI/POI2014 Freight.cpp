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

int dat[N],que[N];
ll dp[N];

inline ll calc(int id){
	return dp[id-1]-(id<<1);
}

int main(){
	int n,m;
	rd(n),rd(m);
	rep(i,1,n+1){
		rd(dat[i]);
		if(i>1&&dat[i]<=dat[i-1])dat[i]=dat[i-1]+1;
	}
	
	// dp[i]=min{max(dp[j-1]+i-j,dat[i])-j}+i+2m, 1<=j<=i
	for(int i=1,j=1,head=0,tail=0;i<=n;++i){
		for(;j<i&&dp[j]-j-1<=dat[i]-i;++j);
		dp[i]=dat[i]-j;
		for(;head<tail&&que[head]<=j;++head);
		if(head<tail)Min(dp[i],calc(que[head])+i);
		dp[i]+=i+(m<<1);
		for(;head<tail&&calc(que[tail-1])>=calc(i);--tail);
		que[tail++]=i;
	}
	
	ptn(dp[n]);
	return 0;
}

/*
	
	Oct.09.16
	
	Tags:dp,monotonous queue
	Submissions:1
	
	Memory 17324KB
	Time 132MS
	Code Length 2450B
	
*/

