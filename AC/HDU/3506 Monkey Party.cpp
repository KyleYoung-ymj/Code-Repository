#include<cstdio>
typedef unsigned long long ull;
const int N=2005,INF=1e9+5;
int num[N],dp[N][N],s[N][N];
ull sum[N];
inline int calc(int L,int R){
	return sum[R]-sum[L-1];
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int main(){
	int n;
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;++i){
			scanf("%d",&num[i]);
			num[i+n]=num[i];
		}
		int m=n<<1,ans=INF;
		sum[0]=0;
		for(int i=1;i<=m;++i){
			sum[i]=sum[i-1]+num[i];
			dp[i][i]=0;
			s[i][i]=i;
		}
		for(int d=1;d<n;++d)
			for(int i=1;i<=m-d;++i){
				int j=i+d;
				dp[i][j]=INF;
				for(int k=s[i][j-1];k<=s[i+1][j]&&k<j;++k){
					if(k<i)continue;
					int tmp=dp[i][k]+dp[k+1][j]+calc(i,j);
					if(tmp<=dp[i][j]){
						dp[i][j]=tmp;
						s[i][j]=k;
					}
				}
			}
		for(int i=1;i<=n;++i)
			Min(ans,dp[i][i+n-1]);
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	Dec.27.15
	
	Tags:dp,classic
	Submissions:5
	WA:Pay attention when n=1
	
	Exe.Time 608MS
	Exe.Memory 28588K
	Code Len. 865B
	
*/
