#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
const int M=10005,INF=1000000000;
struct node{
	int to,cost;
};
node make_node(int a,int b){
	node res;
	res.to=a;
	res.cost=b;
	return res;
}
int dis[M],que[M*100];
bool mark[M];
vector<node>edge[M];
void SPFA(int s,int n){
	for(int i=1;i<=n;i++)dis[i]=INF;
	int L=0,R=0;
	dis[s]=0;
	que[R++]=s;
	while(L<R){
		int k=que[L++];
		mark[k]=false;
		for(int i=0;i<edge[k].size();i++){
			int y=edge[k][i].to,v=edge[k][i].cost;
			if(dis[y]>dis[k]+v){
				dis[y]=dis[k]+v;
				if(!mark[y]){
					que[R++]=y;
					mark[y]=true;
				}
			}
		}
	}
}
int main(){
	int n,m,s,t,x,y,z;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	while(m--){
		scanf("%d%d%d",&x,&y,&z);
		edge[x].push_back(make_node(y,z));
	}
	SPFA(s,n);
	if(dis[t]==INF)dis[t]=-1;
	printf("%d\n",dis[t]);
	return 0;
}
