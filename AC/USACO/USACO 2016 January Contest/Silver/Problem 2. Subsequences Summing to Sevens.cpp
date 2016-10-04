#include<cstdio>
const int N=5e4+5;
int num[N],dp[N][10];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int main(){
	freopen("div7.in","r",stdin);
	freopen("div7.out","w",stdout);
	int n,ans=0;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",&num[i]);
	for(int i=0;i<n;++i){
		int rem=num[i]%7;
		for(int j=0;j<7;++j){
			if(!i)dp[i][j]=j==rem;
			else{
				int k=j-rem;
				if(k<0)k+=7;
				if(dp[i-1][k])dp[i][j]=dp[i-1][k]+1;
			}
		}
		Max(dp[i][rem],1);
		Max(ans,dp[i][0]);
	}
	printf("%d\n",ans);
	return 0;
}
