#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=105,M=1e3+5,V=N,E=N+M<<1,INF=0x7fffffff;
int n,m,src,sink,tot_edge,tot_ans=0,
	ans[N],deg[N]={0},org[M][2],
	head[V],dist[V],arc[V],que[V];
bool used[V];
struct Edge{
	int to,cap,nxt;
}edge[E<<1];
void add_edge(int from,int to,double c){
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
				que[R++]=to;
				dist[to]=dist[cur]+1;
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
int calc(int g){
	tot_edge=0;
	memset(head,-1,sizeof(head));
	for(int i=0;i<m;++i){
		add_edge(org[i][0],org[i][1],n*n);
		add_edge(org[i][1],org[i][0],n*n);
	}
	for(int i=1;i<=n;++i){
		add_edge(src,i,m*n*n);
		add_edge(i,sink,2*g+(m-deg[i])*n*n);
	}
	return m*n*n*n-Dinic();
}
void find_dfs(int cur){
	used[cur]=true;
	if(cur!=src)ans[tot_ans++]=cur;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(edge[i].cap&&!used[to])find_dfs(to);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	if(!m){
		puts("1\n1");
		return 0;
	}
	src=0;
	sink=n+1;
	for(int i=0;i<m;++i){
		scanf("%d%d",&org[i][0],&org[i][1]);
		++deg[org[i][0]];
		++deg[org[i][1]];
	}
	int L=n,R=m*n*n,res;
	while(L<=R){
		int mid=L+R>>1;
		if(calc(mid)>0){
			res=mid;
			L=mid+1;
		}
		else R=mid-1;
	}
	calc(res);
	for(int i=src;i<=sink;++i)
		used[i]=false;
	find_dfs(src);
	printf("%d\n",tot_ans);
	sort(ans,ans+tot_ans);
	for(int i=0;i<tot_ans;++i)
		printf("%d\n",ans[i]);
	return 0;
}
/*
	
	Mar.10.16
	
	Tags:Minimun Cut
	Submissions:5
	
	Memory 452K
	Time 157MS
	Code Length 2261B
	
*/
