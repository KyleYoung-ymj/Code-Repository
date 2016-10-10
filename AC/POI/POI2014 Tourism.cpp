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
const int inf=0x7fffffff,infty=(int)2e9,mod=(int)1e9+7,dxy[]={-1,0,1,0,-1};
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


const int N=(int)2e4+5,M=(int)25e3+5,DEP=11,POW=(int)6e4;

int tot_edge,head[N],cost[N],dep[N],arr[DEP],pow3[DEP],dp[DEP][POW];
bool vis[N];
pii edge[M<<1];

void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}

void init(){
	pow3[0]=1;
	rep(i,1,DEP)pow3[i]=pow3[i-1]*3;
}

void dfs(int u){
	vis[u]=true;
	int dep=::dep[u];
	if(!dep)dp[0][0]=cost[u],dp[0][1]=infty,dp[0][2]=0;
	else{
		rep(i,0,pow3[dep+1])dp[dep][i]=infty;
		int tot=0;
		for(int i=head[u];~i;i=edge[i].se){
			int v=edge[i].fi;
			if(vis[v]&&::dep[v]<::dep[u])arr[tot++]=::dep[v];
		}
		rep(mask,0,pow3[dep]){
			int mask_selected=mask,mask_not_selected=mask+(pow3[dep]<<1);
			bool flag=false;
			rep(i,0,tot){
				int num=mask/pow3[arr[i]]%3;
				if(num==2)mask_selected-=pow3[arr[i]];
				else if(!num&&!flag)flag=true,mask_not_selected-=pow3[dep];
			}
			Min(dp[dep][mask_selected],dp[dep-1][mask]+cost[u]);
			Min(dp[dep][mask_not_selected],dp[dep-1][mask]);
		}
	}
	for(int i=head[u];~i;i=edge[i].se){
		int v=edge[i].fi;
		if(vis[v])continue;
		::dep[v]=::dep[u]+1;
		dfs(v);
		rep(mask,0,pow3[dep+1])dp[dep][mask]=min(dp[dep+1][mask],dp[dep+1][mask+pow3[dep+1]]);
	}
}

int main(){
	int n,m;
	rd(n),rd(m);
	rep(i,1,n+1){
		rd(cost[i]);
		head[i]=-1;
	}
	for(int u,v;m--;){
		rd(u),rd(v);
		if(u!=v)add_edge(u,v),add_edge(v,u);
	}
	init();
	int ans=0;
	rep(i,1,n+1)if(!vis[i]){
		dfs(i);
		ans+=min(dp[0][0],dp[0][1]);
	}
	ptn(ans);
	return 0;
}

/*
	
	Oct.10.16
	
	Tags:graph,dfs,tree,dp
	Submissions:1
	
	Memory 4924KB
	Time 2016MS
	Code Length 3466B
	
*/

