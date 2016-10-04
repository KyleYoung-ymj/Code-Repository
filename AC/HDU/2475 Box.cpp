#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=5e4+5,M=N<<1;
int tot,n,order[M],Lid[N],Rid[N];
vector<int>son[N];
void dfs(int cur){
	order[tot++]=cur;
	for(int i=0;i<son[cur].size();++i)
		dfs(son[cur][i]);
	order[tot++]=-cur;
}
struct Splay_Tree{
	int allc,root,par[M],ch[M][2],val[M];
	// root is meaningless
	inline void clear(){
		allc=tot=0;
	}
	void NewNode(int &cur,int v,int fa){
		cur=++allc;
		par[cur]=fa;
		val[cur]=abs(v);
		if(v>0)Lid[v]=cur;
		else Rid[-v]=cur;
	}
	void construct(int L,int R,int &cur,int fa){
		if(L>R){
			cur=0;
			return;
		}
		int mid=L+R>>1;
		NewNode(cur,order[mid],fa);
		construct(L,mid-1,ch[cur][0],cur);
		construct(mid+1,R,ch[cur][1],cur);
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
				if(ch[y][flag]==x)rotate(x,!flag);
				else rotate(y,flag);
				rotate(x,flag);
			}
		}
	}
	int get_mi(int cur){
		for(;ch[cur][0];cur=ch[cur][0]);
		return cur;
	}
	int get_mx(int cur){
		for(;ch[cur][1];cur=ch[cur][1]);
		return cur;
	}
	int query(int x){
		Splay(Lid[x]);
		return val[get_mi(Lid[x])];
	}
	void move(int x,int y){
		// move x to y
		if(x==y)return;
		Splay(Lid[x]);
		Splay(Rid[x]);
		int L=ch[Lid[x]][0],R=ch[Rid[x]][1],
			pre=get_mx(L);
		par[L]=par[R]=ch[Lid[x]][0]=ch[Rid[x]][1]=0;
		ch[pre][1]=R;
		par[R]=pre;
		// split the subtree rooted by x from the SplayTree
		if(!y)return;
		if(query(y)==x){
			// y is in the subtree
			ch[pre][1]=par[R]=0;
			par[L]=Lid[x];
			par[R]=Rid[x];
			ch[Lid[x]][0]=L;
			ch[Rid[x]][1]=R;
			return;
		}
		Splay(Lid[y]);
		int nxt=get_mi(ch[Lid[y]][1]);
		ch[nxt][0]=Rid[x];
		par[Rid[x]]=nxt;
	}
	void solve(){
		clear();
		for(int i=0;i<son[0].size();++i)
			dfs(son[0][i]);
		int cnt=0,ptr=0;
		for(int i=0;i<tot;++i){
			if(order[i]>0)++cnt;
			else if(!(--cnt)){
				construct(ptr,i,root,0);
				ptr=i+1;
			}
		}
		int m,x,y;
		char str[10];
		scanf("%d",&m);
		while(m--&&~scanf("%s%d",str,&x)){
			if(str[0]=='Q')printf("%d\n",query(x));
			else{
				scanf("%d",&y);
				move(x,y);
			}
		}
	}
}T;
int main(){
	bool first=true;
	while(~scanf("%d",&n)){
		if(first)first=false;
		else putchar('\n');
		for(int i=0;i<=n;++i)
			son[i].clear();
		int tmp;
		for(int i=1;i<=n;++i){
			scanf("%d",&tmp);
			son[tmp].push_back(i);
		}
		T.solve();
	}
	return 0;
}
/*
	
	Feb.24.16
	
	Tags:Splay,Dynamic Tree,dfs
	Submissions:1
	
	Exe.Time 1248MS
	Exe.Memory 8592K
	Code Len. 2723B
	
*/
