#include<cstdio>
#include<cmath>
#include<ctime>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<cassert>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<bitset>
#include<complex>
#include<iostream>
#include<algorithm>
#define fi first
#define se second
#define lowbit(x) (x&-x)
#define y1 kjfasiv
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1),eps=1e-9;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
const int N=(int)1e5+5,M=105;
int amt[N];
double dp[N][M],buf[M];
double C(int n,int m){
	double res=1;
	for(int i=1;i<=m;++i)
		res*=1.0*n--/i;
	return res;
}
int main(){
	int n,m;
	double ans=0;
	rd(n);
	for(int i=1;i<=n;++i){
		rd(amt[i]);
		dp[i][amt[i]]=1;
		ans+=dp[i][0];
	}
	rd(m);
	int u,v,K;
	while(m--){
		rd(u);rd(v);rd(K);
		memset(buf,0,sizeof buf);
		for(int i=0;i<=100&&i<=amt[u];++i)
			for(int j=0;j<=i&&j<=K;++j){
				buf[i-j]+=dp[u][i]*C(i,j)*C(amt[u]-i,K-j)/C(amt[u],K);
			}
		amt[u]-=K;
		amt[v]+=K;
		ans-=dp[u][0];
		memcpy(dp[u],buf,sizeof buf);
		ans+=dp[u][0];
		printf("%.12f\n",ans);
	}
	return 0;
}
/*
	
	Jul.11.16

	Tags:probability,dp
	Submissions:2

	Time 1090ms
	Memory 82600KB

*/
