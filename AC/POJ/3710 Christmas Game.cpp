#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=105,M=505;
int tot_edge,head[N],par[N],dep[N];
bool vis[N];
struct Edge{
	int to,nxt;
}edge[M<<1];
void add_edge(int from,int to){
	edge[tot_edge]=(Edge){to,head[from]};
	head[from]=tot_edge++;
}
void dfs(int cur,int fa,int depth){
	vis[cur]=true;
	par[cur]=fa;
	dep[cur]=depth++;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==fa)continue;
		if(vis[to]&&dep[to]<dep[cur]){
			int pre,tmp=cur,cnt=2;
			while(par[tmp]!=to){
				++cnt;
				pre=tmp;
				tmp=par[tmp];
			}
			if(cnt&1)par[pre]=-1;
			else par[tmp]=-1;
		}
		else if(!vis[to])dfs(to,cur,depth);
	}
}
int SG(int cur){
	int sum=0;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(par[to]==cur)sum^=SG(to)+1;
	}
	return sum;
}
int main(){
	int cnt,n,m,u,v;
	while(~scanf("%d",&cnt)){
		int sum=0;
		while(cnt--&&scanf("%d%d",&n,&m)){
			tot_edge=0;
			memset(head,-1,n+1<<2);
			memset(vis,false,n+1);
			while(m--&&scanf("%d%d",&u,&v)){
				add_edge(u,v);
				add_edge(v,u);
			}
			dfs(1,-1,0);
			sum^=SG(1);
		}
		puts(sum?"Sally":"Harry");
	}
	return 0;
}
/*
	
	May.20.16
	
	Tags:Game Theory
	Submissions:3
	
	Memory 304K
	Time 16MS
	Code Length 1149B
	
*/
