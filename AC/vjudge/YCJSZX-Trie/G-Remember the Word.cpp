#include<cstdio>
#include<cstring>
const int LEN=3e5+5,NODE=4e5+5,P=20071027;
char str[LEN],sub[105];
int allc=0,pre[NODE][26]={0},dp[LEN]={0};
bool en[NODE]={false};
int main(){
	int cas=0;
	dp[0]=1;
	while(~scanf("%s",str)){
		int n;
		scanf("%d",&n);
		while(n--){
			scanf("%s",sub);
			int len=strlen(sub),cur=0;
			for(int i=len-1;i>=0;--i){
				if(!pre[cur][sub[i]-'a'])
					pre[cur][sub[i]-'a']=++allc;
				cur=pre[cur][sub[i]-'a'];
			}
			en[cur]=true;
		}
		int len=strlen(str);
		for(int i=0;i<len;++i){
			int cur=0;
			for(int j=i;j>=0;--j){
				cur=pre[cur][str[j]-'a'];
				if(!cur)break;
				if(en[cur])dp[i+1]=(dp[i+1]+dp[j])%P;
			}
		}
		printf("Case %d: %d\n",++cas,dp[len]);
		for(int i=1;i<=len;++i)
			dp[i]=0;
		for(int i=0;i<=allc;++i){
			en[i]=false;
			for(int j=0;j<26;++j)
				pre[i][j]=0;
		}
		allc=0;
	}
	return 0;
}
/*
	
	Nov.22.15
	Submit:1
	
	Time 79ms
	Code Length 851B
	
*/
