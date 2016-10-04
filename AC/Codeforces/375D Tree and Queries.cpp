#include <cstdio>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<ll,ll> pll;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
const int N=(int)1e5+5;
int tot_edge,head[N],
	col[N],
	dfs_clock,pre[N],post[N],id[N],
	cnt[N],sum[N],
	S,ans[N];
pii edge[N<<1];
struct Query{
	int id,L,R,c;
	inline void Rd(){
		rd(c);
		L=pre[c];
		R=post[c];
		rd(c);
	}
	inline bool operator <(const Query &tmp)const{
		int a=L/S,b=tmp.L/S;
		if(a!=b)return a<b;
		return R<tmp.R;
	}
}query[N];
void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
void dfs(int cur,int par=0){
	id[pre[cur]=++dfs_clock]=cur;
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==par)continue;
		dfs(son,cur);
	}
	post[cur]=dfs_clock;
}
int main(){
	int n,m;
	rd(n);rd(m);
	for(int i=1;i<=n;++i){
		rd(col[i]);
		head[i]=-1;
	}
	for(int i=1,u,v;i<n;++i){
		rd(u);rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1);
	for(int i=0;i<m;++i){
		query[i].Rd();
		query[i].id=i;
	}
	S=(int)sqrt(n);
	if(!S)++S;
	sort(query,query+m);
	for(int i=0,L=1,R=0;i<m;++i){
		while(R<query[i].R)++sum[++cnt[col[id[++R]]]];
		while(L>query[i].L)++sum[++cnt[col[id[--L]]]];
		while(R>query[i].R)--sum[cnt[col[id[R--]]]--];
		while(L<query[i].L)--sum[cnt[col[id[L++]]]--];
		ans[query[i].id]=sum[query[i].c];
	}
	for(int i=0;i<m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
/*
	
	Jul.12.16

	Tags:mo-algorithm,dfs clock
	Submissions:1

	Time 109ms
	Memory 9400KB

*/
