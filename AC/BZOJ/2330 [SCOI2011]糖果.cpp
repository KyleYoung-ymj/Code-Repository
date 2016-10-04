#include<cstdio>
#include<cstring>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#define fi first
#define se second
#define lowbit(x) (x&-x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
const int N=(int)1e5+5,mod=(int)1e9+7,INF=0x7fffffff;
int n,tot_edge,mi,sz,head[N],dist[N],cnt[N];
bool in_que[N],vis[N];
queue<int>que;
struct Edge{
	int to,nxt,cost;
	Edge(){}
	Edge(int to,int nxt,int cost):to(to),nxt(nxt),cost(cost){}
}edge[N<<1];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
void add_edge(int u,int v,int cost){
	edge[tot_edge]=Edge(v,head[u],cost);
	head[u]=tot_edge++;
}
bool SPFA(){
	for(int i=1;i<=n;++i){
		dist[i]=1;
		cnt[i]=0;
		que.push(i);
		in_que[i]=true;
	}
	while(!que.empty()){
		int cur=que.front();
		que.pop();
		in_que[cur]=false;
		for(int i=head[cur];~i;i=edge[i].nxt){
			int to=edge[i].to;
			if(dist[to]<dist[cur]+edge[i].cost){
				dist[to]=dist[cur]+edge[i].cost;
				if(!in_que[to]){
					if(++cnt[to]==n)return false;
					que.push(to);
					in_que[to]=true;
				}
			}
		}
	}
	return true;
}
int main(){
	int m,ope,u,v;
	rd(n);rd(m);
	tot_edge=0;
	memset(head,-1,n+1<<2);
	for(int i=0;i<m;++i){
		rd(ope);rd(u);rd(v);
		switch(ope){
			case 1:
				add_edge(u,v,0);
				add_edge(v,u,0);
				break;
			case 2:
				add_edge(u,v,1);
				break;
			case 3:
				add_edge(v,u,0);
				break;
			case 4:
				add_edge(v,u,1);
				break;
			case 5:
				add_edge(u,v,0);
				break;
		}
	}
	if(!SPFA())return puts("-1");
	ll ans=0;
	for(int i=1;i<=n;++i)
		ans+=dist[i];
	printf("%lld\n",ans);
	return 0;
}
/*
	
	Jul.11.16

	Tags:system of difference constraints
	Submissions:5

	Memory 5400kb
	Time 4540ms
	Code Length 2184B

*/
