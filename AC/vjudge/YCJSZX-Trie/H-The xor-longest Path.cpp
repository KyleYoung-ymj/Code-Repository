#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+5,NODE=32e5+5;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),!isdigit(c));
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),isdigit(c));
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
struct edge{
	int to,cost,nxt;
}G[N<<1];
int tot=1,head[N]={0},allc=0,pre[NODE][2]={0},xor_sum[N],bin[31],ans=0;
void add_edge(int from,int to,int cost){
	G[tot].to=to;
	G[tot].cost=cost;
	G[tot].nxt=head[from];
	head[from]=tot++;
}
void dfs(int now,int fa,int sum){
	xor_sum[now]=sum;
	for(int i=head[now];i;i=G[i].nxt){
		if(G[i].to==fa)continue;
		dfs(G[i].to,now,sum^G[i].cost);
	}
}
int find_mx(){
	int res=0,cur=0;
	for(int i=0;i<31;++i)
		if(pre[cur][bin[i]^1]){
			cur=pre[cur][bin[i]^1];
			res|=1<<30-i;
		}
		else cur=pre[cur][bin[i]];
	return res;
}
void solve_dfs(int now,int fa,int sum){
	for(int i=30;i>=0;--i)
		bin[30-i]=(bool)(sum&1<<i);
	Max(ans,find_mx());
	int cur=0;
	for(int i=30;i>=0;--i){
		if(!pre[cur][bin[30-i]])
			pre[cur][bin[30-i]]=++allc;
		cur=pre[cur][bin[30-i]];
	}
	for(int i=head[now];i;i=G[i].nxt){
		if(G[i].to==fa)continue;
		solve_dfs(G[i].to,now,sum^G[i].cost);
	}
}
int main(){
	int n;
	while(~scanf("%d",&n)){
		int a,b,c;
		for(int i=1;i<n;++i){
			rd(a);rd(b);rd(c);
			++a;++b;
			add_edge(a,b,c);
			add_edge(b,a,c);
		}
		dfs(1,-1,0);
		solve_dfs(1,-1,0);
		printf("%d\n",ans);
		for(int i=1;i<=n;++i)
			head[i]=0;
		tot=1;
		for(int i=0;i<=allc;++i)
			pre[i][0]=pre[i][1]=0;
		allc=ans=0;
	}
	return 0;
}
/*
	
	Nov.23.15
	Submit:1
	
	Memory 15936KB
	Time 469ms
	Code Length 1584B
	
*/
