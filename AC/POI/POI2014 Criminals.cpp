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

int dat[N],A[N],B[N],pre[N],nxt[N],pos[N],dp[N],ans[N],lst[N],tar[N];
pii itv[N];

int main(){
	int n,K,a,b;
	rd(n),rd(K);
	rep(i,1,n+1){
		rd(dat[i]);
		lst[dat[i]]=i;
	}
	rd(a),rd(b);
	rep(i,0,a){
		rd(A[i]);
		if(i)pre[A[i]]=A[i-1];
	}
	rep(i,0,b){
		rd(B[i]);
		if(i)nxt[B[i]]=B[i-1];
	}
	int tot=0;
	rep(i,1,n+1){
		if(dat[i]==A[a-1])tar[tot++]=i;
		
		if(dat[i]==A[0])dp[i]=i;
		else dp[i]=dp[pos[pre[dat[i]]]];
		
		pos[dat[i]]=i;
	}
	rep(i,1,K+1)pos[i]=0;
	per(i,1,n+1){
		int tmp;
		if(dat[i]==B[b-1])tmp=dp[i];
		
		if(dat[i]==B[0])dp[i]=i;
		else dp[i]=dp[pos[nxt[dat[i]]]];
		
		if(dat[i]==B[b-1])itv[i]=pii(tmp,dp[i]);
		
		pos[dat[i]]=i;
	}
	if(!tot)return puts("0");
	int cnt=0;
	for(int i=0,j=0,mx=0;i<tot;++i){
		int L=itv[tar[i]].fi,R=itv[tar[i]].se;
		if(!(L&&L<=tar[i]&&R<=n&&R>=tar[i]))continue;
		while(j<L-1)Max(mx,lst[dat[++j]]);
		if(mx>R)ans[cnt++]=tar[i];
	}
	ptn(cnt);
	rep(i,0,cnt)pt(ans[i]),putchar(' ');
	return 0;
}

/*
	
	Oct.07.16
	
	Tags:implementation
	Submissions:6
	
	Memory 48576KB
	Time 340MS
	Code Length 2913B
	
*/

