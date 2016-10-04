#include<cstdio>
const int N=205,INF=1e9+5;
int num[N],sum[N],dp_mi[N][N],dp_mx[N][N];
inline int calc(int L,int R){
	return sum[R]-sum[L-1];
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int main(){
	int n,ans_mi=INF,ans_mx=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&num[i]);
		num[i+n]=num[i];
	}
	int m=n<<1;
	sum[0]=0;
	for(int i=1;i<=m;++i){
		sum[i]=sum[i-1]+num[i];
		dp_mi[i][i]=dp_mx[i][i]=0;
	}
	for(int d=1;d<n;++d)
		for(int i=1;i<=m-d;++i){
			int j=i+d;
			dp_mi[i][j]=INF;
			for(int k=i;k<j;++k){
				Min(dp_mi[i][j],dp_mi[i][k]+dp_mi[k+1][j]+calc(i,j));
				if(d==n-1)Min(ans_mi,dp_mi[i][j]);
			}
			dp_mx[i][j]=0;
			for(int k=i;k<j;++k){
				Max(dp_mx[i][j],dp_mx[i][k]+dp_mx[k+1][j]+calc(i,j));
				if(d==n-1)Max(ans_mx,dp_mx[i][j]);
			}
		}
	printf("%d\n%d\n",ans_mi,ans_mx);
	return 0;
}
/*
	
	Dec.27.15
	
	Tags:dp,classic
	Submissions:6
	
	Test1 Accepted / 6ms / 12580kB
	Test2 Accepted / 6ms / 12580kB
	Test3 Accepted / 1ms / 12580kB
	Test4 Accepted / 1ms / 12580kB
	Test5 Accepted / 1ms / 12580kB
	Test6 Accepted / 1ms / 12580kB
	Test7 Accepted / 0ms / 12580kB
	Test8 Accepted / 7ms / 12580kB
	Test9 Accepted / 13ms / 12580kB
	Test10 Accepted / 68ms / 12580kB
*/
