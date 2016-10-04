#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=(int)1e5+5,LEN=31;
int n,tot_edge,dfs_clock,head[N],val[N],pre[N],post[N],ans[N];
struct Edge{
	int to,nxt;
	Edge(){}
	Edge(int to,int nxt):to(to),nxt(nxt){}
}edge[N<<1];
struct Ope{
	bool type;
	int num,aux;
	/*
		type=0:update
			aux:-1 or 1
		
		type=1:query
			aux:id of the query
	*/
	Ope(){}
	Ope(bool type,int num,int aux):type(type),num(num),aux(aux){}
};
struct Trie{
	static const int NODE=LEN*N<<1;
	int allc,son[NODE][2],mul[NODE];
	bool bin[LEN];
	inline void init(){
		son[0][0]=son[0][1]=allc=0;
	}
	void convert(int num){
		for(int i=LEN-1;~i;--i,num>>=1)
			bin[i]=num&1;
	}
	int newNode(){
		++allc;
		mul[allc]=son[allc][0]=son[allc][1]=0;
		return allc;
	}
	void update(int num,int sgn){
		convert(num);
		for(int i=0,cur=0;i<LEN;mul[cur=son[cur][bin[i++]]]+=sgn){
			if(!son[cur][bin[i]])
				son[cur][bin[i]]=newNode();
		}
	}
	int query_mx(int num){
		convert(num);
		int res=0;
		for(int i=0,cur=0;i<LEN;++i){
			res<<=1;
			if(mul[son[cur][bin[i]^1]]){
				res|=1;
				cur=son[cur][bin[i]^1];
			}
			else cur=son[cur][bin[i]];
		}
		return res;
	}
}trie;
struct Segment_Tree{
	vector<Ope>ope[N<<2];
	#define lson l,mid,k<<1
	#define rson mid+1,r,k<<1|1
	void build(int l=1,int r=n,int k=1){
		ope[k].clear();
		if(l==r)return;
		int mid=l+r>>1;
		build(lson);
		build(rson);
	}
	void update(int L,int R,int num,int sgn,int l=1,int r=n,int k=1){
		if(l==L&&r==R){
			ope[k].push_back(Ope(0,num,sgn));
			return;
		}
		int mid=l+r>>1;
		if(R<=mid)update(L,R,num,sgn,lson);
		else if(L>mid)update(L,R,num,sgn,rson);
		else{
			update(L,mid,num,sgn,lson);
			update(mid+1,R,num,sgn,rson);
		}
	}
	void query(int tar,int num,int id,int l=1,int r=n,int k=1){
		ope[k].push_back(Ope(1,num,id));
		if(l==r)return;
		int mid=l+r>>1;
		if(tar<=mid)query(tar,num,id,lson);
		else query(tar,num,id,rson);
	}
	inline void Max(int &a,int b){
		if(b>a)a=b;
	}
	void consider(int l=1,int r=n,int k=1){
		trie.init();
		for(int i=0;i<(int)ope[k].size();++i){
			int num=ope[k][i].num,
				aux=ope[k][i].aux;
			if(ope[k][i].type){
				Max(ans[aux],trie.query_mx(num));
			}
			else{
				trie.update(num,aux);
			}
		}
		if(l==r)return;
		int mid=l+r>>1;
		consider(lson);
		consider(rson);
	}
}sgt;
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
void add_edge(int u,int v){
	edge[tot_edge]=Edge(v,head[u]);
	head[u]=tot_edge++;
}
void dfs(int cur,int par=0){
	pre[cur]=++dfs_clock;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int son=edge[i].to;
		if(son==par)continue;
		dfs(son,cur);
	}
	post[cur]=dfs_clock;
}
void solve(){
	int m;
	rd(n);rd(m);
	tot_edge=0;
	memset(head,-1,n+1<<2);
	for(int i=2,par;i<=n;++i){
		rd(par);
		add_edge(i,par);
		add_edge(par,i);
	}
	for(int i=1;i<=n;++i)
		rd(val[i]);
	dfs_clock=0;
	dfs(1);
	sgt.build();
	for(int i=1;i<=n;++i)
		sgt.update(pre[i],post[i],val[i],1);
	int cnt_query=0;
	for(int i=0,ope,u;i<m;++i){
		rd(ope);rd(u);
		if(ope){
			sgt.query(pre[u],val[u],cnt_query);
			ans[cnt_query++]=0;
		}
		else{
			sgt.update(pre[u],post[u],val[u],-1);
			rd(val[u]);
			sgt.update(pre[u],post[u],val[u],1);
		}
	}
	sgt.consider();
	for(int i=0;i<cnt_query;++i)
		printf("%d\n",ans[i]);
}
int main(){
	int cas;
	rd(cas);
	while(cas--)solve();
	return 0;
}
/*
	
	Jul.06.16
	
	Tags:dfs,segment tree,trie
	Submissions:1
	
	Memory(KB) 118200
	Time(ms) 2730
	Length(Bytes) 3372
	
*/
