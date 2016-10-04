#include<cstdio>
const int N=105,INF=1e9;
int n,sum[N][N]={0};
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int solve(int L,int R){
	int tmp=0,res=-INF,mi=0;
	for(int i=1;i<=n;++i){
		tmp+=sum[R][i]-sum[L-1][i];
		Max(res,tmp-mi);
		Min(mi,tmp);
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			scanf("%d",&sum[i][j]);
			sum[i][j]+=sum[i-1][j];
		}
	int ans=-INF;
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)
			Max(ans,solve(i,j));
	printf("%d\n",ans);
	return 0;
}
/*
	
	Jan.09.16
	
	Tags:presum
	Submissions:1
	
	Memory 260kB
	Time 0ms
	Code Length 565B
	
*/
