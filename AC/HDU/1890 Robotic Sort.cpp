#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,cnt[N],pos[N],num[N],mp[N];
struct Splay_Tree{
	int allc,root,par[N],ch[N][2],sz[N];
	bool flip[N];
	inline void clear(){
		allc=root=sz[0]=0;
	}
	inline void push_up(int k){
		sz[k]=sz[ch[k][0]]+sz[ch[k][1]]+1;
	}
	void push_down(int k){
		if(!flip[k])return;
		swap(ch[k][0],ch[k][1]);
		flip[ch[k][0]]^=1;
		flip[ch[k][1]]^=1;
		flip[k]=false;
	}
	void rotate(int x,bool f){
		int y=par[x];
		push_down(y);
		push_down(x);
		par[ch[x][f]]=y;
		ch[y][!f]=ch[x][f];
		par[x]=par[y];
		if(par[y])ch[par[y]][ch[par[y]][1]==y]=x;
		par[y]=x;
		ch[x][f]=y;
		push_up(y);
	}
	void Splay(int x,int goal=0){
		push_down(x);
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
		if(!goal)root=x;
		push_up(x);
	}
	void construct(int L,int R,int &cur,int fa){
		if(L>R){
			cur=0;
			return;
		}
		cur=++allc;
		par[cur]=fa;
		flip[cur]=false;
		int mid=L+R>>1;
		pos[num[mid]]=cur;
		construct(L,mid-1,ch[cur][0],cur);
		construct(mid+1,R,ch[cur][1],cur);
		push_up(cur);
	}
	int get_pre(){
		int cur=ch[root][0];
		while(true){
			push_down(cur);//must push_down first
			if(ch[cur][1])cur=ch[cur][1];
			else break;
		}
		return cur;
	}
	void del_root(){
		push_down(root);
		if(!ch[root][0]||!ch[root][1]){
			root=ch[root][0]+ch[root][1];
			par[root]=0;
			return;
		}
		int tar=get_pre();
		Splay(tar,root);
		par[ch[root][1]]=tar;
		ch[tar][1]=ch[root][1];
		par[root=tar]=0;
		push_up(root);
	}
	inline void Reverse(int x){
		flip[x]^=1;
	}
	void update(int x){
		if(!x)return;
		update(par[x]);
		push_down(x);
	}
	void debug(int x){
		if(!x)return;
		printf("#%d %d %d %d %d\n",x,par[x],ch[x][0],ch[x][1],sz[x]);
		debug(ch[x][0]);
		debug(ch[x][1]);
	}
	void solve(){
		clear();
		construct(0,n-1,root,0);
		for(int i=0;i<n;++i){
			update(par[pos[i]]);
			Splay(pos[i]);
//			debug(root);//
			printf("%d%c",i+1+sz[ch[root][0]],i==n-1?'\n':' ');
			Reverse(ch[root][0]);
			del_root();
		}
	}
}T;
int main(){
	while(~scanf("%d",&n)&&n){
		for(int i=0;i<n;++i){
			scanf("%d",&num[i]);
			mp[i]=num[i];
		}
		sort(mp,mp+n);
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<n;++i){
			num[i]=lower_bound(mp,mp+n,num[i])-mp;
			num[i]+=cnt[num[i]]++;
		}
		T.solve();
	}
	return 0;
}
/*
	
	Feb.20.16
	
	Tags:Splay
	Submissions:1
	
	Exe.Time 374MS
	Exe.Memory 4656K
	Code Len. 2552B
	
*/
