#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e5+5;
typedef long long ll;
int n,tot_edge,dfs_clock,head[N],dep[N],pre[N],post[N],org_val[N];
ll arr[N];
struct Edge{
	int to,nxt;
}edge[N<<1];
struct Segment_Tree{
	struct Node{
		int L,R;
		ll add;
	}tree[N<<2];
	ll val[N];
	void push_down(int k){
		if(!tree[k].add)return;
		tree[k<<1].add+=tree[k].add;
		tree[k<<1|1].add+=tree[k].add;
		tree[k].add=0;
	}
	void construct(bool mark,int L,int R,int k=1){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].add=0;
		if(L==R){
			val[L]=mark*arr[L];
			return;
		}
		int mid=L+R>>1;
		construct(mark,L,mid,k<<1);
		construct(mark,mid+1,R,k<<1|1);
	}
	ll query(int tar){
		int cur=1;
		while(tree[cur].L!=tree[cur].R){
			push_down(cur);
			int mid=tree[cur].L+tree[cur].R>>1;
			if(tar<=mid)cur<<=1;
			else (cur<<=1)|=1;
		}
		return val[tar]+tree[cur].add;
	}
	void update(int L,int R,ll val,int k=1){
		if(tree[k].L==L&&tree[k].R==R){
			tree[k].add+=val;
			return;
		}
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)update(L,R,val,k<<1);
		else if(L>mid)update(L,R,val,k<<1|1);
		else{
			update(L,mid,val,k<<1);
			update(mid+1,R,val,k<<1|1);
		}
	}
}K,B;
void add_edge(int from,int to){
	edge[tot_edge]=(Edge){to,head[from]};
	head[from]=tot_edge++;
}
void dfs(int cur,int par,int depth,ll sum){
	dep[cur]=depth++;
	arr[pre[cur]=++dfs_clock]=(sum+=org_val[cur]);
	for(int i=head[cur];~i;i=edge[i].nxt){
		if(edge[i].to==par)continue;
		dfs(edge[i].to,cur,depth,sum);
	}
	post[cur]=dfs_clock;
}
inline void add_node(int tar,int val){
	B.update(pre[tar],post[tar],val);
}
inline void add_subtree(int tar,int val){
	K.update(pre[tar],post[tar],val);
	B.update(pre[tar],post[tar],1ll*val*(1-dep[tar]));
}
inline ll Query(int tar){
	return K.query(pre[tar])*dep[tar]+B.query(pre[tar]);
}
int main(){
	int m,ope,tar,val;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&org_val[i]);
	tot_edge=0;
	memset(head,-1,sizeof(head));
	for(int i=1,a,b;i<n;++i){
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		add_edge(b,a);
	}
	dfs_clock=0;
	dfs(1,-1,0,0);
	K.construct(0,1,n);
	B.construct(1,1,n);
	while(m--){
		scanf("%d%d",&ope,&tar);
		if(ope^3)scanf("%d",&val);
		switch(ope){
			case 1:
				add_node(tar,val);
				break;
			case 2:
				add_subtree(tar,val);
				break;
			case 3:
				printf("%lld\n",Query(tar));
				break;
		}
	}
	return 0;
}
/*
	
	Apr.27.16
	
	Tags:dfs clock,Segment Tree
	Submissions:7
	
	Memory 23000kb
	Time 1848ms
	Code Length 2709B
	
*/
