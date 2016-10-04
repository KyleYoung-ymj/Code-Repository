#include<cstdio>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
const int M=10005,INF=2000000000;
struct node{
	int to,cost;
	bool operator <(const node &tmp)const{
		return cost>tmp.cost;
	}
};
node make_node(int a,int b){
	node res;
	res.to=a,res.cost=b;
	return res;
}
int ans,dis[M];
bool mark[M];
vector<node>edge[M];
priority_queue<node>pque;
void Prim(int n){
	for(int i=1;i<=n;i++)dis[i]=INF;
	pque.push(make_node(1,0));
	dis[1]=0;
	while(!pque.empty()){
		int k=pque.top().to;
		pque.pop();
		if(mark[k])continue;
		ans+=dis[k];
		mark[k]=true;
		for(int i=0;i<edge[k].size();i++){
			node nxt=edge[k][i];
			int y=nxt.to,v=nxt.cost;
			if(!mark[y]&&dis[y]>v){
				dis[y]=v;
				pque.push(nxt);
			}
		}
	}
}
int main(){
	int n,m,x,y,z;
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d%d",&x,&y,&z);
		edge[x].push_back(make_node(y,z));
		edge[y].push_back(make_node(x,z));
	}
	Prim(n);
	printf("%d\n",ans);
	return 0;
}
