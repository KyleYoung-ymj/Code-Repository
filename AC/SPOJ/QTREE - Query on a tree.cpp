#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1e4+5,INF=2e9;
int n,allc,
	par[N],dep[N],sz[N],son[N],top[N],tid[N],val[N];
struct EDGE{
	int u,v,cost;
}es[N];
struct Edge{
	int to,cost;
};
vector<Edge>edge[N];
struct Segment_Tree{
	struct Node{
		int L,R,mx;
	}tree[N<<2];
	void construct(int L,int R,int k=1){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].mx=0;
		if(L==R)return;
		int mid=L+R>>1;
		construct(L,mid,k<<1);
		construct(mid+1,R,k<<1|1);
	}
	inline void push_up(int k){
		tree[k].mx=max(tree[k<<1].mx,tree[k<<1|1].mx);
	}
	int query(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R)
			return tree[k].mx;
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)return query(L,R,k<<1);
		if(L>mid)return query(L,R,k<<1|1);
		return max(query(L,mid,k<<1),query(mid+1,R,k<<1|1));
	}
	void update(int tar,int v,int k=1){
		if(tree[k].L==tree[k].R){
			tree[k].mx=v;
			return;
		}
		int mid=tree[k].L+tree[k].R>>1;
		if(tar<=mid)update(tar,v,k<<1);
		else update(tar,v,k<<1|1);
		push_up(k);
	}
}T;
void pre_dfs(int cur,int fa,int depth){
	par[cur]=fa;
	dep[cur]=depth;
	sz[cur]=1;
	son[cur]=-1;
	for(int i=0;i<edge[cur].size();++i){
		int to=edge[cur][i].to;
		if(to==fa)continue;
		val[to]=edge[cur][i].cost;
		pre_dfs(to,cur,depth+1);
		sz[cur]+=sz[to];
		if(son[cur]==-1||sz[to]>sz[son[cur]])
			son[cur]=to;
	}
}
void dfs(int cur,int anc){
	tid[cur]=++allc;
	top[cur]=anc;
	if(~son[cur])dfs(son[cur],anc);
	else return;
	for(int i=0;i<edge[cur].size();++i){
		int to=edge[cur][i].to;
		if(to==par[cur]||to==son[cur])continue;
		dfs(to,to);
	}
}
void init(){
	pre_dfs(1,-1,0);
	allc=0;
	dfs(1,1);
	T.construct(1,n);
	val[1]=-INF;
	for(int i=1;i<=n;++i)
		T.update(tid[i],val[i]);
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int Query(int u,int v){
	int mx=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		Max(mx,T.query(tid[top[u]],tid[u]));
		u=par[top[u]];
	}
	if(u==v)return mx;
	if(dep[u]>dep[v])swap(u,v);
	return max(mx,T.query(tid[son[u]],tid[v]));
}
void Change(int id,int x){
	int u=es[id].u,v=es[id].v;
	if(dep[u]>dep[v])swap(u,v);
	T.update(tid[v],x);
}
int main(){
	int cas,a,b,c;
	char ope[10];
	scanf("%d",&cas);
	while(cas--&&~scanf("%d",&n)){
		for(int i=1;i<=n;++i)
			edge[i].clear();
		for(int i=1;i<n;++i){
			scanf("%d%d%d",&a,&b,&c);
			es[i].u=a;
			es[i].v=b;
			es[i].cost=c;
			edge[a].push_back((Edge){b,c});
			edge[b].push_back((Edge){a,c});
		}
		init();
		while(~scanf("%s",ope)&&ope[0]!='D'){
			scanf("%d%d",&a,&b);
			if(ope[0]=='Q')printf("%d\n",Query(a,b));
			else Change(a,b);
		}
	}
	return 0;
}
/*
	
	Feb.27.16
	
	Tags:HLD,classic
	Submissions:2
	
	TIME 0.41
	MEM 4.8M
	
*/
