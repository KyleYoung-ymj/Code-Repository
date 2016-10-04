#include<cstdio>
const int N=25,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
int n,m,ans;
char mp[N][N];
bool used[N][N]={false};
inline bool in(int x,int y){
	return ~x&&x<n&&~y&&y<m;
}
void dfs(int x,int y){
	++ans;
	used[x][y]=true;
	for(int i=0;i<4;++i){
		int dx=x+rx[i],dy=y+ry[i];
		if(in(dx,dy)&&mp[dx][dy]!='#'&&!used[dx][dy])
			dfs(dx,dy);
	}
}
int main(){
	while(~scanf("%d%d",&m,&n)&&n&&m){
		int sx,sy;
		bool flag=false;
		for(int i=0;i<n;++i){
			scanf("%s",mp[i]);
			if(!flag)
				for(int j=0;j<m;++j)
					if(mp[i][j]=='@'){
						sx=i;
						sy=j;
						flag=true;
					}
		}
		ans=0;
		dfs(sx,sy);
		printf("%d\n",ans);
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)
				used[i][j]=false;
	}
	return 0;
}
/*
	
	Dec.12.15
	
	Tags:dfs
	Submissions:1
	
	Memory 388K
	Time 16MS
	Code Length 713B
	
*/
