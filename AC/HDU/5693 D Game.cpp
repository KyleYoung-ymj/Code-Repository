#include<cstdio>
#include<algorithm>
using namespace std;
const int N=305;
int m,num[N],delta[N];
bool dp[N][N];
int DP[N];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
bool exist(int tar){
	int k=lower_bound(delta,delta+m,tar)-delta;
	return k<m&&delta[k]==tar;
}
void solve(){
	int n;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&num[i]);
		dp[i][i-1]=true;
	}
	for(int i=0;i<m;++i)
		scanf("%d",&delta[i]);
	sort(delta,delta+m);
	for(int d=2;d<=n;++d){
		for(int i=1,j=i+d-1;j<=n;++i,++j){
			dp[i][j]=false;
			if(dp[i+1][j-1]&&exist(num[j]-num[i])){
				dp[i][j]=true;
				continue;
			}
			for(int k=i+1;k<j-1;++k){
				if(dp[i][k]&&dp[k+1][j]){
					dp[i][j]=true;
					break;
				}
			}
			if(!dp[i][j]){
				for(int k=i+1;k<j;++k){
					if(num[k]-num[i]==num[j]-num[k]&&dp[i+1][k-1]&&dp[k+1][j-1]&&exist(num[k]-num[i])){
						dp[i][j]=true;
						break;
					}
				}
			}
		}
	}
	DP[0]=0;
	for(int i=1;i<=n;++i){
		DP[i]=DP[i-1];
		for(int j=1;j<i;++j){
			if(!dp[j][i])continue;
			Max(DP[i],DP[j-1]+i-j+1);
		}
	}
	printf("%d\n",DP[n]);
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--)solve();
	return 0;
}
/*
	
	May.22.16
	
	Tags:dp
	Submissions:1
	
	Exe.Time 655MS
	Exe.Memory 1808K
	Code Len. 1204B
	
*/
