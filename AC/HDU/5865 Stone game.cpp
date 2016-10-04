#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define y1 jfskav
#define pb push_back
#define lson (k<<1)
#define rson (k<<1|1)
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
#define rep(i,s,t) for(register int i=s,_t=t;i<_t;++i)
#define per(i,s,t) for(register int i=t-1,_s=s;i>=_s;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int mod=3,inf=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
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
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
inline void mod_minus(int &a,int b){
	if((a-=b)<0)a+=mod;
}


const int N=(int)5e3+5,M=(int)1e5+5,MAX_K=305,LG=14,HASH=(int)1e7;

int n,m,K,tot_edge,head[N],SG[N],pos[MAX_K],num[LG],tmp[LG],cnt[HASH],arr[M];
bool mark[N];
pii edge[M];

void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
void calc_SG(int cur){
	if(~SG[cur])return;

	for(int i=head[cur];~i;i=edge[i].se)
		calc_SG(edge[i].fi);

	for(int i=head[cur];~i;i=edge[i].se)
		mark[SG[edge[i].fi]]=true;

	for(SG[cur]=0;mark[SG[cur]];++SG[cur]);

	for(int i=head[cur];~i;i=edge[i].se)
		mark[SG[edge[i].fi]]=false;
}
bool check(){
	rep(i,0,LG)if(num[i])return false;
	return true;
}
int Hash(){
	int res=0;
	for(int i=0,pw=1;i<LG;++i,pw*=mod)res+=tmp[i]*pw;
	return res;
}

void solve(){
	rd(m),rd(K);
	tot_edge=0;
	memset(head,-1,n+1<<2);
	memset(SG,-1,n+1<<2);
	for(int u,v;m--;){
		rd(u),rd(v);
		add_edge(u,v);
	}
	rep(i,0,K)rd(pos[i]);
	rep(i,1,n+1)calc_SG(i);

	rep(i,0,LG){
		num[i]=0;
		rep(j,0,K)mod_add(num[i],SG[pos[j]]>>i&1);
	}

	int ans=0;
	cnt[0]=1;
	rep(i,0,K){
		int tot=0;
		for(int j=head[pos[i]];~j;j=edge[j].se){
			int to=edge[j].fi;
			// putchar('\n');//
			// debug(pos[i]),debug(to);//
			rep(k,0,LG){
				mod_minus(tmp[k]=0,SG[pos[i]]>>k&1);
				mod_add(tmp[k],SG[to]>>k&1);
				// debug(k),debug(tmp[k]);//
			}
			arr[tot++]=Hash();
			// putchar('\n');//
			rep(k,0,LG){
				if(tmp[k])tmp[k]=mod-tmp[k];
				mod_minus(tmp[k],num[k]);
				// debug(k),debug(tmp[k]);//
			}
			ans+=cnt[Hash()];
		}
		rep(j,0,tot)++cnt[arr[j]];
	}
	rep(i,0,K)for(int j=head[pos[i]];~j;j=edge[j].se){
		int to=edge[j].fi;
		rep(k,0,LG){
			mod_minus(tmp[k]=0,SG[pos[i]]>>k&1);
			mod_add(tmp[k],SG[to]>>k&1);
		}
		cnt[Hash()]=0;
	}
	ptn(ans);
}

int main(){
	// freopen("1009.in","r",stdin);//
	// freopen("data.out","w",stdout);//
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	Aug.19.16

	Tags:game theory
	Submissions:2

	Exe.Time 577MS
	Exe.Memory 2496K
	Code Len. 3527B

*/
