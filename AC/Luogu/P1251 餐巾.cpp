#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e3+5,V=N<<1,E=6*N,INF=1e9;
typedef long long ll;
int src,sink,tot_edge,
	head[V],dist[V],flow[V],pre[V],pre_edge[V],que[V*100],
	need[N];
bool in_que[V];
struct Edge{
	int to,cap,cost,nxt;
}edge[E<<1];
void add_edge(int from,int to,int c,int cost){
	edge[tot_edge]=(Edge){to,c,cost,head[from]};
	head[from]=tot_edge++;
	edge[tot_edge]=(Edge){from,0,-cost,head[to]};
	head[to]=tot_edge++;
}
void SPFA(){
	int L=0,R=0;
	for(int i=src;i<=sink;++i){
		dist[i]=INF;
		in_que[i]=false;
	}
	dist[que[R++]=src]=0;
	flow[src]=INF;
	in_que[src]=true;
	while(L<R){
		int cur=que[L++];
		in_que[cur]=false;
		for(int i=head[cur];~i;i=edge[i].nxt){
			int to=edge[i].to;
			if(edge[i].cap&&dist[to]>dist[cur]+edge[i].cost){
				dist[to]=dist[cur]+edge[i].cost;
				pre[to]=cur;
				pre_edge[to]=i;
				flow[to]=min(flow[cur],edge[i].cap);
				if(!in_que[to]){
					que[R++]=to;
					in_que[to]=true;
				}
			}
		}
	}
}
ll mincost_maxflow(){
	ll tot_cost=0;
	while(true){
		SPFA();
		if(dist[sink]==INF)return tot_cost;
		tot_cost+=1ll*dist[sink]*flow[sink];
		int cur=sink;
		while(cur!=src){
			edge[pre_edge[cur]].cap-=flow[sink];
			edge[pre_edge[cur]^1].cap+=flow[sink];
			cur=pre[cur];
		}
	}
}
int main(){
	int n;
	scanf("%d",&n);
	src=0;
	sink=(n<<1)+1;
	tot_edge=0;
	memset(head,-1,sizeof(head));
	for(int i=1;i<=n;++i)
		scanf("%d",&need[i]);
	int a,b,c,d,e;
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
	for(int i=1;i<=n;++i){
		add_edge(src,i,need[i],0);
		add_edge(i+n,sink,need[i],0);
		add_edge(src,i+n,INF,a);
		if(i<n)add_edge(i,i+1,INF,0);
		if(i+b<=n)add_edge(i,i+b+n,INF,c);
		if(i+d<=n)add_edge(i,i+d+n,INF,e);
	}
	printf("%lld\n",mincost_maxflow());
	return 0;
}
/*
	
	Mar.13.16
	
	Tags:mincost_maxflow,classic
	Submissions:2
	
	Time 3399ms
	Memory 2.42Mb
	Code Length 1.71kb
	
*/
