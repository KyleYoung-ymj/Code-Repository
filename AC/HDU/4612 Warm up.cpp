#include<cstdio>
#include<cstring>
#include<vector>
#pragma comment(linker,"/STACK:102400000,102400000")
using namespace std;
const int N=2e5+5,M=1e6+5;
int tot_edge,head[N],dfs_clock,dfn[N],top,stk[N],bcc_cnt,bcc_no[N],ID,mx;
bool vis[N];
vector<int>T[N];
struct Edge{
	int to,nxt;
}edge[M<<1];
inline void add_edge(int from,int to){
	edge[tot_edge].to=to;
	edge[tot_edge].nxt=head[from];
	head[from]=tot_edge++;
}
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int Tarjan(int u,int id){
	int lowu=dfn[u]=++dfs_clock;
	stk[top++]=u;
	for(int i=head[u];~i;i=edge[i].nxt){
		if((i^1)==id)continue;
		int v=edge[i].to;
		if(dfn[v])Min(lowu,dfn[v]);
		else Min(lowu,Tarjan(v,i));
	}
	if(lowu==dfn[u]){
		++bcc_cnt;
		while(true){
			int elm=stk[--top];
			bcc_no[elm]=bcc_cnt;
			if(elm==u)break;
		}
	}
	return lowu;
}
void dfs(int cur,int dis){
	vis[cur]=true;
	if(dis>mx){
		mx=dis;
		ID=cur;
	}
	for(int i=0;i<T[cur].size();++i){
		int to=T[cur][i];
		if(vis[to])continue;
		dfs(to,dis+1);
	}
}
int main(){
	int n,m,u,v;
	while(rd(n),rd(m),n+m){
		tot_edge=dfs_clock=0;
		memset(head,-1,n+1<<2);
		memset(dfn,0,n+1<<2);
		while(m--){
			rd(u);rd(v);
			add_edge(u,v);
			add_edge(v,u);
		}
		mx=top=bcc_cnt=0;
		Tarjan(1,-1);
		for(int i=1;i<=bcc_cnt;++i)
			T[i].clear();
		for(int i=1;i<=n;++i)
			for(int j=head[i];~j;j=edge[j].nxt){
				int to=edge[j].to;
				if(bcc_no[i]!=bcc_no[to]){
					T[bcc_no[i]].push_back(bcc_no[to]);
					T[bcc_no[to]].push_back(bcc_no[i]);
				}
			}
		memset(vis,false,bcc_cnt+1);
		dfs(1,0);
		memset(vis,false,bcc_cnt+1);
		dfs(ID,0);
		printf("%d\n",bcc_cnt-1-mx);
	}
	return 0;
}
/*
	
	May.07.16
	
	Tags:bcc
	Submissions:1
	
	Exe.Time 1903MS
	Exe.Memory 32492K
	Code Len. 1830B
	
*/
