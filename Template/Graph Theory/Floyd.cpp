#include<cstdio>
const int M=10005,INF=1000000000;
int mp[M][M];
int main(){
	int n,m,s,t,x,y,z;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			mp[i][j]=INF;
	while(m--){
		scanf("%d%d%d",&x,&y,&z);
		if(mp[x][y]>z)mp[x][y]=z;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(mp[i][j]>mp[i][k]+mp[k][j])
					mp[i][j]=mp[i][k]+mp[k][j];
	if(mp[s][t]==INF)mp[s][t]=-1;
	printf("%d\n",mp[s][t]);
	return 0;
}
