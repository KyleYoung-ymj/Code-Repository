#include<cstdio>
#include<cstring>
const int N=1005;
bool used[N];
int n,m,edge[N][2],adj[N];
bool Hungary(int cur){
	for(int i=0;i<2;++i){
		int to=edge[cur][i];
		if(used[to])continue;
		used[to]=true;
		if(adj[to]==-1||Hungary(adj[to])){
			adj[to]=cur;
			return true;
		}
	}
	return false;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
		scanf("%d%d",&edge[i][0],&edge[i][1]);
	memset(adj,-1,sizeof(adj));
	int ans=0;
	for(int i=1;i<=m;++i){
		memset(used,false,sizeof(used));
		if(Hungary(i))++ans;
		else break;// WA...
	}
	printf("%d\n",ans);
	return 0;
}
/*
	
	Mar.02.16
	
	Tags:Hungary Algorithm
	Submissions:5
	
	Memory 820kb
	Time 0ms
	Code Length 665B
	
*/
