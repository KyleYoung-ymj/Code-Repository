#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
const int N=25,M=16400,K=15,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
int n,m,k,nx[K],ny[K],tx[K],ty[K];
bool stone[N][N],used[N][N][M];
struct Status{
	int x,y,dir,step;
}now;
queue<Status>que;
int hash(){
	int res=0;
	for(int i=k-1;i;--i){
		int dir;
		for(dir=0;;++dir)
			if(tx[i]==tx[i-1]+rx[dir]&&ty[i]==ty[i-1]+ry[dir])
				break;
		res=res<<2|dir;
	}
	return res;
}
void hash_back(){
	nx[0]=now.x;
	ny[0]=now.y;
	for(int i=1;i<k;++i){
		int dir=now.dir&3;
		now.dir>>=2;
		nx[i]=nx[i-1]+rx[dir];
		ny[i]=ny[i-1]+ry[dir];
	}
}
inline bool in(int x,int y){
	return x>=0&&x<n&&y>=0&&y<m;
}
bool move(int dir){
	tx[0]=nx[0]+rx[dir];
	ty[0]=ny[0]+ry[dir];
	if(!in(tx[0],ty[0])||stone[tx[0]][ty[0]])return false;
	for(int i=1;i<k;++i){
		if(nx[i]==tx[0]&&ny[i]==ty[0])
			return false;
		tx[i]=nx[i-1];
		ty[i]=ny[i-1];
	}
	return true;
}
int bfs(){
	if(!nx[0]&&!ny[0])return 0;
	int tmp=0;
	memset(used,false,sizeof(used));
	for(int i=k-1;i;--i){
		int dir;
		for(dir=0;;++dir)
			if(nx[i]==nx[i-1]+rx[dir]&&ny[i]==ny[i-1]+ry[dir])
				break;
		tmp=tmp<<2|dir;
	}
	while(!que.empty())que.pop();
	que.push((Status){nx[0],ny[0],tmp,0});
	used[nx[0]][ny[0]][tmp]=true;
	while(!que.empty()){
		now=que.front();
		que.pop();
		hash_back();
		for(int i=0;i<4;++i)
			if(move(i)){
				if(!tx[0]&&!ty[0])return now.step+1;
				int dir=hash();
				if(used[tx[0]][ty[0]][dir])continue;
				que.push((Status){tx[0],ty[0],dir,now.step+1});
				used[tx[0]][ty[0]][dir]=true;
			}
	}
	return -1;
}
int main(){
	int cnt=1;
	while(scanf("%d %d %d",&n,&m,&k),n){
		int s,a,b;
		for(int i=0;i<k;++i){
			scanf("%d %d",&a,&b);
			nx[i]=a-1;
			ny[i]=b-1;
		}
		scanf("%d",&s);
		memset(stone,false,sizeof(stone));
		while(s--){
			scanf("%d %d",&a,&b);
			stone[a-1][b-1]=true;
		}
		printf("Case %d: %d\n",cnt++,bfs());
	}
	return 0;
}
/*
	
	Nov.03.15
	Submit:2
	
	Memory 11276K
	Time 2313MS
	Code Length 1922B
	
*/
