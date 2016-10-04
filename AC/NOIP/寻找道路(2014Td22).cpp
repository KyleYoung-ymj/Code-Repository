#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1e4+5,INF=1e8;
void Rd(int &res){
	res=0;
	char c;
	while(c=getchar(),!isdigit(c));
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),isdigit(c));
}
vector<int>G[2][N];
bool used[N]={0},flag[N]={0};
void dfs(int now){
	used[now]=flag[now]=true;
	int sz=G[1][now].size();
	for(int i=0;i<sz;++i){
		int to=G[1][now][i];
		if(used[to])continue;
		dfs(to);
	}
}
struct Pair{
	int dist,node;
	bool operator <(const Pair &tmp)const{
		return dist>tmp.dist;
	}
};
bool cant[N]={0};
int dist[N];
priority_queue<Pair>pque;
void Dijkstra(int n,int s){
	memset(dist,-1,sizeof(dist));
	if(cant[s])return;
	while(!pque.empty())pque.pop();
	pque.push((Pair){dist[s]=0,s});
	while(!pque.empty()){
		Pair p=pque.top();
		pque.pop();
		int u=p.node;
		if(dist[u]<p.dist)continue;
		int sz=G[0][u].size();
		for(int i=0;i<sz;++i){
			int v=G[0][u][i];
			if(cant[v])continue;
			if(dist[v]==-1||dist[v]>dist[u]+1)
				pque.push((Pair){dist[v]=dist[u]+1,v});
		}
	}
}
int main(){
//	freopen("road.in","r",stdin);
//	freopen("road.out","w",stdout);
	int n,m,x,y,s,t;
	Rd(n);Rd(m);
	for(int i=0;i<2;++i)
		for(int j=1;j<=n;++j)
			G[i][j].clear();
	while(m--){
		Rd(x);Rd(y);
		G[0][x].push_back(y);
		G[1][y].push_back(x);
	}
	Rd(s);Rd(t);
	dfs(t);
	for(int i=1;i<=n;++i)
		if(!flag[i]){
			int sz=G[1][i].size();
			for(int j=0;j<sz;++j)
				cant[G[1][i][j]]=true;
		}
	Dijkstra(n,s);
	printf("%d\n",dist[t]);
	return 0;
}
/*
	
	Oct.28.15
	Score 100
	
	Memory 4128K
	Time 78MS
	Code Length 1.60K
	
*/
