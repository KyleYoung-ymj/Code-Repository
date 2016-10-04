#include<cstdio>
#include<cstring>
const int N=2e5+5,P=1e4+7;
char str[N];
int n,f[N]={0},dp[N]={0};
void get_fail(){
	for(int i=1;i<n;++i){
		int j=f[i];
		while(j&&str[i]!=str[j])j=f[j];
		f[i+1]=str[i]==str[j]?j+1:0;
	}
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		scanf("%d %s",&n,str);
		get_fail();
		int ans=0;
		for(int i=1;i<=n;++i){
			dp[i]=dp[f[i]]+1;
			if(dp[i]==P)dp[i]=0;
			else ans=(ans+dp[i])%P;
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	Nov.27.15
	Submit:1
	
	Memory 3156KB
	Time 62ms
	Code Length 471B
	
*/
