#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=1e3+5,M=N<<1,rx[]={0,1,0,-1},ry[]={1,0,-1,0};
int id[100];
char str[N];
bool mark[M][M][4]={false},vis[M][M];
pii dir[100];
queue<pii>que;
void init(){
	dir['N']=pii(0,1);
	dir['S']=pii(0,-1);
	dir['W']=pii(-1,0);
	dir['E']=pii(1,0);
}
inline bool in(int x,int y){
	return ~x&&x<M&&~y&&y<M;
}
void fun(int x,int y,char c){
//	printf("*%d %d %c\n",x,y,c);//
	if(c=='N'){
		mark[x-1][y][1]=mark[x][y][3]=true;
	}
	else if(c=='E'){
		mark[x][y-1][0]=mark[x][y][2]=true;
	}
	else if(c=='S'){
		mark[x-1][y-1][1]=mark[x][y-1][3]=true;
	}
	else if(c=='W'){
		mark[x-1][y-1][0]=mark[x-1][y][2]=true;
	}
}
int main(){
	freopen("gates.in","r",stdin);
	freopen("gates.out","w",stdout);
	int n;
	scanf("%d%s",&n,str);
	int x=N,y=N;
	init();
	for(int i=0;i<n;++i){
		int dx=x+dir[str[i]].x,
			dy=y+dir[str[i]].y;
		fun(x,y,str[i]);
		x=dx;
		y=dy;
	}
	memset(vis,false,sizeof vis);
	int ans=0;
	while(!que.empty())que.pop();
	for(int i=0;i<M;++i)
		for(int j=0;j<M;++j)
			if(!vis[i][j]){
//				printf("!%d %d\n",i,j);//
				vis[i][j]=true;
				++ans;
				que.push(pii(i,j));
				while(!que.empty()){
					pii cur=que.front();
					que.pop();
					for(int k=0;k<4;++k){
						int dx=cur.x+rx[k],
							dy=cur.y+ry[k];
						if(!in(dx,dy)||vis[dx][dy]||mark[cur.x][cur.y][k])continue;
						vis[dx][dy]=true;
//						if(dx==1003&&dy==1006)printf("#%d %d %d\n",cur.x,cur.y,k);//
						que.push(pii(dx,dy));
					}
				}
			}
	printf("%d\n",ans-1);
	return 0;
}
