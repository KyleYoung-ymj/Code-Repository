#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=3e4+5,INF=1e9;
int n,allc=0,qmx,qsum,
	val[N],par[N],dep[N],sz[N],son[N],top[N],tid[N];
vector<int>edge[N];
struct Segment_Tree{
	struct Node{
		int L,R,mx,sum;
	}tree[N<<2];
	void push_up(int k){
		tree[k].mx=max(tree[k<<1].mx,tree[k<<1|1].mx);
		tree[k].sum=tree[k<<1].sum+tree[k<<1|1].sum;
	}
	void construct(int L,int R,int k=1){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].mx=-INF;
		tree[k].sum=0;
		if(L==R)return;
		int mid=L+R>>1;
		construct(L,mid,k<<1);
		construct(mid+1,R,k<<1|1);
	}
	inline void Max(int &a,int b){
		if(b>a)a=b;
	}
	void query(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R){
			qsum+=tree[k].sum;
			Max(qmx,tree[k].mx);
			return;
		}
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)query(L,R,k<<1);
		else if(L>mid)query(L,R,k<<1|1);
		else{
			query(L,mid,k<<1);
			query(mid+1,R,k<<1|1);
		}
	}
	void update(int tar,int v,int k=1){
		if(tree[k].L==tree[k].R){
			tree[k].mx=tree[k].sum=v;
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
		int to=edge[cur][i];
		if(to==fa)continue;
		pre_dfs(to,cur,depth+1);
		sz[cur]+=sz[to];
		if(son[cur]==-1||sz[to]>sz[son[cur]])son[cur]=to;
	}
}
void dfs(int cur,int anc){
	T.update(tid[cur]=++allc,val[cur]);
	top[cur]=anc;
	if(~son[cur])dfs(son[cur],anc);
	else return;
	for(int i=0;i<edge[cur].size();++i){
		int to=edge[cur][i];
		if(to==par[cur]||to==son[cur])continue;
		dfs(to,to);
	}
}
void init(){
	pre_dfs(1,-1,0);
	T.construct(1,n);
	dfs(1,1);
}
inline void Change(int tar,int v){
	T.update(tid[tar],v);
}
void Query(int u,int v){
	qsum=0;
	qmx=-INF;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		T.query(tid[top[u]],tid[u]);
		u=par[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	T.query(tid[u],tid[v]);
}
int main(){
	int m,a,b;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		edge[i].clear();
	for(int i=1;i<n;++i){
		scanf("%d%d",&a,&b);
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	for(int i=1;i<=n;++i)
		scanf("%d",&val[i]);
	init();
	scanf("%d",&m);
	char ope[10];
	while(m--&&~scanf("%s%d%d",ope,&a,&b)){
		if(ope[0]=='C')Change(a,b);
		else{
			Query(a,b);
			printf("%d\n",ope[1]=='S'?qsum:qmx);
		}
	}
	return 0;
}
/*
	
	Feb.27.16
	
	Tags:HLD
	Submissions:1
	
	Time 2306ms
	Memory 2.38kb
	Code Length 6.16Mb
	
*/
