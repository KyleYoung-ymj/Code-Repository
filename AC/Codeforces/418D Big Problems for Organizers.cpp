#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+5,LG=18,INF=1e9;
int n,tot_edge,tot,mx_dis,ID,head[N],pre[N],id[N],dep[N],mx_dep[N],lg[N],arr[N],
	ST[2][N][LG];
struct Edge{
	int to,nxt;
}edge[N<<1];
inline void add_edge(int from,int to){
	edge[tot_edge]=(Edge){to,head[from]};
	head[from]=tot_edge++;
}
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
void dfs(int cur,int par,int depth){
	if(depth>=mx_dis){
		mx_dis=depth;
		ID=cur;
	}
	pre[cur]=par;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==par)continue;
		dfs(to,cur,depth+1);
	}
}
void assign_dfs(int cur,int belong,int depth){
	id[cur]=belong;
	Max(mx_dep[belong],dep[cur]=depth);
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(~id[to])continue;
		assign_dfs(to,belong,depth+1);
	}
}
void assign(){
	memset(id,-1,n+1<<2);
	for(int cur=ID,cnt=0;~cur;cur=pre[cur]){
		id[cur]=cnt;
		arr[cnt++]=cur;
	}
	tot=mx_dis+1;
	for(int i=0;i<tot;++i)
		assign_dfs(arr[i],i,0);
}
void init(){
	mx_dis=ID=-1;
	dfs(1,-1,0);
	dfs(ID,-1,0);
	assign();
	for(int i=0;i<tot;++i){
		ST[0][i][0]=mx_dep[i]-i;
		ST[1][i][0]=mx_dep[i]+i;
	}
	for(int j=1;1<<j<=tot;++j)
		for(int i=0;i+(1<<j)<=tot;++i)
			for(int k=0;k<2;++k)
				ST[k][i][j]=max(ST[k][i][j-1],ST[k][i+(1<<j-1)][j-1]);
	for(int i=2,j=1;i<=tot+1;++i){
		lg[i]=j;
		if(!(i&(i-1)))++j;
	}
}
int query_mx(bool type,int L,int R){
	if(L>R)return -INF;
	int k=lg[R-L+2]-1;
	return max(ST[type][L][k],ST[type][R-(1<<k)+1][k]);
}
int solve(int u,int v){
	if(id[u]==id[v]){
		if(dep[u]>dep[v])swap(u,v);
		return max(id[u],tot-1-id[u])+dep[u];
	}
	if(id[u]>id[v])swap(u,v);
	int mid=id[u]-dep[u]+id[v]+dep[v]>>1,ans=0;
	if(mid<id[u]){
		Max(ans,query_mx(0,0,id[v]-1)+id[v]+dep[v]);
		Max(ans,dep[v]);
		Max(ans,query_mx(1,id[v]+1,tot-1)-id[v]+dep[v]);
	}
	else if(mid>=id[v]){
		Max(ans,query_mx(0,0,id[u]-1)+id[u]+dep[u]);
		Max(ans,dep[u]);
		Max(ans,query_mx(1,id[u]+1,tot-1)-id[u]+dep[u]);
	}
	else{
		Max(ans,query_mx(0,0,id[u]-1)+id[u]+dep[u]);
		Max(ans,dep[u]);
		Max(ans,query_mx(1,id[u]+1,mid)-id[u]+dep[u]);
		Max(ans,query_mx(0,mid+1,id[v]-1)+id[v]+dep[v]);
		Max(ans,dep[v]);
		Max(ans,query_mx(1,id[v]+1,tot-1)-id[v]+dep[v]);
	}
	return ans;
}
int main(){
	int sz=128<<20;
	char *p=(char*)malloc(sz)+sz;
	__asm__("movl %0, %%esp\n" :: "r"(p));
	int m,u,v;
	rd(n);
	tot_edge=0;
	memset(head,-1,n+1<<2);
	for(int i=1;i<n;++i){
		rd(u);rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	init();
	rd(m);
	while(m--){
		rd(u);rd(v);
		printf("%d\n",solve(u,v));
	}
	return 0;
}
/*
	
	Jun.01.16
	
	Tags:Tree
	Submissions:4
	
	Time 93ms
	Memory 151600KB
	
*/
