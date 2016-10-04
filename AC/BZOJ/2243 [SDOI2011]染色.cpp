#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,allc=0,
	col[N],par[N],dep[N],sz[N],son[N],top[N],tid[N];
vector<int>edge[N];
struct Segment_Tree{
	struct Node{
		int L,R,Lcol,Rcol,sum;
		bool same;
	}tree[N<<2];
	void push_up(int k){
		tree[k].Lcol=tree[k<<1].Lcol;
		tree[k].Rcol=tree[k<<1|1].Rcol;
		tree[k].sum=tree[k<<1].sum+tree[k<<1|1].sum-(tree[k<<1].Rcol==tree[k<<1|1].Lcol);
	}
	void update_same(int k,int c){
		tree[k].same=true;
		tree[k].Lcol=tree[k].Rcol=c;
		tree[k].sum=1;
	}
	void push_down(int k){
		if(!tree[k].same)return;
		update_same(k<<1,tree[k].Lcol);
		update_same(k<<1|1,tree[k].Lcol);
		tree[k].same=false;
	}
	void build(int L,int R,int k=1){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].same=false;
		if(L==R)return;
		int mid=L+R>>1;
		build(L,mid,k<<1);
		build(mid+1,R,k<<1|1);
	}
	void update(int L,int R,int c,int k=1){
		if(tree[k].L==L&&tree[k].R==R){
			update_same(k,c);
			return;
		}
		push_down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)update(L,R,c,k<<1);
		else if(L>mid)update(L,R,c,k<<1|1);
		else{
			update(L,mid,c,k<<1);
			update(mid+1,R,c,k<<1|1);
		}
		push_up(k);
	}
	int query_color(int tar){
		int cur=1;
		while(tree[cur].L<tree[cur].R){
			push_down(cur);
			int mid=tree[cur].L+tree[cur].R>>1;
			if(tar<=mid)cur<<=1;
			else cur=cur<<1|1;
		}
		return tree[cur].Lcol;
	}
	int query(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R)
			return tree[k].sum;
		push_down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)return query(L,R,k<<1);
		if(L>mid)return query(L,R,k<<1|1);
		return query(L,mid,k<<1)+query(mid+1,R,k<<1|1)-(query_color(mid)==query_color(mid+1));
		// WA: didn't judge if mid's color is the same as mid+1's
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
	tid[cur]=++allc;
	T.update(tid[cur],tid[cur],col[cur]);
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
	T.build(1,n);
	dfs(1,1);
}
void Change(int u,int v,int c){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		T.update(tid[top[u]],tid[u],c);
		u=par[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	T.update(tid[u],tid[v],c);
}
int Query(int u,int v){
	int res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		res+=T.query(tid[top[u]],tid[u]);
		if(T.query_color(tid[top[u]])==T.query_color(tid[par[top[u]]]))--res;
		u=par[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	res+=T.query(tid[u],tid[v]);
	return res;
}
int main(){
	int m,a,b,c;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&col[i]);
		edge[i].clear();
	}
	for(int i=1;i<n;++i){
		scanf("%d%d",&a,&b);
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	init();
	char ope[5];
	while(m--&&~scanf("%s%d%d",ope,&a,&b)){
		if(ope[0]=='C'){
			scanf("%d",&c);
			Change(a,b,c);
		}
		else printf("%d\n",Query(a,b));
	}
	return 0;
}
/*
	
	Feb.28.16
	
	Tags:HLD,Segment Tree
	Submissions:3
	
	Memory 20200kb
	Time 8732ms
	Code Length 3654B
	
*/
