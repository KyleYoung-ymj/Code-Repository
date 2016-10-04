#include<cstdio>
#include<algorithm>
using namespace std;
const int N=205,M=1e3+5,INF=1e9;
int src,sink,tot_edge,
	head[N],dist[N],work[N],que[N],
	in[N],out[N];
bool used[N];
struct Edge{
	int to,cap,nxt;
}edge[N+M<<1];
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
void Dinic(){
	while(true){
		bfs();
		if(dist[sink]==-1)return;
		for(int i=src;i<=sink;++i)
			work[i]=head[i];
		while(true){
			for(int i=src;i<=sink;++i)
				used[i]=false;
			int f=dfs(src,INF);
			if(!f)break;
		}
	}
}
bool solve(){
	int n,m,u,v;
	bool flag;
	scanf("%d%d",&n,&m);
	src=0;
	sink=n+1;
	tot_edge=0;
	for(int i=src;i<=sink;++i){
		in[i]=out[i]=0;
		head[i]=-1;
	}
	while(m--&&~scanf("%d%d%hhu",&u,&v,&flag)){
		++out[u];
		++in[v];
		if(!flag)add_edge(u,v,1);
	}
	for(int i=1;i<=n;++i){
		if(in[i]+out[i]&1)return false;
		if(in[i]>out[i])add_edge(i,sink,in[i]-out[i]>>1);
		else if(out[i]>in[i])add_edge(src,i,out[i]-in[i]>>1);
	}
	Dinic();
	for(int i=head[src];~i;i=edge[i].nxt)
		if(edge[i].cap)return false;
	return true;
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		puts(solve()?"possible":"impossible");
	}
	return 0;
}
/*
	
	Mar.07.16
	
	Tags:Graph Theory,Dinic
	Submissions:3
	
	Memory 408K
	Time 16MS
	Code Length 1835B
	
*/
