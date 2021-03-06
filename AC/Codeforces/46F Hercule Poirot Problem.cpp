#include<cstdio>
#include<cstring>
#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;
const int N=1e3+5;
int n,m,K,tot_edge,head[N],par[2][N*3];
bool flag,update,vis[N];
string str;
map<string,int>mp;
struct Edge{
	int to,nxt,id;
}edge[N<<1];
inline void add_edge(int from,int to,int id){
	edge[tot_edge]=(Edge){to,head[from],id};
	head[from]=tot_edge++;
}
int get_root(int x){
	return par[flag][x]==x?x:par[flag][x]=get_root(par[flag][x]);
}
void unite(int u,int v){
	u=get_root(u);
	v=get_root(v);
	par[flag][u]=v;
}
bool same(bool mark,int u,int v){
	flag=mark;
	return get_root(u)==get_root(v);
}
bool judge(int tot){
	for(int i=1;i<=tot;++i)
		for(int j=1;j<=tot;++j){
			if(same(0,i,j)!=same(1,i,j))
				return false;
		}
	return true;
}
void dfs(int cur){
	vis[cur]=true;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to,id=edge[i].id;
		if(vis[to]||get_root(K+n+id)!=get_root(K+cur))continue;
		if(!same(flag,K+cur,K+to))update=true;
		unite(K+cur,K+to);
		dfs(to);
	}
}
void search(int cur){
	while(true){
		update=false;
		memset(vis,false,sizeof(vis));
		dfs(cur);
		if(!update)return;
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1,tot=n+m+K;i<=tot;++i)
		par[0][i]=par[1][i]=i;
	tot_edge=0;
	memset(head,-1,n+1<<2);
	for(int i=1,u,v;i<=m;++i){
		scanf("%d%d",&u,&v);
		add_edge(u,v,i);
		add_edge(v,u,i);
	}
	mp.clear();
	flag=0;
	for(int i=1,loc,tot,key;i<=K;++i){
		cin>>str;
		mp[str]=i;
		scanf("%d%d",&loc,&tot);
		unite(i,K+loc);
		while(tot--&&scanf("%d",&key))
			unite(i,K+n+key);
		search(loc);
	}
	flag=1;
	for(int i=1,loc,tot,key;i<=K;++i){
		cin>>str;
		int id=mp[str];
		scanf("%d%d",&loc,&tot);
		unite(id,K+loc);
		while(tot--&&scanf("%d",&key))
			unite(id,K+n+key);
		search(loc);
	}
	puts(judge(n+m+K)?"YES":"NO");
	return 0;
}
/*
	
	May.27.16
	
	Tags:dsu,Graph,brute force
	Submissions:4
	
	Time 374ms
	Memory 2300KB
	
*/
