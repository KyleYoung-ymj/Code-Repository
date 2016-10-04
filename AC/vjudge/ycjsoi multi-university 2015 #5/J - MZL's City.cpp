#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int N=205,M=505;
int n,K,tot,arr[N],match[N],ans[M];
bool adj[N][N],vis[N],used[N];
vector<int>G[N*M];
void dfs(int cur){
	vis[cur]=true;
	arr[tot++]=cur;
	for(int i=1;i<=n;++i){
		if(!adj[cur][i]||vis[i])continue;
		dfs(i);
	}
}
bool Find(int cur){
	for(int i=0;i<G[cur].size();++i){
		int to=G[cur][i];
		if(used[to])continue;
		used[to]=true;
		if(!match[to]||Find(match[to])){
			match[to]=cur;
			return true;
		}
	}
	return false;
}
int Hungary(int m){
	int res=0;
	for(int i=m-1;~i;--i){
		int cnt=0;
		for(int j=i*K,en=(i+1)*K;j<en;++j){
			memset(used,false,n+1);
			if(Find(j)){
				++res;
				++cnt;
			}
		}
		ans[i]=cnt;
	}
	return res;
}
void solve(){
	int m;
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=n;++i){
		match[i]=0;
		for(int j=1;j<=n;++j)
			adj[i][j]=false;
	}
	int tot_query=0;
	for(int i=0,ope,tar,u,v;i<m;++i){
		scanf("%d",&ope);
		if(ope==1){
			scanf("%d",&tar);
			memset(vis,false,n+1);
			tot=0;
			dfs(tar);
			for(int j=tot_query*K,en=++tot_query*K;j<en;++j){
				G[j].clear();
				for(int k=0;k<tot;++k)
					G[j].push_back(arr[k]);
			}
		}
		else if(ope==2){
			scanf("%d%d",&u,&v);
			adj[u][v]=adj[v][u]=true;
		}
		else{
			scanf("%d",&tar);
			while(tar--&&scanf("%d%d",&u,&v))
				adj[u][v]=adj[v][u]=false;
		}
	}
	printf("%d\n",Hungary(tot_query));
	for(int i=0;i<tot_query;++i)
		printf("%d%c",ans[i]," \n"[i==tot_query-1]);
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--)solve();
	return 0;
}
/*
	
	Jun.21.16
	
	Tags:Hungary,brute
	Submissions:3
	
	Memory(KB) 5788
	Time(ms) 733
	Length(Bytes) 1548
	
*/
