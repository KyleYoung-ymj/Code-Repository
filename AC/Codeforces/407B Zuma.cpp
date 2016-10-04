#include<cstdio>
#include<cstring>
const int N=505,INF=0x7f7f7f7f;
int num[N],dp[N][N];
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int DP(int L,int R){
	if(dp[L][R]<INF)return dp[L][R];
	int &res=dp[L][R];
	if(L>R)res=0;
	else if(L==R)res=1;
	else{
		res=DP(L+1,R)+1;
		if(num[L]==num[L+1])Min(res,DP(L+2,R)+1);
		for(int k=L+2;k<=R;++k)
			if(num[k]==num[L])
				Min(res,DP(L+1,k-1)+DP(k+1,R));
	}
	return res;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&num[i]);
	memset(dp,127,sizeof(dp));
	printf("%d\n",DP(1,n));
	return 0;
}
/*
	
	Dec.29.15
	
	Tags:dp
	Submissions:2
	
	Time 109ms
	Memory 800KB
	
*/
