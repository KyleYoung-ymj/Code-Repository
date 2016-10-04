#include<cstdio>
const int N=1e5+5;
struct Splay_Tree{
	int sz,root,ans,par[N],ch[N][2],val[N],cnt[N],sum[N];
	inline void clear(){
		sz=root=ans=0;
	}
	void NewNode(int &now,int fa,int v){
		now=++sz;
		par[now]=fa;
		ch[now][0]=ch[now][1]=0;
		sum[now]=cnt[now]=1;
		val[now]=v;
	}
	inline void up(int x){
		sum[x]=cnt[x]+sum[ch[x][0]]+sum[ch[x][1]];
	}
	void rotate(int x,bool f){
		int y=par[x];
		par[ch[x][f]]=y;
		ch[y][!f]=ch[x][f];
		par[x]=par[y];
		if(par[y])ch[par[y]][ch[par[y]][1]==y]=x;
		par[y]=x;
		ch[x][f]=y;
		up(y);
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
		up(x);
		if(!goal)root=x;
	}
	void insert(int x){
		if(!root){
			NewNode(root,0,x);
			return;
		}
		int cur=root;
		for(;ch[cur][x>val[cur]];cur=ch[cur][x>val[cur]])
			if(val[cur]==x){
				++cnt[cur];
				++sum[cur];
				Splay(cur);
				return;
			}
		NewNode(ch[cur][x>val[cur]],cur,x);
		Splay(ch[cur][x>val[cur]]);
	}
	int get_pre(int x){
		int cur=root,res=-1;
		while(cur){
			if(val[cur]<x){
				res=cur;
				cur=ch[cur][1];
			}
			else cur=ch[cur][0];
		}
		return res;
	}
	void del(int lim){
		int cur=get_pre(lim);
		if(cur==-1)return;
		Splay(cur);
		ans+=sum[ch[cur][0]]+cnt[cur];
		root=ch[cur][1];
		par[root]=0;
	}
	int find_kth(int k,int cur){
		if(sum[ch[cur][1]]>=k)return find_kth(k,ch[cur][1]);
		if(k>sum[ch[cur][1]]+cnt[cur])return find_kth(k-sum[ch[cur][1]]-cnt[cur],ch[cur][0]);
		return val[cur];
	}
}T;
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>=48);
}
int main(){
	int n,m,k,extra=0;
	char str[5];
	rd(n);rd(m);
	T.clear();
	while(n--&&~scanf("%s",str)){
		rd(k);
		switch(str[0]){
			case 'I':
				if(k>=m)T.insert(k-extra);
				break;
			case 'A':
				extra+=k;
				break;
			case 'S':
				extra-=k;
				T.del(m-extra);
				break;
			case 'F':
				printf("%d\n",!T.root||T.sum[T.root]<k?-1:T.find_kth(k,T.root)+extra);
				break;
		}
	}
	printf("%d\n",T.ans);
	return 0;
}
/*
	
	Feb.17.16
	
	Tags:Data Structure,Splay
	Submissions:1
	
	Time 682ms
	Memory 3.87Mb
	Code Length 2.17kb
	
*/
