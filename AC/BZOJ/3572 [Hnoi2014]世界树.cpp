#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=3e5+5,LG=20;
int n,dfn=0,tot_edge=0,
	head[N],id[N],dep[N],par[N][LG],sz[N],
	node[N],org[N],
	belong[N]={0},rem[N]={0},stk[N],ans[N]={0};
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>=48);
}
struct Edge{
	int to,nxt;
}edge[N<<1];
void add_edge(int a,int b){
	edge[tot_edge]=(Edge){b,head[a]};
	head[a]=tot_edge++;
}
void pre_dfs(int cur,int fa){
	id[cur]=++dfn;
	dep[cur]=dep[fa]+1;
	par[cur][0]=fa;
	for(int i=1;i<LG;++i)
		par[cur][i]=par[par[cur][i-1]][i-1];
	sz[cur]=1;
	for(int i=head[cur];~i;i=edge[i].nxt){
		if(edge[i].to==fa)continue;
		pre_dfs(edge[i].to,cur);
		sz[cur]+=sz[edge[i].to];
	}
}
inline bool cmp(int a,int b){
	return id[a]<id[b];
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
inline int dist(int u,int v){
	return dep[u]+dep[v]-(dep[lca(u,v)]<<1);
}
void DP0(int cur){
	rem[cur]=sz[cur];
	for(int i=head[cur];~i;i=edge[i].nxt){
		DP0(edge[i].to);
		if(!belong[edge[i].to])continue;
		int dis0=dist(cur,belong[cur]),
			dis1=dist(cur,belong[edge[i].to]);
		if(!belong[cur]||dis1<dis0||dis0==dis1&&belong[edge[i].to]<belong[cur])
			belong[cur]=belong[edge[i].to];
	}
}
void DP1(int cur){
	for(int i=head[cur];~i;i=edge[i].nxt){
		int dis0=dist(edge[i].to,belong[edge[i].to]),
			dis1=dist(edge[i].to,belong[cur]);
		if(dis1<dis0||dis0==dis1&&belong[cur]<belong[edge[i].to])
			belong[edge[i].to]=belong[cur];
		DP1(edge[i].to);
	}
}
void solve(int u,int v){// dep[v]>dep[u]
	int son=v,mid=v,
		step=dep[v]-dep[u]-1;
	for(int i=0;i<LG;++i)
		if(step&1<<i)
			son=par[son][i];
	rem[u]-=sz[son];
	if(belong[u]==belong[v]){
		ans[belong[u]]+=sz[son]-sz[v];
		return;
	}
	for(int i=LG-1;~i;--i){
		int fa=par[mid][i];
		if(dep[fa]<=dep[u])continue;
		int	dis0=dist(fa,belong[u]),
			dis1=dist(fa,belong[v]);
		if(dis1<dis0||dis0==dis1&&belong[v]<belong[u])
			mid=fa;
	}
	ans[belong[u]]+=sz[son]-sz[mid];
	ans[belong[v]]+=sz[mid]-sz[v];
}
void dfs_solve(int cur){
	for(int i=head[cur];~i;i=edge[i].nxt){
		solve(cur,edge[i].to);
		dfs_solve(edge[i].to);
	}
}
void dfs_rem(int cur){
	ans[belong[cur]]+=rem[cur];
	for(int i=head[cur];~i;i=edge[i].nxt)
		dfs_rem(edge[i].to);
}
void dfs_clear(int cur){
	ans[belong[cur]]=0;
	belong[cur]=0;
	for(int i=head[cur];~i;i=edge[i].nxt)
		dfs_clear(edge[i].to);
	head[cur]=-1;
}
void Solve(){
	int m,top=0;
	rd(m);
	for(int i=0;i<m;++i){
		rd(node[i]);
		belong[node[i]]=org[i]=node[i];
	}
	sort(node,node+m,cmp);
	if(belong[1]!=1)stk[++top]=1;
	tot_edge=0;
	for(int i=0;i<m;++i){
		int anc=-1;
		while(top){
			anc=lca(stk[top],node[i]);
			if(top>1&&dep[anc]<dep[stk[top-1]]){
				add_edge(stk[top-1],stk[top]);
				--top;
			}
			else if(dep[anc]<dep[stk[top]]){
				add_edge(anc,stk[top]);
				--top;
				break;
			}
			else break;
		}
		if(~anc&&stk[top]!=anc)stk[++top]=anc;
		stk[++top]=node[i];
	}
	while(top>1){
		add_edge(stk[top-1],stk[top]);
		--top;
	}
	DP0(1);
	DP1(1);
	dfs_solve(1);
	dfs_rem(1);
	for(int i=0;i<m;++i)
		printf("%d%c",ans[org[i]],i==m-1?'\n':' ');
	dfs_clear(1);
}
int main(){
	rd(n);
	int m,a,b;
	memset(head,-1,sizeof(head));
	for(int i=1;i<n;++i){
		rd(a);rd(b);
		add_edge(a,b);
		add_edge(b,a);
	}
	dep[0]=0;
	pre_dfs(1,0);
	rd(m);
	memset(head,-1,sizeof(head));
	while(m--)Solve();
	return 0;
}
/*
	
	Mar.02.16
	
	Tags:Virtual Tree,dp,binary search
	Submissions:3
	
	Memory 45276kb
	Time 7488ms
	Code Length 4125B
	
*/
