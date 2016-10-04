#include<cstdio>
#include<cstring>
const int N=105,M=15,S_MAX=65;
int m,tot=0,pat[N]={0},status[S_MAX],amt[S_MAX],dp[N][S_MAX][S_MAX];
char mp[M];
void pre_pro(int c,int sum,int S){
	if(c>=m){
		status[tot]=S;
		amt[tot++]=sum;
		return;
	}
	pre_pro(c+1,sum,S);
	pre_pro(c+3,sum+1,S|1<<c);
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
void solve_1(){
	int ans=0;
	for(int i=0;i<tot;++i)
		if((pat[0]|status[i])==pat[0])
			Max(ans,amt[i]);
	printf("%d\n",ans);
}
int solve(int row,int pre_S,int S){
	int &res=dp[row][pre_S][S];
	if(res==-1)
		if(row==1)
			res=amt[S]+amt[pre_S];
		else
			for(int i=0;i<tot;++i)
				if((pat[row-2]|status[i])==pat[row-2]&&!(status[i]&status[pre_S])&&!(status[i]&status[S]))//WA:must compare i with S again!
					Max(res,solve(row-1,i,pre_S)+amt[S]);
	return res;
}
int main(){
	int n,ans=0;
	scanf("%d%d",&n,&m);
	pre_pro(0,0,0);
	for(int i=0;i<n;++i){
		scanf("%s",mp);
		for(int j=0;j<m;++j)
			pat[i]|=(mp[j]=='P')<<j;
	}
	if(n==1){
		solve_1();
		return 0;
	}
	memset(dp,-1,sizeof(dp));
	for(int S=0;S<tot;++S)
		for(int pre_S=0;pre_S<tot;++pre_S)
			if((pat[n-1]|status[S])==pat[n-1]&&(pat[n-2]|status[pre_S])==pat[n-2]&&!(status[S]&status[pre_S]))
				Max(ans,solve(n-1,pre_S,S));
	printf("%d\n",ans);
	return 0;
}
/*
	
	Dec.18.15
	
	Tags:dp,classic
	Submissions:2
	Bug Data:
		6 10
		PPPPPPPPPP
		PPPPPPPPPP
		PPPPPPPPPP
		PPPPPPPPPP
		HHHHHHHHHH
		PPPPPPPPPP
		Ans:17
	
	Memory 2124K
	Time 391MS
	Code Length 1224B
	
*/
