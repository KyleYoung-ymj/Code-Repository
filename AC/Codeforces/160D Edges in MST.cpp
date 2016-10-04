#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int tot_edge,head[N],dfs_clock,pre[N],par[N],ans[N];
// ans[i]=0:any 1:at least one 2:none
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
struct EDGE{
	int u,v,cost,id;
	inline void Rd(){
		rd(u);rd(v);rd(cost);
	}
	inline bool operator <(const EDGE &tmp)const{
		return cost<tmp.cost;
	}
}es[N];
struct Edge{
	int to,nxt,id;
}edge[N<<1];
void add_edge(int u,int v,int id){
	edge[tot_edge]=(Edge){v,head[u],id};
	head[u]=tot_edge++;
}
int get_root(int x){
	return par[x]==x?x:par[x]=get_root(par[x]);
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int dfs(int u,int id){
	int lowu=pre[u]=++dfs_clock;
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].to;
		if(!pre[v]){
			int lowv=dfs(v,i);
			Min(lowu,lowv);
			if(lowv>pre[u])ans[edge[i].id]=0;
		}
		else if(pre[v]<pre[u]&&i!=(id^1)){
			Min(lowu,pre[v]);
		}
	}
	return lowu;
}
void unite(int u,int v){
	u=get_root(u);
	v=get_root(v);
	if(u==v)return;
	par[u]=v;
}
int main(){
	int n,m;
	rd(n);rd(m);
	for(int i=1;i<=n;++i)
		par[i]=i;
	for(int i=0;i<m;++i){
		es[i].Rd();
		es[i].id=i;
	}
	sort(es,es+m);
	for(int i=0;i<m;){
		int j=i;
		while(j+1<m&&es[j+1].cost==es[j].cost)++j;
		tot_edge=dfs_clock=0;
		for(int k=i;k<=j;++k){
			es[k].u=get_root(es[k].u);
			es[k].v=get_root(es[k].v);
			int u=es[k].u,v=es[k].v;
			head[u]=head[v]=-1;
			pre[u]=pre[v]=0;
		}
		for(int k=i;k<=j;++k){
			int u=es[k].u,v=es[k].v,id=es[k].id;
			if(u==v){
				ans[id]=2;
				continue;
			}
			ans[id]=1;
			add_edge(u,v,id);
			add_edge(v,u,id);
		}
		for(int k=i;k<=j;++k){
			if(!pre[es[k].u])dfs(es[k].u,-1);
		}
		for(;i<=j;++i)
			unite(es[i].u,es[i].v);
	}
	for(int i=0;i<m;++i){
		if(ans[i]==2)puts("none");
		else puts(ans[i]?"at least one":"any");
	}
	return 0;
}
/*
	
	Jun.24.16
	
	Tags:tree,MST,dsu,dfs,bridge
	Submissions:2
	
	Time 122ms
	Memory 8100KB
	
*/
