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


const int N=(int)1e5+5,M=(int)2e5+5;

int tot_edge,head[N],type,top,stk[M],in[N],out[N];
pii edge[M<<1];
bool mark[M];

void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}

inline int id(int x){
	return type==1?x>>1:x;
}

void dfs(int u){
	for(int &i=head[u];~i;){
		if(mark[id(i)])i=edge[i].se;
		else{
			mark[id(i)]=true;
			int tmp=i,v=edge[i].fi;
			i=edge[i].se;
			dfs(v);
			stk[top++]=type==1?(tmp&1?(-(tmp>>1))-1:(tmp>>1)+1):tmp+1;
		}
	}
}

int main(){
	rd(type);
	int n,m;
	rd(n),rd(m);
	memset(head,-1,n+1<<2);
	for(int i=0,u,v;i<m;++i){
		rd(u),rd(v);
		++out[u],++in[v];
		add_edge(u,v);
		if(type==1)add_edge(v,u);
	}
	rep(i,1,n+1)if((type==1&&in[i]+out[i]&1)||(type==2&&in[i]!=out[i])){
		puts("NO");
		return 0;
	}
	dfs(edge[0].fi);
	if(top<m){
		puts("NO");
		return 0;
	}
	puts("YES");
	per(i,0,top)printf("%d%c",stk[i]," \n"[!i]);
	return 0;
}

/*
	
	Oct.02.16
	
	Problem:UOJ #117
	
*/

