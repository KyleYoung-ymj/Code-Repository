#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=405,SIGMA=805;
int n,m,sum_A,A[N],B[N],C[N];
typedef __int64 ll;
const ll INF=1ll<<60;
ll ans,val[SIGMA];
struct Point{
	ll x,y;
	inline bool operator ==(const Point &tmp)const{
		return x==tmp.x&&y==tmp.y;
	}
}dp[SIGMA];
inline void Min(ll &a,ll b){
	if(b<a)a=b;
}
Point DP(ll kb,ll kc){
	dp[0]=(Point){0,0};
	val[0]=0;
	for(int i=1;i<=sum_A;++i){
		dp[i]=(Point){INF,INF};
		val[i]=INF;
	}
	for(int i=0;i<n;++i){
		for(int j=sum_A;j>=A[i];--j){
			ll value=val[j-A[i]]+kb*B[i]+kc*C[i];
			if(value<val[j]){
				val[j]=value;
				dp[j]=(Point){dp[j-A[i]].x+B[i],dp[j-A[i]].y+C[i]};
			}
		}
	}
	int res_id=m;
	Point res=dp[m];
	for(int i=m+1;i<=sum_A;++i){
		if(val[i]<val[res_id]){
			res_id=i;
			res=dp[i];
		}
	}
	return res;
}
void rec(Point L,Point R){
	Point mid=DP(L.y-R.y,R.x-L.x);
	if(mid==L||mid==R)return;
	Min(ans,mid.x*mid.y);
	rec(L,mid);
	rec(mid,R);
}
int main(){
	while(~scanf("%d%d",&n,&m)){
		sum_A=0;
		for(int i=0;i<n;++i){
			scanf("%d%d%d",&A[i],&B[i],&C[i]);
			sum_A+=A[i];
		}
		Point L=DP(1,0),R=DP(0,1);
		ans=min(L.x*L.y,R.x*R.y);
		rec(L,R);
		printf("%I64d\n",ans);
	}
	return 0;
}
/*
	
	May.26.16
	
	Tags:Mathematics,dp
	Submissions:1
	
	Exe.Time 826MS
	Exe.Memory 1424K
	Code Len. 1266B
	
*/
