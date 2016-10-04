#include<cstdio>
const int N=1e6+5,P=1e9;
int n,ans[N];
int main(){
	scanf("%d",&n);
	ans[0]=1;
	for(int i=1;i<=n;++i)
		if(i&1)ans[i]=ans[i-1];
		else ans[i]=(ans[i>>1]+ans[i-1])%P;
	printf("%d\n",ans[n]);
	return 0;
}
/*
	
	Dec.15.15
	
	Tags:Binary,Mathematics,dp
	Submissions:1
	
	Memory 4300K
	Time 63MS
	Code Length 219B
	
*/
