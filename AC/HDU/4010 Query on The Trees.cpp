#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=3e5+5,NEG_INF=0x80000000;
int n,tot_edge,head[N],val[N],mx[N];
struct Edge{
	int to,nxt;
}edge[N<<1];
struct LCT{
	int par[N],ch[N][2],extra[N],stk[N];
	bool flip[N];
	void dfs(int x){
		for(int i=head[x];~i;i=edge[i].nxt){
			int to=edge[i].to;
			if(to==par[x])continue;
			par[to]=x;
			dfs(to);
		}
	}
	void init(){
		par[1]=0;
		memset(ch,0,sizeof(ch));
		memset(extra,0,n+1<<2);
		memset(flip,false,n+1);
		dfs(1);
	}
	inline void Max(int &a,int b){
		if(b>a)a=b;
	}
	inline void push_up(int k){
		mx[k]=max(mx[ch[k][0]],mx[ch[k][1]]);
		Max(mx[k],val[k]);
	}
	void push_down(int k){
		if(flip[k]){
			swap(ch[k][0],ch[k][1]);
			flip[ch[k][0]]^=1;
			flip[ch[k][1]]^=1;
			flip[k]=false;
		}
		if(extra[k]){
			for(int i=0;i<2;++i){
				int son=ch[k][i];
				if(son){
					extra[son]+=extra[k];
					val[son]+=extra[k];
					mx[son]+=extra[k];
				}
			}
			extra[k]=0;
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
		ch[x][f]=y;
		par[y]=x;
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
		flip[x]^=1;
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
		if(find_root(u)==find_root(v)){
			puts("-1");
			return;
		}
		make_root(u);
		par[u]=v;
		Access(u);
	}
	void cut(int u,int v){
		if(u==v||find_root(u)!=find_root(v)){
			puts("-1");
			return;
		}
		make_root(u);
		Access(v);
		Splay(v);
		ch[v][0]=par[ch[v][0]]=0;
		push_up(v);
	}
	void add(int x,int u,int v){
		if(find_root(u)!=find_root(v)){
			puts("-1");
			return;
		}
		make_root(u);
		Access(v);
		Splay(v);
		extra[v]+=x;
		val[v]+=x;
		mx[v]+=x;
	}
	int query_mx(int u,int v){
		if(find_root(u)!=find_root(v))return -1;
		make_root(u);
		Access(v);
		Splay(v);
		return mx[v];
	}
}lct;
inline void add_edge(int from,int to){
	edge[tot_edge]=(Edge){to,head[from]};
	head[from]=tot_edge++;
}
int main(){
	int m,ope,a,b,c;
	mx[0]=NEG_INF;
	while(~scanf("%d",&n)){
		tot_edge=0;
		memset(head,-1,n+1<<2);
		for(int i=1,u,v;i<n;++i){
			scanf("%d%d",&u,&v);
			add_edge(u,v);
			add_edge(v,u);
		}
		for(int i=1;i<=n;++i){
			scanf("%d",&val[i]);
			mx[i]=val[i];
		}
		lct.init();
		scanf("%d",&m);
		while(m--&&~scanf("%d%d%d",&ope,&a,&b)){
			switch(ope){
				case 1:
					lct.link(a,b);
					break;
				case 2:
					lct.cut(a,b);
					break;
				case 3:
					scanf("%d",&c);
					lct.add(a,b,c);
					break;
				case 4:
					printf("%d\n",lct.query_mx(a,b));
					break;
			}
		}
		putchar('\n');
	}
	return 0;
}
/*
	
	May.02.16
	
	Tags:LCT
	Submissions:1
	
	Exe.Time 1310MS
	Exe.Memory 7452K
	Code Len. 3483B
	
*/
