#include<cstdio>
#include<cstring>
const int N=(int)1e3+5,M=(int)1e4+5,INF=(int)1e9;
int n,tot_edge,dist[N];
struct Edge{
	int from,to,cost;
	Edge(){}
	Edge(int from,int to,int cost):from(from),to(to),cost(cost){}
}edge[N+(M<<1)];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
bool Bellman_Ford(){
	for(int i=0;i<n;++i)
		dist[i]=INF;
	dist[0]=0;
	for(int i=0;i<n;++i){
		bool update=false;
		for(int j=0;j<tot_edge;++j){
			int u=edge[j].from,v=edge[j].to,cost=edge[j].cost;
			if(dist[v]>dist[u]+cost){
				if(i==n-1)return false;
				dist[v]=dist[u]+cost;
				update=true;
			}
		}
		if(!update)break;
	}
	return true;
}
int main(){
	int m1,m2,u,v,dis;
	rd(n);rd(m1);rd(m2);
	tot_edge=0;
	for(int i=1;i<n;++i){
		edge[tot_edge++]=Edge(i,i-1,0);
	}
	while(m1--){
		rd(u);rd(v);rd(dis);
		edge[tot_edge++]=Edge(u-1,v-1,dis);
	}
	while(m2--){
		rd(u);rd(v);rd(dis);
		edge[tot_edge++]=Edge(v-1,u-1,-dis);
	}
	if(!Bellman_Ford())puts("-1");
	else if(dist[n-1]==INF)puts("-2");
	else printf("%d\n",dist[n-1]);
	return 0;
}
/*
	
	Jul.10.16

	Tags:system of difference constraints
	Submissions:1

	Memory 520K
	Time 0MS
	Code Length 1100B

*/
