#include<cstdio>
const int M=205;
int n,m;
char mp[M][M];
void dfs(int x,int y){
	if(mp[x][y]=='@')mp[x][y]='*';
	for(int dx=-1;dx<=1;dx++)
		for(int dy=-1;dy<=1;dy++){
			int nx=x+dx,ny=y+dy;
			if(nx>=0&&nx<n&&ny>=0&&ny<m&&mp[nx][ny]=='@')
				dfs(nx,ny);
		}
}
int main(){
	int ans=0;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%s",mp[i]);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(mp[i][j]=='@'){
				ans++;
				dfs(i,j);
			}
	printf("%d\n",ans);
}
