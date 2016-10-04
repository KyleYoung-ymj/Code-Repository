#include<cstdio>
#include<algorithm>
using namespace std;
const int N=32800,INF=1e9;
struct SplayTree{
	int sz,root,ch[N][2],par[N],val[N];
	inline void clear(){
		sz=root=0;
	}
	void NewNode(int &now,int fa,int v){
		now=++sz;
		par[now]=fa;
		ch[now][0]=ch[now][1]=0;
		val[now]=v;
	}
	void rotate(int x,bool f){
		int y=par[x];
		par[ch[x][f]]=y;
		ch[y][!f]=ch[x][f];
		par[x]=par[y];
		if(par[y])ch[par[y]][ch[par[y]][1]==y]=x;
		par[y]=x;
		ch[x][f]=y;
	}
	void Splay(int x,int goal=0){
		while(par[x]!=goal){
			int y=par[x];
			if(par[y]==goal)rotate(x,ch[y][0]==x);
			else{
				bool flag=ch[par[y]][0]==y;
				if(ch[y][flag]==x){
					rotate(x,!flag);
					rotate(x,flag);
				}
				else{
					rotate(y,flag);
					rotate(x,flag);
				}
			}
		}
		if(!goal)root=x;
	}
	bool insert(int x){
		int cur=root;
		for(;ch[cur][x>val[cur]];cur=ch[cur][x>val[cur]])
			if(val[cur]==x){
				Splay(cur);
				return false;
			}
		NewNode(ch[cur][x>val[cur]],cur,x);
		Splay(ch[cur][x>val[cur]]);
		return true;
	}
	int Get_Pre(){
		int x=ch[root][0];
		if(!x)return INF;
		while(ch[x][1])x=ch[x][1];
		return val[x];
	}
	int Get_Next(){
		int x=ch[root][1];
		if(!x)return INF;
		while(ch[x][0])x=ch[x][0];
		return val[x];
	}
}T;
int main(){
	int n,ans,tmp;
	while(~scanf("%d%d",&n,&ans)){
		T.clear();
		T.NewNode(T.root,0,ans);
		for(int i=1;i<n;++i){
			scanf("%d",&tmp);
			if(T.insert(tmp)){
				int a=T.Get_Pre(),b=T.Get_Next();
				if(a!=INF)a=tmp-a;
				if(b!=INF)b=b-tmp;
				ans+=min(a,b);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	Feb.04.16
	
	Tags:Data Structure,Splay,classic
	Submissions:1
	
	Time 187MS
	Memory 700K
	Code Length 1626Byte
	
*/
