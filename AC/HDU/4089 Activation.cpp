#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e3+5;
const double eps=1e-5;
typedef pair<double,double> P;
P dp[2][N];
int main(){
    int n,m,k;
    double p1,p2,p3,p4;
    while(~scanf("%d%d%d",&n,&m,&k)){
        scanf("%lf%lf%lf%lf",&p1,&p2,&p3,&p4);
        if(p4<eps){
        	puts("0.00000");
        	continue;
		}
        bool cur=0,pre=1;
        dp[pre][1]=P(0,p4/(1-p1-p2));
        for(int i=2;i<=n;++i){
            dp[cur][1]=P(p2/(1-p1),p4/(1-p1));
            for(int j=2;j<=i;++j){
                dp[cur][j].first=p2*dp[cur][j-1].first;
                dp[cur][j].second=p2*dp[cur][j-1].second;
                dp[cur][j].second+=p3*dp[pre][j-1].second+p4*(j<=k);
                dp[cur][j].first/=(1-p1);
                dp[cur][j].second/=(1-p1);
            }
            dp[cur][i].second=dp[cur][i].second/(1-dp[cur][i].first);
            for(int j=1;j<i;++j)
                dp[cur][j].second=dp[cur][j].first*dp[cur][i].second+dp[cur][j].second;
            cur^=1;
            pre^=1;
        }
        printf("%.5f\n",dp[pre][m].second);
    }
    return 0;
}
/*
	
	May.10.16
	
	Tags:dp,Mathematics
	Submissions:5
	
	Exe.Time 1092MS
	Exe.Memory 1508K
	Code Len. 1168B
	
*/
