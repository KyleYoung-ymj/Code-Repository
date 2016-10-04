#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e6+5,MAX_K=26,P=1e9+7;
int last[MAX_K],dp[MAX_K];
char str[N];
inline void mod_add(int &a,int b){
	if((a+=b)>=P)a-=P;
}
int main(){
	int n,m,K,sum=0,ans=1;
	scanf("%d%d%s",&m,&K,str);
	n=strlen(str);
	for(int i=0;i<K;++i){
		dp[i]=0;
		last[i]=-1;
	}
	for(int i=0;i<n;++i){
		last[str[i]-='a']=i;
		int tmp=dp[str[i]];
		dp[str[i]]=(sum+1)%P;
		sum=(((sum<<1)+1-tmp)%P+P)%P;
	}
	for(int i=0;i<m;++i){
		int ptr=-1;
		for(int j=0;j<K;++j)
			if(ptr==-1||last[j]<last[ptr])ptr=j;
		int tmp=dp[ptr];
		dp[ptr]=(sum+1)%P;
		sum=(((sum<<1)+1-tmp)%P+P)%P;
		last[ptr]=n+i;
	}
	for(int i=0;i<K;++i)
		mod_add(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}
/*
	
	Jun.10.16
	
	Tags:dp,greedy
	Submissions:1
	
	Time 108ms
	Memory 3000KB
	
*/
