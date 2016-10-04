#include<cstdio>
#include<cstring>
#include<algorithm>
#define fi first
#define se second
#define lowbit(x) (x&-x)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=(int)1e5+5,mod=(int)1e9+7;
int n,val[N],tot_sum,
	tot_edge,head[N],
	dfs_clock,pre[N],post[N],
	par[N],dep[N],sz[N],
	allc,heavy_son[N],top[N],Tid[N],
	val_bit[N],w_bit[N];
pii edge[N<<1];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
inline int sqr(int x){
	return 1ll*x*x%mod;
}
void add(int *bit,int x,int v){
	for(;x<=n;x+=lowbit(x))
		mod_add(bit[x],v);
}
int sum(int *bit,int x){
	int res=0;
	for(;x;x-=lowbit(x))
		mod_add(res,bit[x]);
	return res;
}
int query_sum(int *bit,int L,int R){
	return sum(bit,R)-sum(bit,L-1);
}
int query_subtree_sum(int v){
	return query_sum(val_bit,pre[v],post[v]);
}
void dfs(int cur,int fa=0,int depth=0){
	add(val_bit,pre[cur]=++dfs_clock,val[cur]);
	par[cur]=fa;
	dep[cur]=depth++;
	sz[cur]=1;
	heavy_son[cur]=0;
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==fa)continue;
		dfs(son,cur,depth);
		sz[cur]+=sz[son];
		if(!heavy_son[cur]||sz[son]>sz[heavy_son[cur]])
			heavy_son[cur]=son;
	}
	post[cur]=dfs_clock;
}
void allc_dfs(int cur,int anc){
	top[cur]=anc;
	Tid[cur]=++allc;
	if(heavy_son[cur])allc_dfs(heavy_son[cur],anc);
	int light_sum=0;
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==par[cur]||son==heavy_son[cur])continue;
		allc_dfs(son,son);
		mod_add(light_sum,sqr(query_subtree_sum(son)));
	}
	add(w_bit,Tid[cur],light_sum);
}
void Modify(int tar,int v){
	int delta=v-val[tar];
	if(delta<0)delta+=mod;
	val[tar]=v;
	mod_add(tot_sum,delta);
	add(val_bit,pre[tar],delta);

	for(tar=top[tar];par[tar];tar=top[par[tar]]){
		int cur_sum=query_subtree_sum(tar),
			tmp=sqr(cur_sum)-sqr(cur_sum-delta);
		if(tmp<0)tmp+=mod;
		add(w_bit,Tid[par[tar]],tmp);
	}
}
int Query(int u,int v){
	ll ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);

		ans+=query_sum(w_bit,Tid[top[u]],Tid[u]);
		if(heavy_son[u])ans+=sqr(query_subtree_sum(heavy_son[u]));
		ans-=sqr(query_subtree_sum(top[u]));

		u=par[top[u]];
	}

	if(dep[u]>dep[v])swap(u,v);

	ans+=query_sum(w_bit,Tid[u],Tid[v]);
	if(heavy_son[v])ans+=sqr(query_subtree_sum(heavy_son[v]));

	ans+=sqr(tot_sum-query_subtree_sum(u));

	ans=sqr(tot_sum)-ans;
	ans%=mod;
	if(ans<0)ans+=mod;
	return (int)ans;
}
void solve(){
	int m,ope,a,b;
	rd(m);
	tot_sum=0;
	for(int i=1;i<=n;++i){
		rd(val[i]);
		mod_add(tot_sum,val[i]);
	}
	tot_edge=0;
	memset(head,-1,n+1<<2);
	for(int i=1,u,v;i<n;++i){
		rd(u);rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs_clock=0;
	memset(val_bit,0,n+1<<2);
	memset(w_bit,0,n+1<<2);
	dfs(1);
	allc=0;
	allc_dfs(1,1);
	while(m--){
		rd(ope);rd(a);rd(b);
		if(ope==1)Modify(a,b);
		else printf("%d\n",Query(a,b));
	}
}
int main(){
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	Jul.10.16

	Tags:tree,dfs clock,bit,HLD
	Submissions:1

	Memory(KB) 13560
	Time(ms) 1201
	Length(Bytes) 3088 

*/