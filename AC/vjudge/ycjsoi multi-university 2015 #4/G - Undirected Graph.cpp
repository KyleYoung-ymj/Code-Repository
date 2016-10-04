#include<cstdio>
#include<cassert>
#include<cstring>
#include<algorithm>
#define lowbit(x) (x&-x)
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
const int N=1e5+5,M=2e5+5,Q=1e5+5,NODE=N+M,INF=1e9;
int n,m,bit[N],ans[Q],val[NODE];
pii edge[M];
struct Query{
	int L,R,id;
	inline bool operator <(const Query &tmp)const{
		return R<tmp.R;
	}
}query[Q];
struct LCT{
	int par[NODE],ch[NODE][2],mi[NODE],stk[NODE];
	bool flip[NODE];
	void clear(){
		memset(ch,0,sizeof(ch));
		memset(par,0,n+m+1<<2);
		memset(flip,false,n+m+1);
		for(int i=1;i<=n+m;++i)
			mi[i]=i;
	}
	void push_up(int k){
		mi[k]=k;
		for(int i=0;i<2;++i)
			if(ch[k][i]&&val[mi[ch[k][i]]]<val[mi[k]])mi[k]=mi[ch[k][i]];
	}
	void push_down(int k){
		if(!flip[k])return;
		swap(ch[k][0],ch[k][1]);
		flip[ch[k][0]]^=1;
		flip[ch[k][1]]^=1;
		flip[k]=false;
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
	void make_root(int x){
		Access(x);
		Splay(x);
		flip[x]^=1;
	}
	void link(int u,int v){
		make_root(u);
		par[u]=v;
		Access(u);
	}
	void cut(int u,int v){
		make_root(u);
		Access(v);
		Splay(v);
		assert(ch[v][0]==u&&par[u]==v);
		ch[v][0]=par[u]=0;
		push_up(v);
	}
	int query_mi(int u,int v){
		make_root(u);
		Access(v);
		Splay(v);
		return mi[v];
	}
}lct;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
void add(int x,int v){
	while(x<=n){
		bit[x]+=v;
		x+=lowbit(x);
	}
}
int sum(int x){
	int res=0;
	while(x){
		res+=bit[x];
		x-=lowbit(x);
	}
	return res;
}
void print(int x){
	if(!x)return;
	print(x/10);
	putchar(x%10^48);
}
void solve(){
	int q;
	rd(m);rd(q);
	for(int i=1;i<=n;++i){
		val[i]=INF;
		bit[i]=0;
	}
	int a,b;
	for(int i=0;i<m;++i){
		rd(a);rd(b);
		if(a>b)swap(a,b);
		edge[i]=pii(b,a);
	}
	sort(edge,edge+m);
	for(int i=0;i<q;++i){
		rd(query[i].L);rd(query[i].R);
		query[i].id=i;
	}
	sort(query,query+q);
	lct.clear();
	for(int i=0,j=0,tot=0;i<q;++i){
		while(j<m&&edge[j].fi<=query[i].R){
			int u=edge[j].fi,v=edge[j].se,id=++j+n;
			val[id]=v;
			if(lct.find_root(u)!=lct.find_root(v)){
				lct.link(u,id);
				lct.link(v,id);
				add(v,1);
				++tot;
			}
			else{
				int mi=lct.query_mi(u,v);
				if(val[mi]<val[id]){
					lct.cut(mi,edge[mi-n-1].fi);
					lct.cut(mi,edge[mi-n-1].se);
					add(edge[mi-n-1].se,-1);
					lct.link(u,id);
					lct.link(v,id);
					add(v,1);
				}
			}
		}
		ans[query[i].id]=n-(tot-sum(query[i].L-1));
	}
	for(int i=0;i<q;++i,putchar('\n'))
		print(ans[i]);
}
int main(){
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	Jun.25.16
	
	Tags:graph theory,lct,bit
	Submissions:4
	
	Memory(KB) 12336KB
	Time(ms) 1716ms
	Length(Bytes) 3427B
	
*/
