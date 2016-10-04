#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e4+5,LG=15;
int n,tot_edge,root,head[N],val[N],dfs_clock,pre[N],post[N],bit[N],par[N][LG],dep[N];
struct Edge{
	int to,nxt;
}edge[N<<1];
inline void add_edge(int from,int to){
	edge[tot_edge]=(Edge){to,head[from]};
	head[from]=tot_edge++;
}
void add(int x,int a){
	while(x<=n){
		bit[x]+=a;
		x+=x&-x;
	}
}
int sum(int x){
	int res=0;
	while(x){
		res+=bit[x];
		x&=x-1;
	}
	return res;
}
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
void dfs(int cur,int fa,int depth){
	par[cur][0]=fa;
	dep[cur]=depth++;
	for(int i=1;i<LG;++i)
		par[cur][i]=par[par[cur][i-1]][i-1];
	add(pre[cur]=++dfs_clock,val[cur]);
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==fa)continue;
		dfs(to,cur,depth);
	}
	post[cur]=dfs_clock;
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
inline int subtree_sum(int x){
	return sum(post[x])-sum(pre[x]-1);
}
int query(int x){
	if(x==root)return subtree_sum(1);
	if(lca(x,root)!=x)return subtree_sum(x);
	return subtree_sum(1)-subtree_sum(up(root,dep[root]-dep[x]-1));
}
void solve(){
	rd(n);
	memset(bit,0,n+1<<2);
	tot_edge=0;
	memset(head,-1,n+1<<2);
	for(int i=1,u,v;i<n;++i){
		rd(u);rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;++i)
		rd(val[i]);
	dfs_clock=0;
	dfs(1,-1,0);
	root=1;
	int m,x,a;
	char ope[10];
	rd(m);
	while(m--){
		scanf("%s",ope);rd(x);
		if(ope[0]=='C'){
			rd(a);
			add(pre[x],a-val[x]);
			val[x]=a;
		}
		else if(ope[0]=='Q')printf("%d\n",query(x));
		else root=x;
	}
}
int main(){
	int cas,kase=0;
	rd(cas);
	while(cas--){
		printf("Case #%d:\n",++kase);
		solve();
	}
	return 0;
}
/*
	
	May.14.16
	
	Tags:Tree,Data Structure
	Submissions:1
	
	Exe.Time 499MS
	Exe.Memory 2384K
	Code Len. 2099B
	
*/
