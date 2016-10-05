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
#pragma comment(linker, "/STACK:1024000000,1024000000")
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
 
int amt[N],in[N],out[N],tot_edge,head[N],first,pre[N],nxt[N],top,stk[N];
pii es[N];
 
struct Edge{
	int to,nxt;
	inline Edge(){}
	inline Edge(int to,int nxt):to(to),nxt(nxt){}
}edge[N];
 
void add_edge(int u,int v){
	edge[tot_edge]=Edge(v,head[u]);
	head[u]=tot_edge++;
}
 
void dfs(int u){
	for(int &i=head[u];~i;){
		int v=edge[i].to;
		i=edge[i].nxt;
		dfs(v);
		stk[top++]=v;
	}
}
 
void del(int x){
	if(x==first)first=nxt[x];
	nxt[pre[x]]=nxt[x];
	pre[nxt[x]]=pre[x];
}
 
int main(){
	int n,st,en;
	rd(n),rd(st),rd(en);
	first=1;
	rep(i,1,n+1){
		rd(amt[i]);
		in[i]=out[i]=amt[i];
		head[i]=-1;
		pre[i]=i-1;
		nxt[i]=i+1;
	}
	--in[st],--out[en];
	if(!in[st])del(st);
	 
	if(n==1){
		if(amt[1]==1)puts("1");
		else puts("0");
		return 0;
	}
	if(st==en&&amt[st]==1)return puts("0");
	 
	int lst=0,tot_es=0;
	rep(i,1,n+1){
		int tar=first;
		while(out[i]){
			if(tar==i){
				tar=nxt[tar];
				continue;
			}
			if(tar>n){
				lst=i;
				break;
			}
			es[tot_es++]=pii(i,tar);
			--out[i];
			if(!--in[tar]){
				del(tar);
				tar=nxt[tar];
			}
		}
	}
	if(lst){
		for(int i=0;i<tot_es&&out[lst];++i){
			int tar=es[i].se;
			if(es[i].fi==lst||tar==lst)continue;
			es[i].se=lst;
			es[tot_es++]=pii(lst,tar);
			--out[lst];
		}
		if(out[lst])return puts("0");
	}
	rep(i,0,tot_es)add_edge(es[i].fi,es[i].se);
	 
	dfs(st);
	pt(st),putchar(' ');
	per(i,1,top)pt(stk[i]),putchar(' ');
	rep(i,1,n+1){
		top=0;
		dfs(i);
		if(top){
			pt(i),putchar(' ');
			per(i,1,top)pt(stk[i]),putchar(' ');
		}
	}
	ptn(en);
	 
	return 0;
}

/*
	
	Oct.05.16
	
	Tags:Euler path,constructive algorithm
	Submissions:3
	
	Memory 91420KB
	Time 288MS
	Code Length 3631B
	
*/

