#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<double,double> P;
const int N=525;
P dp[N];
void solve(){
	int n,k1,k2,k3,x1,x2,x3;
	scanf("%d%d%d%d%d%d%d",&n,&k1,&k2,&k3,&x1,&x2,&x3);
	double p=1.0/k1/k2/k3;
	for(int i=n+1,tot=n+k1+k2+k3;i<=tot;++i)
		dp[i]=P(0,0);
	for(int i=n;~i;--i){
		dp[i]=P(0,0);
		for(int a=1;a<=k1;++a)
			for(int b=1;b<=k2;++b)
				for(int c=1;c<=k3;++c){
					if(a==x1&&b==x2&&c==x3){
						dp[i].first+=p;
						continue;
					}
					int tar=i+a+b+c;
					dp[i].first+=dp[tar].first*p;
					dp[i].second+=dp[tar].second*p;
				}
		++dp[i].second;
	}
	printf("%.15f\n",dp[0].second/(1-dp[0].first));
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--)solve();
	return 0;
}
/*
	
	May.09.16
	
	Tags:dp
	Submissions:1
	
	Run Time(ms) 10
	Run Memory(KB) 176
	
*/
