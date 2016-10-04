#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef pair<int,int> P;
const int N=10005,INF=1000000000;
struct edge{
	int to,cost;
};
edge make_edge(int a,int b){
	edge res;
	res.to=a;
	res.cost=b;
	return res;
}
int dist[N];
vector<edge>G[N];
priority_queue<P,vector<P>,greater<P> >pque;
void Dijkstra(int n,int s){
	fill(dist,dist+n,INF);
	dist[s]=0;
	pque.push(P(0,s));
	while(!pque.empty()){
		P p=pque.top();pque.pop();
		int u=p.second;
		if(dist[u]<p.first)continue;
		for(int i=0;i<G[u].size();++i){
			int v=G[u][i].to,c=G[u][i].cost;
			if(dist[v]>dist[u]+c){
				dist[v]=dist[u]+c;
				pque.push(P(dist[v],v));
			}
		}
	}
}
int main(){
	int n,m,s,t,x,y,z;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	--s;
	--t;
	while(m--){
		scanf("%d%d%d",&x,&y,&z);
		--x;
		--y;
		G[x].push_back(make_edge(y,z));
	}
	Dijkstra(n,s);
	if(dist[t]==INF)dist[t]=-1;
	printf("%d\n",dist[t]);
	return 0;
}
/*
	
	Oct.15.15
	
*/
