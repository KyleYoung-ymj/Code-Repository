#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int dfs_clock,tot_edge,head[N],pre[N],post[N],val[N];
typedef __int64 ll;
const ll INF=1ll<<60;
struct Edge{
	int to,nxt;
}edge[N<<1];
struct Segment_Tree{
	struct Node{
		int L,R;
		ll mx,extra;
	}tree[N<<2];
	inline void push_up(int k){
		tree[k].mx=max(tree[k<<1].mx,tree[k<<1|1].mx);
	}
	void push_down(int k){
		ll &tmp=tree[k].extra;
		if(!tmp)return;
		tree[k<<1].mx+=tmp;
		tree[k<<1|1].mx+=tmp;
		tree[k<<1].extra+=tmp;
		tree[k<<1|1].extra+=tmp;
		tmp=0;
	}
	void init(int L,int R,int k=1){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].mx=-INF;
		tree[k].extra=0;
		if(L==R)return;
		int mid=L+R>>1;
		init(L,mid,k<<1);
		init(mid+1,R,k<<1|1);
	}
	void assign(int tar,ll amt,int k=1){
		if(tree[k].L==tree[k].R){
			tree[k].mx=amt;
			return;
		}
		push_down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(tar<=mid)assign(tar,amt,k<<1);
		else assign(tar,amt,k<<1|1);
		push_up(k);
	}
	ll query(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R)return tree[k].mx;
		push_down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)return query(L,R,k<<1);
		if(L>mid)return query(L,R,k<<1|1);
		return max(query(L,mid,k<<1),query(mid+1,R,k<<1|1));
	}
	void add(int L,int R,int amt,int k=1){
		if(tree[k].L==L&&tree[k].R==R){
			tree[k].mx+=amt;
			tree[k].extra+=amt;
			return;
		}
		push_down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)add(L,R,amt,k<<1);
		else if(L>mid)add(L,R,amt,k<<1|1);
		else{
			add(L,mid,amt,k<<1);
			add(mid+1,R,amt,k<<1|1);
		}
		push_up(k);
	}
}T;
inline void add_edge(int from,int to){
	edge[tot_edge].to=to;
	edge[tot_edge].nxt=head[from];
	head[from]=tot_edge++;
}
void dfs(int cur,int par,ll sum){
	T.assign(pre[cur]=++dfs_clock,sum+=val[cur]);
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==par)continue;
		dfs(to,cur,sum);
	}
	post[cur]=dfs_clock;
}
void solve(){
	int n,m,ope,x,y;
	scanf("%d%d",&n,&m);
	tot_edge=0;
	memset(head,-1,n<<2);
	for(int i=1,u,v;i<n;++i){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=0;i<n;++i)
		scanf("%d",&val[i]);
	T.init(1,n);
	dfs_clock=0;
	dfs(0,-1,0);
	while(m--&&scanf("%d%d",&ope,&x)){
		if(ope)printf("%I64d\n",T.query(pre[x],post[x]));
		else{
			scanf("%d",&y);
			T.add(pre[x],post[x],y-val[x]);
			val[x]=y;
		}
	}
}
int main(){
	int cas,kase=0;
	scanf("%d",&cas);
	while(cas--){
		printf("Case #%d:\n",++kase);
		solve();
	}
	return 0;
}
/*
	
	May.21.16
	
	Tags:dfs,Segment Tree
	Submissions:3
	
	Exe.Time 2386MS
	Exe.Memory 14520K
	Code Len. 2645B
	
*/
