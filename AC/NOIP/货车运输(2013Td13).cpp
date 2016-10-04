#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1e4+5,M=5e4+5,Q=3e4+5;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>=48);
}
struct edge{
	int from,to,cost;
	bool operator <(const edge &tmp)const{
		return cost>tmp.cost;
	}
}es[M];
struct Query{
	int id,x;
}tmp;
vector<Query>query[N];
int par[N],ans[Q];
int get(int x){
	return par[x]==x?x:par[x]=get(par[x]);
}
inline void check(int &a,int b){
	if(b>a)a=b;
}
int main(){
	int n,m,q,a,b,c;
	rd(n);rd(m);
	for(int i=1;i<=n;++i)
		par[i]=i;
	for(int i=0;i<m;++i){
		rd(a);rd(b);rd(c);
		es[i]=(edge){a,b,c};
	}
	sort(es,es+m);
	rd(q);
	for(int i=0;i<q;++i){
		rd(a);rd(b);
		query[a].push_back((Query){i,b});
		query[b].push_back((Query){i,a});
	}
	memset(ans,-1,sizeof(ans));
	for(int i=0;i<m;++i){
		int ra=get(es[i].from),rb=get(es[i].to);
		if(ra==rb)continue;
		if(query[ra].size()>query[rb].size())swap(ra,rb);
		par[ra]=rb;
		int sz=query[ra].size();
		for(int j=0;j<sz;++j){
			Query now=query[ra][j];
			if(get(now.x)==rb)check(ans[now.id],es[i].cost);
			else query[rb].push_back(now);
		}
	}
	for(int i=0;i<q;++i)
		printf("%d\n",ans[i]);
	return 0;
}
/*
	
	Oct.30.15
	Submit:2
	
	Memory 3296K
	Time 63MS
	Code Length 1.29K
	
*/
