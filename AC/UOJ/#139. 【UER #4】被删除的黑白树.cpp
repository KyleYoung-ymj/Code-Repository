#include<cstdio>
#include<cctype>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1e5+5,INF=1e6+5;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),!isdigit(c));
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),isdigit(c));
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
vector<int>T[N];
int rank[N],dep[N],ans=0;
int dfs(int now,int pre){
	rank[now]=rank[pre]+1;
	int sz=T[now].size(),mi=INF;
	for(int i=0;i<sz;++i){
		int to=T[now][i];
		if(to==pre)continue;
		Min(mi,dfs(to,now));
	}
	if(sz==1&&now!=1)return dep[now]=1;
	return dep[now]=mi+1;
}
void paint(int x,int left){
	bool flag=dep[x]==left;
	ans+=flag;
	int sz=T[x].size();
	for(int i=0;i<sz;++i){
		int to=T[x][i];
		if(rank[to]<rank[x])continue;
		paint(to,left-flag);
	}
}
int main(){
	int n,a,b;
	rd(n);
	for(int i=1;i<=n;++i)
		T[i].clear();
	for(int i=1;i<n;++i){
		rd(a);rd(b);
		T[a].push_back(b);
		T[b].push_back(a);
	}
	rank[0]=0;
	dfs(1,0);
	paint(1,dep[1]);
	printf("%d\n",ans);
	return 0;
}
/*
	
	Nov.05.15
	Submit:1
	
	Time 469ms
	Memory 11380kb
	Code Length 1.0kb
	
	
*/
