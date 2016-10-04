#include <cstdio>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb push_back
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<ll,ll> pll;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
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
const int N=85,Rx[]={-1,-1,0,0},Ry[]={-1,0,0,-1};
int n,m,risk[N][N],dist[N*N];
char str[N];
bool mark[N][N],vis[N][N];
pii src,sink;
piii que[N*N];
priority_queue<piii,vector<piii>,greater<piii> >pque;
inline bool in_pos(int x,int y){
	return ~x&&x<=n&&~y&&y<=m;
}
inline bool in_block(int x,int y){
	return ~x&&x<n&&~y&&y<m;
}
bool check(int x,int y){
	for(int i=0;i<4;++i){
		int dx=x+Rx[i],dy=y+Ry[i];
		if(in_block(dx,dy)&&mark[dx][dy])
			return true;
	}
	return false;
}
int calc(int x,int y){
	if(check(x,y))return n+m;
	memset(vis,false,sizeof vis);
	vis[x][y]=true;
	int L=0,R=0;
	for(que[R++]=piii(0,pii(x,y));;){
		piii cur=que[L++];
		int step=cur.fi+1;
		for(int i=0;i<4;++i){
			int dx=cur.se.fi+rx[i],
				dy=cur.se.se+ry[i];
			if(!in_pos(dx,dy)||vis[dx][dy])continue;
			if(check(dx,dy))return n+m-step;
			vis[dx][dy]=true;
			que[R++]=piii(step,pii(dx,dy));
		}
	}
}
inline int id(int x,int y){
	return x*(m+1)+y+1;
}
bool judge(int x,int y,int dir){
	switch(dir){
		case 0:
			return in_block(x-1,y-1)&&mark[x-1][y-1]&&in_block(x-1,y)&&mark[x-1][y];
		case 1:
			return in_block(x-1,y)&&mark[x-1][y]&&in_block(x,y)&&mark[x][y];
		case 2:
			return in_block(x,y)&&mark[x][y]&&in_block(x,y-1)&&mark[x][y-1];
		case 3:
			return in_block(x,y-1)&&mark[x][y-1]&&in_block(x-1,y-1)&&mark[x-1][y-1];
	}
}
void Dijkstra(int x,int y){
	for(int i=0;i<=n;++i)
		for(int j=0;j<=m;++j)
			dist[id(i,j)]=-1;
	for(pque.push(piii(dist[id(x,y)]=risk[x][y],pii(x,y)));!pque.empty();){
		piii cur=pque.top();
		pque.pop();
		int dis=cur.fi,x=cur.se.fi,y=cur.se.se,index=id(x,y);
		if(~dist[index]&&dist[index]<dis)continue;
		for(int i=0;i<4;++i){
			int dx=x+rx[i],dy=y+ry[i];
			if(!in_pos(dx,dy)||judge(x,y,i))continue;
			int id_to=id(dx,dy);
			if(dist[id_to]==-1||dist[id_to]>dis+risk[dx][dy])
				pque.push(piii(dist[id_to]=dis+risk[dx][dy],pii(dx,dy)));
		}
	}
}
void solve(){
	rd(n);rd(m);
	rd(src.fi);rd(src.se);
	rd(sink.fi);rd(sink.se);
	for(int i=0;i<n;++i){
		scanf("%s",str);
		for(int j=0;j<m;++j)
			mark[i][j]=str[j]=='1';
	}
	for(int i=0;i<=n;++i)
		for(int j=0;j<=m;++j)
			risk[i][j]=calc(i,j);
	Dijkstra(src.fi,src.se);
	int ans=dist[id(sink.fi,sink.se)];
	if(ans==-1)puts("no solution");
	else printf("%d\n",ans);
}
int main(){
	int cas;
	for(rd(cas);cas--;)solve();
	return 0;
}
/*
	
	Jul.15.16

	Tags:brute force
	Submissions:2

	Memory 256kB
	Time 4ms
	Code Length 3284B

*/
