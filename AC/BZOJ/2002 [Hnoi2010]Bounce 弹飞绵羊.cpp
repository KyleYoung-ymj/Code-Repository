#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e5+5;
int val[N];
struct LCT{
	int par[N],ch[N][2],sz[N],stk[N];
	inline void init(){
		sz[0]=0;
		memset(par,0,sizeof(par));
		memset(ch,0,sizeof(ch));
	}
	inline void push_up(int k){
		sz[k]=sz[ch[k][0]]+sz[ch[k][1]]+1;
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
	void Splay(int x){
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
	void link(int u,int v){
		Access(u);
		par[u]=v;
		Access(u);
	}
	void cut(int u){
		Access(u);
		Splay(u);
		ch[u][0]=par[ch[u][0]]=0;
		push_up(u);
	}
	int query_dep(int u){
		Access(u);
		Splay(u);
		return sz[u];
	}
}lct;
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
int main(){
	int n,m,ope,a,b;
	rd(n);
	lct.init();
	for(int i=1;i<=n;++i){
		rd(val[i]);
		if(i+val[i]<=n)lct.link(i,i+val[i]);
	}
	rd(m);
	while(m--){
		rd(ope);rd(a);
		++a;
		if(ope==1){
			printf("%d\n",lct.query_dep(a));
		}
		else{
			rd(b);
			if(a+val[a]<=n)lct.cut(a);
			val[a]=b;
			if(a+val[a]<=n)lct.link(a,a+val[a]);
		}
	}
	return 0;
}
/*
	
	May.03.16
	
	Tags:LCT
	Submissions:4
	
	Memory 5504kb
	Time 1328ms
	Code Length 1937B
	
*/
