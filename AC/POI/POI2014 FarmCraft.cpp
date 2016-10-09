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


const int N=(int)5e5+5;

int n,tot_edge,head[N],par[N],sz[N],val[N],dp[N];
pii edge[N<<1],arr[N];

void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}

inline bool cmp(const pii &a,const pii &b){
	return max(a.fi,a.se+b.fi)<max(b.fi,b.se+a.fi);
}

void DP(int u){
	dp[u]=u>1?val[u]:(n-1<<1)+val[u];
	sz[u]=1;
	for(int i=head[u];~i;i=edge[i].se){
		int v=edge[i].fi;
		if(v==par[u])continue;
		par[v]=u;
		DP(v);
		sz[u]+=sz[v];
	}
	int tot=0;
	for(int i=head[u];~i;i=edge[i].se){
		int v=edge[i].fi;
		if(v==par[u])continue;
		arr[tot++]=pii(dp[v],sz[v]<<1);
	}
	if(!tot)return;
	sort(arr,arr+tot,cmp);
	for(int i=0,sum=1;i<tot;++i){
		Max(dp[u],sum+arr[i].fi);
		sum+=arr[i].se;
	}
}

int main(){
	rd(n);
	rep(i,1,n+1){
		rd(val[i]);
		head[i]=-1;
	}
	for(int i=1,u,v;i<n;++i){
		rd(u),rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	DP(1);
	ptn(dp[1]);
	return 0;
}

/*
	
	Oct.07.16
	
	Tags:dp,greedy
	Submissions:2
	
	Memory 45452KB
	Time 488MS
	Code Length 2829B
	
*/

