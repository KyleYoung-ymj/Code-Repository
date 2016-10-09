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


const int N=(int)5e5+5,M=(N<<1)+(int)1e6+5;

int n,tot_edge_in,tot_edge_out,head_in[N],head_out[N],in[N],que[N],mx_in[N],mx_out[N];
pii edge_in[M],edge_out[M];

void add_edge(int u,int v){
	edge_out[tot_edge_out]=pii(v,head_out[u]);
	head_out[u]=tot_edge_out++;
	edge_in[tot_edge_in]=pii(u,head_in[v]);
	head_in[v]=tot_edge_in++;
}

struct Heap{
	priority_queue<int>p,q;
	inline void psh(int x){
		p.push(x);
	}
	inline bool is_empty(){
		return p.empty();
	}
	inline int tp(){
		return p.top();
	}
	inline void del(int x){
		for(q.push(x);!p.empty()&&!q.empty()&&p.top()==q.top();p.pop(),q.pop());
	}
}hp;

void topo_sort(){
	int L=0,R=0;
	rep(i,1,n+1)if(!in[i])que[R++]=i;
	while(L<R){
		int u=que[L++];
		for(int i=head_out[u];~i;i=edge_out[i].se){
			int v=edge_out[i].fi;
			if(!--in[v])que[R++]=v;
		}
	}
}

void DP(){
	rep(id,0,n){
		int u=que[id];
		for(int i=head_in[u];~i;i=edge_in[i].se){
			int v=edge_in[i].fi;
			Max(mx_in[u],mx_in[v]);
		}
		++mx_in[u];
	}
	per(id,0,n){
		int u=que[id];
		for(int i=head_out[u];~i;i=edge_out[i].se){
			int v=edge_out[i].fi;
			Max(mx_out[u],mx_out[v]);
		}
		++mx_out[u];
	}
}

int consider(int u,int pre){
	if(~pre)for(int i=head_out[pre];~i;i=edge_out[i].se){
		int v=edge_out[i].fi;
		hp.psh(mx_in[pre]+mx_out[v]+1);
	}
	for(int i=head_in[u];~i;i=edge_in[i].se){
		int v=edge_in[i].fi;
		hp.del(mx_in[v]+mx_out[u]+1);
	}
	return hp.is_empty()?0:hp.tp();
}

int main(){
	int m;
	rd(n),rd(m);
	memset(head_in,-1,n+2<<2);
	memset(head_out,-1,n+2<<2);
	rep(i,1,n+1)add_edge(0,i),add_edge(i,n+1);
	for(int u,v;m--;){
		rd(u),rd(v);
		add_edge(u,v);
		++in[v];
	}
	topo_sort();
	DP();
	int ans=inf,id;
	for(int i=head_out[0];~i;i=edge_out[i].se){
		int v=edge_out[i].fi;
		hp.psh(mx_out[v]+1);
	}
	rep(i,0,n){
		int res=consider(que[i],i?que[i-1]:-1);
		if(res<ans){
			ans=res;
			id=que[i];
		}
	}
	pt(id),putchar(' '),ptn(ans-2);
	return 0;
}

/*
	
	Oct.09.16
	
	Tags:graph,toposort,heap
	Submissions:3
	
	Memory 69260KB
	Time 4244MS
	Code Length 3966B
	
*/

