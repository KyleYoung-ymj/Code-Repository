#include<cstdio>
#include<cstring>
const int N=(int)5e4+5,INF=0x7fffffff;
int n,tot_edge,head[N],dist[N],que[N*100];
bool in_que[N];
struct Edge{
	int to,nxt,cost;
	Edge(){}
	Edge(int to,int nxt,int cost):to(to),nxt(nxt),cost(cost){}
}edge[3*N];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void add_edge(int u,int v,int cost){
	edge[tot_edge]=Edge(v,head[u],cost);
	head[u]=tot_edge++;
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
void SPFA(int src){
	memset(dist,127,sizeof(dist));
	memset(in_que,false,sizeof(in_que));
	int L=0,R=0;
	dist[que[R++]=src]=0;
	while(L<R){
		int cur=que[L++];
		in_que[cur]=false;
		for(int i=head[cur];~i;i=edge[i].nxt){
			int to=edge[i].to;
			if(dist[to]>dist[cur]+edge[i].cost){
				dist[to]=dist[cur]+edge[i].cost;
				if(!in_que[to]){
					que[R++]=to;
					in_que[to]=true;
				}
			}
		}
	}
}
void solve(){
	int mi=INF,mx=0,L,R,cnt;
	tot_edge=0;
	memset(head,-1,sizeof(head));
	while(n--){
		rd(L);rd(R);rd(cnt);
		Min(mi,L);
		Max(mx,R+1);
		add_edge(R+1,L,-cnt);
	}
	for(int i=mi;i<mx;++i){
		add_edge(i,i+1,1);
		add_edge(i+1,i,0);
	}
	SPFA(mx);
	printf("%d\n",-dist[mi]);
}
int main(){
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	Jul.10.16

	Tags:system of difference constraints
	Submissions:1

	Exe.Time 1622MS
	Exe.Memory 9408K
	Code Len. 1380B

*/