#include<cstdio>
#include<cstring>
const int N=105,INF=1e4+5;
int dp[N][N][30];
char A[N],B[N];
void Min(int &a,int b){
	if(b<a)a=b;
}
int solve(int L,int R,int k){
	int &res=dp[L][R][k];
	if(~res)return res;
	if(L>R)res=0;
	else if(L==R){
		if(!k)res=A[L]!=B[L];
		else res=B[L]!=k;
	}
	else{
		res=INF;
		if(!k){
			if(A[L]==B[L])res=solve(L+1,R,k);
			else{
				for(int i=L;i<=R;++i)
					if(B[L]==B[i])Min(res,solve(L,i,B[L])+1+solve(i+1,R,k));
			}
		}
		else{
			if(B[L]==k)res=solve(L+1,R,k);
			else{
				for(int i=L;i<=R;++i)
					if(B[L]==B[i])Min(res,solve(L,i,B[L])+1+solve(i+1,R,k));
			}
		}
	}
	return res;
}
int main(){
	while(gets(A)){
		gets(B);
		int n=strlen(A);
		for(int i=0;i<n;++i){
			A[i]-='a'-1;
			B[i]-='a'-1;
		}
		memset(dp,-1,sizeof(dp));
		printf("%d\n",solve(0,n-1,0));
	}
	return 0;
}
/*
	
	Jan.22.16
	
	Tags:dp,string
	Submissions:2
	
	Exe.Memory 31MS
	Exe.Time 2688K
	Code Len. 866B
	
*/
