#include<cstdio>
#include<cstring>
#include<algorithm>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
const int N=1e5+5;
int tot_edge,head[N],dis[N];
bool mark[N],vis[N];
pii es[N];
struct Edge{
	int to,nxt,id;
}edge[N];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
void add_edge(int u,int v,int id){
	edge[tot_edge]=(Edge){v,head[u],id};
	head[u]=tot_edge++;
}
void assign(int cur,int tar){
	dis[cur]=tar;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(vis[to])continue;
		vis[to]=mark[edge[i].id]=true;
	}
}
void solve(){
	int n,m;
	rd(n);rd(m);
	tot_edge=0;
	memset(head,-1,n+1<<2);
	memset(vis,false,n+1);
	memset(mark,false,m);
	for(int i=0;i<m;++i){
		rd(es[i].fi);rd(es[i].se);
		add_edge(es[i].fi,es[i].se,i);
	}
	int L=1,R=n,cnt=0;
	vis[1]=true;
	while(L<=R){
		if(vis[L])assign(L++,cnt++);
		else if(vis[R])assign(R--,cnt++);
	}
	for(int i=0;i<m;++i){
		if(mark[i])printf("%d\n",dis[es[i].se]-dis[es[i].fi]);
		else printf("%d\n",n);
	}
}
int main(){
	int cas;
	rd(cas);
	while(cas--)solve();
	return 0;
}
/*
	
	Jul.05.16
	
	Tags:constructive,shortest path
	Submissions:1
	
	Memory(KB) 3908KB
	Time(ms) 670ms
	Lenght(Bytes) 1150B
	
*/
