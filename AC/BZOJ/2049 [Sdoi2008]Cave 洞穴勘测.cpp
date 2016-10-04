#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e4+5;
struct LCT{
	int par[N],ch[N][2],stk[N];
	bool flip[N];
	inline void init(){
		memset(par,0,sizeof(par));
		memset(ch,0,sizeof(ch));
		memset(flip,false,sizeof(flip));
	}
	void push_down(int k){
		if(!flip[k])return;
		swap(ch[k][0],ch[k][1]);
		flip[ch[k][0]]^=1;
		flip[ch[k][1]]^=1;
		flip[k]=false;
	}
	inline bool is_root(int k){
		return ch[par[k]][0]!=k&&ch[par[k]][1]!=k;
	}
	void rotate(int x,bool f){
		int y=par[x];
		par[ch[x][f]]=y;
		ch[y][!f]=ch[x][f];
		par[x]=par[y];
		if(!is_root(y))ch[par[y]][ch[par[y]][1]==y]=x;
		par[y]=x;
		ch[x][f]=y;
	}
	void update(int x){
		int top=0;
		stk[top++]=x;
		for(int i=x;!is_root(i);i=par[i])
			stk[top++]=par[i];
		for(int i=top-1;~i;--i)
			push_down(stk[i]);
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
		int y=0;
		while(x){
			Splay(x);
			ch[x][1]=y;
			y=x;
			x=par[x];
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
		ch[v][0]=par[u]=0;
	}
	int find_root(int x){
		Access(x);
		Splay(x);
		for(int cur=x;;cur=ch[cur][0]){
			if(!ch[cur][0]){
				Splay(cur);
				return cur;
			}
		}
	}
}lct;
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>=48);
}
int main(){
	int n,m,u,v;
	char str[10];
	rd(n);rd(m);
	lct.init();
	while(m--&&~scanf("%s",str)){
		rd(u);rd(v);
		switch(str[0]){
			case 'C':
				lct.link(u,v);
				break;
			case 'D':
				lct.cut(u,v);
				break;
			case 'Q':
				puts(lct.find_root(u)==lct.find_root(v)?"Yes":"No");
				break;
		}
	}
	return 0;
}
/*
	
	May.02.16
	
	Tags:LCT
	Submissions:1
	
	Memory 984kb
	Time 1556ms
	Code Length 2352B
	
*/
