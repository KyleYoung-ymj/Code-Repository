#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int M=100005;
struct edge{
	int from,to,cost;
}es[M];
edge make_edge(int a,int b,int c){
	edge res;
	res.from=a;
	res.to=b;
	res.cost=c;
	return res;
}
bool cmp(const edge &A,const edge &B){
	return A.cost<B.cost;
}
int fa[M];
void init_union_find(int n){
	for(int i=1;i<=n;i++)
		fa[i]=i;
}
int get(int x){
	return fa[x]==x?x:fa[x]=get(fa[x]);
}
bool same(int a,int b){
	return get(a)==get(b);
}
void unite(int a,int b){
	a=get(a);
	b=get(b);
	fa[a]=b;
}
int Kruskal(int n,int m){
	int res=0;
	init_union_find(n);
	sort(es+1,es+m+1,cmp);
	for(int i=1;i<m;i++){
		int u=es[i].from,v=es[i].to;
		if(!same(u,v)){
			unite(u,v);
			res+=es[i].cost;
		}
	}
	return res;
}
int main(){
	int n,m,x,y,z;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		es[i]=make_edge(x,y,z);
	}
	printf("%d\n",Kruskal(n,m));
}
