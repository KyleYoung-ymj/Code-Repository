#include<cstdio>
#include<algorithm>
using namespace std;
const int N=20,M=1e3+5,INF=1e9;
int src,sink,tot_edge,
	head[N],used[N],work[N],dist[N],que[N];
struct Edge{
	int to,cap,nxt;
}edge[M<<1];
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
			if(dist[to]==-1&&edge[i].cap){
				dist[to]=dist[cur]+1;
				que[R++]=to;
			}
		}
	}
}
int dfs(int cur,int f){
	if(cur==sink)return f;
	used[cur]=true;
	for(int &i=work[cur];~i;i=edge[i].nxt){
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
			work[i]=head[i];
		while(true){
			for(int i=src;i<=sink;++i)
				used[i]=false;
			int f=dfs(src,INF);
			if(!f)break;
			flow+=f;
		}
	}
}
int solve(){
	int n,m,a,b,c;
	scanf("%d%d",&n,&m);
	src=1;
	sink=n;
	for(int i=src;i<=sink;++i)
		head[i]=-1;
	tot_edge=0;
	while(m--&&~scanf("%d%d%d",&a,&b,&c)){
		add_edge(a,b,c);
	}
	return Dinic();
}
int main(){
	int cas,kase=0;
	scanf("%d",&cas);
	while(cas--){
		printf("Case %d: %d\n",++kase,solve());
	}
	return 0;
}
/*
	
	Mar.07.16
	
	Tags:Dinic,max_flow
	Submissions:1
	
	Exe.Time 124MS
	Exe.Memory 1432K
	Code Len. 1613B
	
*/
