#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5e3+5,M=5e4+5,V=N+M,E=N+3*M,INF=0x7fffffff;
int src,sink,tot_edge,
    head[V],dist[V],arc[V],que[V];
bool used[V];
struct Edge{
	int to,cap,nxt;
}edge[E<<1];
void add_edge(int from,int to,int c){
	edge[tot_edge]=(Edge){to,c,head[from]};
	head[from]=tot_edge++;
	edge[tot_edge]=(Edge){from,0,head[to]};
	head[to]=tot_edge++;
}
void bfs(){
	int L=0,R=0;
	for(int i=src;i<=sink;++i)
		dist[i]=-1;
	dist[que[R++]=src]=0;
	while(L<R){
		int cur=que[L++];
		for(int i=head[cur];~i;i=edge[i].nxt){
			int to=edge[i].to;
			if(edge[i].cap&&dist[to]==-1){
				dist[to]=dist[cur]+1;
				que[R++]=to;
			}
		}
	}
}
int dfs(int cur,int f){
	if(cur==sink)return f;
	used[cur]=true;
	for(int &i=arc[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(!used[to]&&edge[i].cap&&dist[to]==dist[cur]+1){
			int d=dfs(to,min(f,edge[i].cap));
			if(d){
				edge[i].cap-=d;
				edge[i^1].cap+=d;
				return d;
			}
		}
	}
	return 0;
}
int Dinic(){
	int flow=0;
	while(true){
		bfs();
		if(dist[sink]==-1)return flow;
		for(int i=src;i<=sink;++i)
			arc[i]=head[i];
		while(true){
			for(int i=src;i<=sink;++i)
				used[i]=false;
			int f=dfs(src,INF);
			if(!f)break;
			flow+=f;
		}
	}
}
int main(){
	int n,m,tot_val=0;
	scanf("%d%d",&n,&m);
	src=0;
	sink=n+m+1;
	tot_edge=0;
	memset(head,-1,sizeof(head));
	for(int i=1,tmp;i<=n;++i){
		scanf("%d",&tmp);
		add_edge(m+i,sink,tmp);
	}
	for(int i=1,a,b,c;i<=m;++i){
		scanf("%d%d%d",&a,&b,&c);
		tot_val+=c;
		add_edge(src,i,c);
		add_edge(i,m+a,INF);
		add_edge(i,m+b,INF);
	}
	printf("%d\n",tot_val-Dinic());
	return 0;
}
/*
	
	Mar.09.16
	
	Tags:Minimum Cut,Network Flow
	Submissions:1
	
	Memory 5352kb
	Time 3704ms
	Code Length 1901B
	
*/
