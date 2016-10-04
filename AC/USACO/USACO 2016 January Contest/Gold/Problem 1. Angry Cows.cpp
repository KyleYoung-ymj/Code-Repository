#include<cstdio>
#include<algorithm>
using namespace std;
const int N=(int)5e4+5,INF=0x7fffffff;
int pos[N],dp[2][N];
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int main(){
	freopen("angry.in","r",stdin);
	freopen("angry.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&pos[i]);
		pos[i]<<=1;
	}
	sort(pos,pos+n);
	for(int k=0;k<2;++k,reverse(pos,pos+n)){
		dp[k][0]=0;
		for(int i=1,j=0;i<n;++i){
			while(j+1<i&&abs(pos[i]-pos[j+1])>dp[k][j+1]+2)++j;
			dp[k][i]=abs(pos[i]-pos[j]);
			if(j+1<i)Min(dp[k][i],dp[k][j+1]+2);
		}
	}
	reverse(dp[1],dp[1]+n);
	int ans=INF;
	for(int L=0,R=n-1;L<=R;){
		Min(ans,max(pos[R]-pos[L]>>1,max(dp[0][L],dp[1][R])+2));
		if(dp[0][L+1]<dp[1][R-1])++L;
		else --R;
	}
	printf("%d.%d\n",ans>>1,ans&1?5:0);
	return 0;
}
