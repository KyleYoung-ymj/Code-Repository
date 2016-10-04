#include<cstdio>
const int N=135;
int num[N][N]={0};
int main(){
//	freopen("wireless.in","r",stdin);
//	freopen("wireless.out","w",stdout);
	int d,n,x,y,k;
	scanf("%d %d",&d,&n);
	while(n--){
		scanf("%d %d %d",&x,&y,&k);
		num[x][y]=k;
	}
	int res,ans=0;
	for(int i=0;i<=128;++i)
		for(int j=0;j<=128;++j){
			int tmp=0;
			for(x=i-d;x<=i+d;++x)
				for(y=j-d;y<=j+d;++y)
					if(x>=0&&x<=128&&y>=0&&y<=128)
						tmp+=num[x][y];
			if(tmp==ans)++res;
			else if(tmp>ans){
				ans=tmp;
				res=1;
			}
		}
	printf("%d %d\n",res,ans);
	return 0;
}
/*
	
	Oct.28.15
	Score 100
	
	Memory 760K
	Time 78MS
	Code Length 0.56K
	
*/
