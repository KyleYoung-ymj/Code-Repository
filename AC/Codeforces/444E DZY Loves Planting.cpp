#include<cstdio>
#include<algorithm>
using namespace std;
const int N=3e3+5;
int sum,par[N],cnt[N],lim[N];
bool valid;
struct Edge{
	int u,v,cost;
	inline bool operator <(const Edge &tmp)const{
		return cost<tmp.cost;
	}
	void Rd(){
		scanf("%d%d%d",&u,&v,&cost);
	}
}edge[N];
int get_root(int x){
	return par[x]==x?x:par[x]=get_root(par[x]);
}
void unite(int u,int v){
	u=get_root(u);
	v=get_root(v);
	cnt[v]+=cnt[u];
	lim[v]+=lim[u];
	if(cnt[v]>sum-lim[v])valid=false;
	par[u]=v;
}
int main(){
	int n;
	scanf("%d",&n);
	if(n==1){
		puts("0");
		return 0;
	}
	int m=n-1,ans;
	for(int i=0;i<m;++i)
		edge[i].Rd();
	sort(edge,edge+m);
	valid=true;
	sum=0;
	for(int i=1;i<=n;++i){
		cnt[par[i]=i]=1;
		scanf("%d",&lim[i]);
		sum+=lim[i];
	}
	for(int i=0;i<m&&valid;++i){
		if(!i||edge[i].cost!=edge[i-1].cost)ans=edge[i].cost;
		unite(edge[i].u,edge[i].v);
	}
	printf("%d\n",ans);
	return 0;
}
/*
	
	Jun.04.16
	
	Tags:dsu
	Submissions:4
	
	Time 31ms
	Memory 2100KB
	
*/
