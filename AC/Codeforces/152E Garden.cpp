#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int N=105,MX_S=1<<7,rx[]={-1,0,1,0},ry[]={0,1,0,-1},INF=0x7fffffff;
int n,m,K,mx_S,ans,ans_x,ans_y,cost[N][N],dp[N][N][MX_S+5];
bool used[N][N][MX_S+5],mark[N][N];
struct STATUS{
	int x,y,S,dist;
	inline bool operator <(const STATUS &tmp)const{
		return dist>tmp.dist;
	}
};
priority_queue<STATUS>pque;
inline bool in(int x,int y){
	return x&&x<=n&&y&&y<=m;
}
void Dijkstra(){
	ans=INF;
	memset(dp,127,sizeof(dp));
	memset(used,false,sizeof(used));
	while(!pque.empty())pque.pop();
	mx_S=1<<K;
	for(int i=0,x,y;i<K;++i){
		scanf("%d%d",&x,&y);
		pque.push((STATUS){x,y,1<<i,dp[x][y][1<<i]=0});
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			pque.push((STATUS){i,j,0,dp[i][j][0]=0});
	while(!pque.empty()){
		STATUS elm=pque.top();
		pque.pop();
		int x=elm.x,y=elm.y,S=elm.S,dist=elm.dist,dis=dist+cost[x][y];
		if(used[x][y][S])continue;
		used[x][y][S]=true;
		if(S==mx_S-1&&dis<ans){
			ans=dis;
			ans_x=x;
			ans_y=y;
		}
		for(int i=0;i<4;++i){
			int dx=x+rx[i],dy=y+ry[i];
			if(!in(dx,dy))continue;
			if(dis<dp[dx][dy][S])
				pque.push((STATUS){dx,dy,S,dp[dx][dy][S]=dis});
		}
		for(int S0=1;S0<mx_S;++S0){
			if(S&S0||!used[x][y][S0])continue;
			int tar_S=S|S0,value=dist+dp[x][y][S0];
			if(value<dp[x][y][tar_S])
				pque.push((STATUS){x,y,tar_S,dp[x][y][tar_S]=value});
		}
	}
}
void restore(int x,int y,int S){
	mark[x][y]=true;
	for(int S0=1;S0<S;++S0){
		if((S|S0)!=S)continue;
		if(dp[x][y][S0]+dp[x][y][S-S0]==dp[x][y][S]){
			restore(x,y,S0);
			restore(x,y,S-S0);
			return;
		}
	}
	for(int i=0;i<4;++i){
		int dx=x+rx[i],dy=y+ry[i];
		if(!in(dx,dy))continue;
		if(dp[dx][dy][S]+cost[dx][dy]==dp[x][y][S]){
			restore(dx,dy,S);
			return;
		}
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&cost[i][j]);
	Dijkstra();
	printf("%d\n",ans);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			mark[i][j]=false;
	restore(ans_x,ans_y,mx_S-1);
	for(int i=1;i<=n;++i,putchar('\n'))
		for(int j=1;j<=m;++j)
			printf("%c",mark[i][j]?'X':'.');
	return 0;
}
/*
	
	May.27.16
	
	Tags:bitmasks,dp,graph,shortest path
	Submissions:1
	
	Time 62ms
	Memory 10300KB
	
*/
