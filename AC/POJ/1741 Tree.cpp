#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e4+5,INF=0x7fffffff;
int tot_edge,head[N],
	k,ans,mi,centroid,tot_dist,
	sz[N],mx[N],dist[N];
bool used[N];
struct Edge{
	int to,cost,nxt;
}edge[N<<1];
void add_edge(int from,int to,int cost){
	edge[tot_edge]=(Edge){to,cost,head[from]};
	head[from]=tot_edge++;
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
void pre_dfs(int cur,int pre){
	sz[cur]=1;
	mx[cur]=-1;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==pre||used[to])continue;
		pre_dfs(to,cur);
		sz[cur]+=sz[to];
		Max(mx[cur],sz[to]);
	}
}
void find_centroid(int cur,int root,int pre){
	Max(mx[cur],sz[root]-sz[cur]);
	if(mx[cur]<mi){
		mi=mx[cur];
		centroid=cur;
	}
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==pre||used[to])continue;
		find_centroid(to,root,cur);
	}
}
void dfs(int cur,int pre,int dis){
	dist[tot_dist++]=dis;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==pre||used[to])continue;
		dfs(to,cur,dis+edge[i].cost);
	}
}
int calc(int root,int dis){
	tot_dist=0;
	dfs(root,-1,dis);
	sort(dist,dist+tot_dist);
	int L=0,R=tot_dist-1,res=0;
	while(L<R){
		while(L<R&&dist[L]+dist[R]>k)--R;
		res+=R-L;
		++L;
	}
	return res;
}
void solve(int cur){
	mi=INF;
	pre_dfs(cur,-1);
	find_centroid(cur,cur,-1);
	ans+=calc(centroid,0);
	used[centroid]=true;
	for(int i=head[centroid];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(used[to])continue;
		ans-=calc(to,edge[i].cost);
		solve(to);
	}
}
int main(){
	int n;
	while(~scanf("%d%d",&n,&k)&&n+k){
		tot_edge=0;
		memset(head,-1,n+1<<2);
		memset(used,false,n+1);
		for(int i=1,a,b,c;i<n&&~scanf("%d%d%d",&a,&b,&c);++i){
			add_edge(a,b,c);
			add_edge(b,a,c);
		}
		ans=0;
		solve(1);
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	Mar.13.16
	
	Tags:Divide and Conquer,classic
	Submissions:1
	
	Memory 1120K
	Time 188MS
	Code Length 1802B
	
*/
