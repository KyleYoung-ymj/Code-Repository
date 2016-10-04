#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1e3+5,M=1e6+5;
int n,tot_edge,head[N],dfs_clock,dfn[N],bcc_cnt,bcc_no[N],color[N],top=0;
bool hate[N][N],odd[N];
vector<int>bcc[N];
typedef pair<int,int> P;
P stk[M];
struct Edge{
	int to,nxt;
}edge[M];
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int Tarjan(int u,int par){
	int lowu=dfn[u]=++dfs_clock;
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==par)continue;
		if(dfn[v])Min(lowu,dfn[v]);
		else{
			stk[top++]=P(u,v);
			int lowv=Tarjan(v,u);
			Min(lowu,lowv);
			if(lowv>=dfn[u]){
				bcc[++bcc_cnt].clear();
				while(true){
					P e=stk[--top];
					int a=e.first,b=e.second;
					if(bcc_no[a]!=bcc_cnt)bcc[bcc_no[a]=bcc_cnt].push_back(a);
					if(bcc_no[b]!=bcc_cnt)bcc[bcc_no[b]=bcc_cnt].push_back(b);
					if(a==u&&b==v)break;
				}
			}
		}
	}
	return lowu;
}
void find_bcc(){
	dfs_clock=bcc_cnt=0;
	memset(dfn,0,n+1<<2);
	memset(bcc_no,0,n+1<<2);
	for(int i=1;i<=n;++i){
		if(!dfn[i]){
			Tarjan(i,-1);
		}
	}
}
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void add_edge(int from,int to){
	edge[tot_edge]=(Edge){to,head[from]};
	head[from]=tot_edge++;
}
bool paint(int cur,bool col){
	color[cur]=col;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int v=edge[i].to;
		if(bcc_no[v]!=bcc_no[cur])continue;
		if(color[v]==col||color[v]==-1&&!paint(v,col^1))return false;
	}
	return true;
}
int main(){
	int m,u,v;
	while(~scanf("%d",&n)&&n){
		rd(m);
		for(int i=1;i<n;++i)
			for(int j=i+1;j<=n;++j)
				hate[i][j]=hate[j][i]=false;
		tot_edge=0;
		memset(head,-1,n+1<<2);
		while(m--){
			rd(u);rd(v);
			hate[u][v]=hate[v][u]=true;
		}
		for(int i=1;i<n;++i)
			for(int j=i+1;j<=n;++j)
				if(!hate[i][j]){
					add_edge(i,j);
					add_edge(j,i);
				}
		find_bcc();
		memset(odd,false,n+1);
		for(int i=1;i<=bcc_cnt;++i){
			for(int j=0;j<bcc[i].size();++j){
				bcc_no[bcc[i][j]]=i;
				color[bcc[i][j]]=-1;
			}
			if(!paint(bcc[i][0],0)){
				for(int j=0;j<bcc[i].size();++j)
					odd[bcc[i][j]]=true;
			}
		}
		int ans=n;
		for(int i=1;i<=n;++i)
			ans-=odd[i];
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	May.08.16
	
	Tags:bcc,bipartite
	Submissions:2
	
	Memory 8884K
	Time 204MS
	Code Length 2229B
	
*/
