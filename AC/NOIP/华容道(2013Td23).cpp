#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int N=35,rx[]={-1,0,0,1},ry[]={0,1,-1,0};
int n,m,f[N][N][4][4],dist[N][N][4];
bool mp[N][N],used[N][N];
struct Status{
	int x,y,step;
};
queue<Status>que;
struct edge{
	int tx,ty,tdir,cost;
};
vector<edge>G[N][N][4];
struct status{
	int dis,x,y,dir;
	bool operator <(const status &tmp)const{
		return dis>tmp.dis;
	}
};
priority_queue<status>pque;
inline bool in(int x,int y){
	return x>=0&&x<n&&y>=0&&y<m;
}
int bfs(int sx,int sy,int tx,int ty){
	if(sx==tx&&sy==ty)return 0;
	while(!que.empty())que.pop();
	memset(used,false,sizeof(used));
	que.push((Status){sx,sy,0});
	used[sx][sy]=true;
	while(!que.empty()){
		Status now=que.front();
		que.pop();
		int x=now.x,y=now.y,step=now.step+1;
		for(int i=0;i<4;++i){
			int dx=x+rx[i],dy=y+ry[i];
			if(!in(dx,dy)||!mp[dx][dy]||used[dx][dy])continue;
			if(dx==tx&&dy==ty)return step;
			que.push((Status){dx,dy,step});
			used[dx][dy]=true;
		}
	}
	return -2;
}
void pre_pro(){
	memset(f,-1,sizeof(f));
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j){
			if(!mp[i][j])continue;
			mp[i][j]=false;
			for(int k=0;k<4;++k){
				int kx=i+rx[k],ky=j+ry[k];
				if(!in(kx,ky)||!mp[kx][ky])continue;
				for(int t=0;t<4;++t){
					int tx=i+rx[t],ty=j+ry[t];
					if(!in(tx,ty)||!mp[tx][ty])continue;
					f[i][j][k][t]=bfs(kx,ky,tx,ty)+1;
				}
			}
			mp[i][j]=true;
		}
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			for(int k=0;k<4;++k)
				G[i][j][k].clear();
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j){
			if(!mp[i][j])continue;
			for(int k=0;k<4;++k)
				for(int t=0;t<4;++t){
					if(f[i][j][k][t]==-1)continue;
					int tx=i+rx[t],ty=j+ry[t],tdir=3-t;
					G[i][j][k].push_back((edge){tx,ty,tdir,f[i][j][k][t]});
				}
		}
}
void Dijkstra(int sx,int sy,int sdir,int sdis){
	memset(dist,-1,sizeof(dist));
	while(!pque.empty())pque.pop();
	pque.push((status){dist[sx][sy][sdir]=sdis,sx,sy,sdir});
	while(!pque.empty()){
		status now=pque.top();
		pque.pop();
		int dis=now.dis,x=now.x,y=now.y,dir=now.dir;
		if(dist[x][y][dir]<dis)continue;
		int sz=G[x][y][dir].size();
		for(int i=0;i<sz;++i){
			edge tmp=G[x][y][dir][i];
			int tx=tmp.tx,ty=tmp.ty,tdir=tmp.tdir,cost=tmp.cost;
			if(dist[tx][ty][tdir]==-1||dist[tx][ty][tdir]>dist[x][y][dir]+cost)
				pque.push((status){dist[tx][ty][tdir]=dist[x][y][dir]+cost,tx,ty,tdir});
		}
	}
}
int query(){
	int ex,ey,sx,sy,tx,ty;
	scanf("%d %d %d %d %d %d",&ex,&ey,&sx,&sy,&tx,&ty);
	if(sx==tx&&sy==ty)return 0;
	--ex;--ey;--tx;--ty;
	mp[--sx][--sy]=false;
	int ans=-1;
	for(int i=0;i<4;++i){
		int nx=sx+rx[i],ny=sy+ry[i];
		if(!in(nx,ny)||!mp[nx][ny])continue;
		int tmp=bfs(ex,ey,nx,ny);
		if(tmp==-2)continue;
		Dijkstra(sx,sy,i,tmp);
		for(int j=0;j<4;++j){
			if(dist[tx][ty][j]==-1)continue;
			if(ans==-1||dist[tx][ty][j]<ans)ans=dist[tx][ty][j];
		}
	}
	mp[sx][sy]=true;
	return ans;
}
int main(){
	int q;
	scanf("%d %d %d",&n,&m,&q);
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			scanf("%d",&mp[i][j]);
	pre_pro();
	while(q--)printf("%d\n",query());
	return 0;
}
/*
	
	Nov.03.15
	Score 10
	
	Memory 996K
	Time 188MS
	Code Length 3.16K
	
*/
