#include<cstdio>
const int N=1005,INF=1e9+5;
int dp[N][N],s[N][N];
struct Point{
	int x,y;
	inline void rd(){
		scanf("%d%d",&x,&y);
	}
}p[N];
inline int calc(int a,int b,int c,int d){
	return p[c].x-p[a].x+p[b].y-p[d].y;
}
int main(){
	int n;
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;++i)
			p[i].rd();
		for(int i=1;i<=n;++i){
			dp[i][i]=0;
			s[i][i]=i;
			for(int j=i+1;j<=n;++j)
				dp[i][j]=INF;
		}
		for(int d=1;d<n;++d)
			for(int i=1;i<=n-d;++i){
				int j=i+d;
				for(int k=s[i][j-1];k<=s[i+1][j]&&k<j;++k){
					int tmp=dp[i][k]+dp[k+1][j]+calc(i,k,k+1,j);
					if(tmp<=dp[i][j]){
						dp[i][j]=tmp;
						s[i][j]=k;
					}
				}
			}
		printf("%d\n",dp[1][n]);
	}
	return 0;
}
/*
	
	Dec.26.15
	
	Submissions:2
	Tags:2
	
	Exe.Time 187MS
	Exe.Memory 9284K
	Code Len. 732B
	
*/
