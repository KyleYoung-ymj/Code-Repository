#include<cstdio>
#include<cmath>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N=3e4+5,INF=1e9;
int n,S,qsum,qmx,
	val[N],par[N],dep[N],belong[N],sz[N],sum[N],mx[N];
vector<int>edge[N],road[N];
void dfs(int cur,int fa,int depth){
	par[cur]=fa;
	dep[cur]=depth;
	int id=belong[cur];
	for(int i=0;i<edge[cur].size();++i){
		int to=edge[cur][i];
		if(to==fa)continue;
		if(sz[id]<S){
			++sz[id];
			belong[to]=id;
			road[cur].push_back(to);
		}
		dfs(to,cur,depth+1);
	}
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
void build(int cur,int s=0,int m=-INF){
	s+=val[cur];
	sum[cur]=s;
	Max(m,val[cur]);
	mx[cur]=m;
	for(int i=0;i<road[cur].size();++i)
		build(road[cur][i],s,m);
}
void query(int u,int v){
	while(u!=v){
		if(belong[u]==belong[v]){
			if(dep[u]<dep[v])swap(u,v);
			qsum+=val[u];
			Max(qmx,val[u]);
			u=par[u];
		}
		else{
			if(dep[belong[u]]<dep[belong[v]])swap(u,v);
			qsum+=sum[u];
			Max(qmx,mx[u]);
			u=par[belong[u]];
		}
	}
	qsum+=val[u];
	Max(qmx,val[u]);
}
int main(){
	scanf("%d",&n);
	S=sqrt(n);
	int m,a,b;
	for(int i=1;i<n;++i){
		scanf("%d%d",&a,&b);
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&val[i]);
		belong[i]=i;
		sz[i]=0;
	}
	dfs(1,0,0);
	for(int i=1;i<=n;++i)
		if(belong[i]==i)build(i);
	char ope[10];
	scanf("%d",&m);
	while(m--&&~scanf("%s%d%d",ope,&a,&b)){
		if(ope[0]=='C'){
			val[a]=b;
			build(belong[a]);
		}
		else{
			qsum=0;
			qmx=-INF;
			query(a,b);
			printf("%d\n",ope[1]=='M'?qmx:qsum);
		}
	}
	return 0;
}
/*
	
	Feb.28.16
	
	Problem:Luogu P2590
	
*/
