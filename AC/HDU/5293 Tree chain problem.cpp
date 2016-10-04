#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
const int N=1e5+5,LG=18;
typedef long long ll;
int tot_edge,head[N],
	allc_tid,
	par[N][LG],dep[N],sz[N],son[N],top[N],tid[N],
	dp[N],sum[N];
struct Edge{
	int to,nxt;
}edge[N<<1];
struct PATH{
	int u,v,val;
};
vector<PATH>Path[N];
struct PAIR{
	ll x,y;
	inline PAIR operator +(const PAIR &tmp)const{
		return (PAIR){x+tmp.x,y+tmp.y};
	}
};
struct Segment_Tree{
	struct Node{
		int L,R;
		ll sum,sum_dp;
	}tree[N<<2];
	void build(int L,int R,int k=1){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].sum=tree[k].sum_dp=0;
		if(L==R)return;
		int mid=L+R>>1;
		build(L,mid,k<<1);
		build(mid+1,R,k<<1|1);
	}
	void add(bool type,int tar,int val,int k=1){
		// type==0 -> sum  type==1 -> dp
		if(!type)tree[k].sum+=val;
		else tree[k].sum_dp+=val;
		if(tree[k].L==tree[k].R)return;
		int mid=tree[k].L+tree[k].R>>1;
		if(tar<=mid)add(type,tar,val,k<<1);
		else add(type,tar,val,k<<1|1);
	}
	PAIR query(int L,int R,int k=1){
		// return PAIR.x -> sum  PAIR.y -> dp
		if(tree[k].L==L&&tree[k].R==R)
			return (PAIR){tree[k].sum,tree[k].sum_dp};
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)return query(L,R,k<<1);
		if(L>mid)return query(L,R,k<<1|1);
		return query(L,mid,k<<1)+query(mid+1,R,k<<1|1);
	}
}T;
void add_edge(int a,int b){
	edge[tot_edge]=(Edge){b,head[a]};
	head[a]=tot_edge++;
}
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>=48);
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
void pre_dfs(int cur,int fa){
	par[cur][0]=fa;
	for(int i=1;i<LG;++i)
		par[cur][i]=par[par[cur][i-1]][i-1];
	dep[cur]=dep[par[cur][0]]+1;
	son[cur]=-1;
	sz[cur]=1;
	for(int i=head[cur];~i;i=edge[i].nxt){
		if(edge[i].to==fa)continue;
		pre_dfs(edge[i].to,cur);
		sz[cur]+=sz[edge[i].to];
		if(son[cur]==-1||sz[edge[i].to]>sz[son[cur]])
			son[cur]=edge[i].to;
	}
}
void dfs(int cur,int anc){
	top[cur]=anc;
	tid[cur]=++allc_tid;
	if(~son[cur])dfs(son[cur],anc);
	else return;
	for(int i=head[cur];~i;i=edge[i].nxt){
		if(edge[i].to==par[cur][0]||edge[i].to==son[cur])continue;
		dfs(edge[i].to,edge[i].to);
	}
}
void init(){
	dep[0]=allc_tid=0;
	pre_dfs(1,0);
	dfs(1,1);
	T.build(1,allc_tid);
}
int up(int x,int step){
	for(int i=0;i<LG;++i)
		if(step&1<<i)
			x=par[x][i];
	return x;
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	u=up(u,dep[u]-dep[v]);
	if(u==v)return u;
	for(int i=LG-1;~i;--i)
		if(par[u][i]!=par[v][i]){
			u=par[u][i];
			v=par[v][i];
		}
	return par[u][0];
}
int solve(int u,int v){
	ll res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		PAIR tmp=T.query(tid[top[u]],tid[u]);
		res+=tmp.x;
		res-=tmp.y;
		u=par[top[u]][0];
	}
	if(dep[u]>dep[v])swap(u,v);
	PAIR tmp=T.query(tid[u],tid[v]);
	res+=tmp.x;
	res-=tmp.y;
	return (int)res;
}
int SOLVE(int cur){
	dp[cur]=sum[cur]=0;
	for(int i=head[cur];~i;i=edge[i].nxt){
		if(edge[i].to==par[cur][0])continue;
		int tmp=SOLVE(edge[i].to);
		dp[cur]+=tmp;
		sum[cur]+=tmp;
	}
	T.add(0,tid[cur],sum[cur]);
	for(int i=0;i<Path[cur].size();++i)
		Max(dp[cur],solve(Path[cur][i].u,Path[cur][i].v)+Path[cur][i].val);
	T.add(1,tid[cur],dp[cur]);
	return dp[cur];
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		int n,m,u,v,val;
		rd(n);rd(m);
		tot_edge=0;
		memset(head,-1,sizeof(head));
		for(int i=1;i<n;++i){
			rd(u);rd(v);
			add_edge(u,v);
			add_edge(v,u);
		}
		init();
		for(int i=1;i<=n;++i)
			Path[i].clear();
		while(m--){
			rd(u);rd(v);rd(val);
			Path[lca(u,v)].push_back((PATH){u,v,val});
		}
		printf("%d\n",SOLVE(1));
	}
	return 0;
}
/*
	
	Mar.08.16
	
	Tags:dp,HLD
	Submissions:2
	
	Exe.Time 2028MS
	Exe.Memory 29496K
	Code Len. 3860B
	
	
*/
