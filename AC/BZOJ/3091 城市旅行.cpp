#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+5;
typedef unsigned long long ull;
int tot_edge,head[N];
ull val[N];
struct Edge{
	int to,nxt;
}edge[N<<1];
struct LCT{
	int par[N],ch[N][2],stk[N];
	bool flip[N];
	ull sz[N],add[N],sum[N],Lsum[N],Rsum[N],exp[N];
	void clear(){
		sz[0]=sum[0]=Lsum[0]=Rsum[0]=exp[0]=0;
		memset(ch,0,sizeof(ch));
		memset(add,0,sizeof(add));
		memset(flip,false,sizeof(flip));
	}
	void dfs(int cur){
		for(int i=head[cur];~i;i=edge[i].nxt){
			int to=edge[i].to;
			if(to==par[cur])continue;
			par[to]=cur;
			dfs(to);
		}
	}
	void init(){
		par[1]=0;
		dfs(1);
	}
	void push_up(int k){
		int L=ch[k][0],R=ch[k][1];
		sz[k]=sz[L]+sz[R]+1;
		sum[k]=sum[L]+sum[R]+val[k];
		Lsum[k]=Lsum[L]+Lsum[R]+(val[k]+sum[R])*(sz[L]+1);
		Rsum[k]=Rsum[L]+Rsum[R]+(val[k]+sum[L])*(sz[R]+1);
		exp[k]=exp[L]+exp[R]+Lsum[L]*(sz[R]+1)+Rsum[R]*(sz[L]+1)+val[k]*(sz[L]+1)*(sz[R]+1);
	}
	inline ull calc(ull n){// sigma(i*(n+1-i))
		return n*(n+1)*(n+2)/6;
	}
	void update_reverse(int k){
		swap(ch[k][0],ch[k][1]);
		swap(Lsum[k],Rsum[k]);
		flip[k]^=1;
	}
	void update_add(int k,ull d){
		if(!k)return;
		val[k]+=d;
		add[k]+=d;
		sum[k]+=d*sz[k];
		ull amt=d*sz[k]*(sz[k]+1)>>1;
		Lsum[k]+=amt;
		Rsum[k]+=amt;
		exp[k]+=d*calc(sz[k]);
	}
	void push_down(int k){
		if(flip[k]){
			update_reverse(ch[k][0]);
			update_reverse(ch[k][1]);
			flip[k]=false;
		}
		if(add[k]){
			update_add(ch[k][0],add[k]);
			update_add(ch[k][1],add[k]);
			add[k]=0;
		}
	}
	inline bool is_root(int x){
		return ch[par[x]][0]!=x&&ch[par[x]][1]!=x;
	}
	void rotate(int x,bool f){
		int y=par[x];
		par[ch[x][f]]=y;
		ch[y][!f]=ch[x][f];
		par[x]=par[y];
		if(!is_root(y))ch[par[y]][ch[par[y]][1]==y]=x;
		par[y]=x;
		ch[x][f]=y;
		push_up(y);
		push_up(x);
	}
	void update(int x){
		int top=0;
		stk[top++]=x;
		for(;!is_root(x);x=par[x])
			stk[top++]=par[x];
		while(top)push_down(stk[--top]);
	}
	void Splay(int x){
		update(x);
		while(!is_root(x)){
			int y=par[x];
			if(is_root(y))rotate(x,ch[y][0]==x);
			else{
				bool flag=ch[par[y]][0]==y;
				if(ch[y][flag]==x)rotate(x,!flag);
				else rotate(y,flag);
				rotate(x,flag);
			}
		}
	}
	void Access(int x){
		for(int y=0;x;y=x,x=par[x]){
			Splay(x);
			ch[x][1]=y;
			push_up(x);
		}
	}
	void make_root(int x){
		Access(x);
		Splay(x);
		update_reverse(x);
	}
	int find_root(int x){
		Access(x);
		Splay(x);
		for(;;x=ch[x][0]){
			if(!ch[x][0]){
				Splay(x);
				return x;
			}
		}
	}
	void link(int u,int v){
		if(find_root(u)==find_root(v))return;
		make_root(u);
		par[u]=v;
		Access(u);
	}
	void cut(int u,int v){
		if(u==v||find_root(u)!=find_root(v))return;
		make_root(u);
		Access(v);
		Splay(v);
		if(par[u]==v&&sz[u]==1){
			ch[v][0]=par[u]=0;
			push_up(v);
		}
	}
	ull gcd(ull a,ull b){
		return b?gcd(b,a%b):a;
	}
	void Query(int u,int v){
		if(find_root(u)!=find_root(v)){
			puts("-1");
			return;
		}
		make_root(u);
		Access(v);
		Splay(v);
		ull a=exp[v],
			b=sz[v]*(sz[v]+1)>>1,
			d=gcd(a,b);
		printf("%llu/%llu\n",a/d,b/d);
	}
	void Add(int u,int v,ull d){
		if(find_root(u)!=find_root(v))return;
		make_root(u);
		Access(v);
		Splay(v);
		update_add(v,d);
	}
}lct;
inline void add_edge(int from,int to){
	edge[tot_edge]=(Edge){to,head[from]};
	head[from]=tot_edge++;
}
int main(){
	int n,m,ope,u,v;
	ull d;
	scanf("%d%d",&n,&m);
	lct.clear();
	for(int i=1;i<=n;++i){
		scanf("%llu",&val[i]);
		lct.push_up(i);
	}
	tot_edge=0;
	memset(head,-1,n+1<<2);
	for(int i=1;i<n;++i){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	lct.init();
	while(m--&&scanf("%d%d%d",&ope,&u,&v)){
		switch(ope){
			case 1:
				lct.cut(u,v);
				break;
			case 2:
				lct.link(u,v);
				break;
			case 3:
				scanf("%llu",&d);
				lct.Add(u,v,d);
				break;
			case 4:
				lct.Query(u,v);
				break;
		}
	}
	return 0;
}
/*
	
	May.07.16
	
	Tags:LCT,Mathematics
	Submissions:10
	
	Memory 10108kb
	Time 3276ms
	Code Length 4470B
	
*/
