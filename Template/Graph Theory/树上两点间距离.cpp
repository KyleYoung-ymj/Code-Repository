#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1e5+5,LG=20;
struct edge{
	int to,cost;
};
vector<edge>G[N];
int rank[N],dist[N],par[N][LG];
void dfs(int now,int pre,int dis){
	rank[now]=rank[pre]+1;
	par[now][0]=pre;
	dist[now]=dis;
	int sz=G[now].size();
	for(int i=0;i<sz;++i){
		int to=G[now][i].to,cost=G[now][i].cost;
		if(to==pre)continue;
		dfs(to,now,dis+cost);
	}
}
int up(int x,int step){
	for(int i=0;i<LG;++i)
		if(step&1<<i)
			x=par[x][i];
	return x;
}
int lca(int a,int b){
	if(rank[b]<rank[a])swap(a,b);
	b=up(b,rank[b]-rank[a]);
	if(a==b)return a;
	for(int i=LG-1;i>=0;--i)
		if(par[a][i]!=par[b][i]){
			a=par[a][i];
			b=par[b][i];
		}
	return par[a][0];
}
int main(){
	int n,m,a,b,c;
	scanf("%d %d",&n,&m);
	for(int i=0;i<n-1;++i){
		scanf("%d %d %d",&a,&b,&c);
		G[a].push_back((edge){b,c});
		G[b].push_back((edge){a,c});
	}
	rank[0]=0;
	for(int i=0;i<LG;++i)
		par[0][i]=0;
	dfs(1,0,0);
	for(int i=1;i<LG;++i)
		for(int j=1;j<=n;++j)
			par[j][i]=par[par[j][i-1]][i-1];
	while(m--){
		scanf("%d %d",&a,&b);
		printf("%d\n",dist[a]+dist[b]-(dist[lca(a,b)]<<1));
	}
	return 0;
}
