#include<cstdio>
#include<algorithm>
using namespace std;
const int N=105,M=1e4+5,INF=1e9;
int n,m,x,p,num[N][M],sum[N][M],dp[N][M];
struct Deque{
    int head,tail,pos[M],val[M];
    inline void init(){
        head=tail=0;
    }
	void push(int idx,int x){
		while(head<tail&&val[tail-1]<=x)--tail;
		pos[tail]=idx;
		val[tail++]=x;
	}
	inline int front(){
		return val[head];
	}
	void remove(int idx){
		if(pos[head]==idx)++head;
	}
}deque;
void pre_pro(){
	for(int i=1;i<=m;++i)
		dp[1][i]=-INF;
	int tmp=dp[1][x]=num[1][x];
	for(int i=x+1;i-x<=p&&i<=m;++i){
		tmp+=num[1][i];
		dp[1][i]=tmp;
	}
	tmp=num[1][x];
	for(int i=x-1;x-i<=p&&i;--i){
		tmp+=num[1][i];
		dp[1][i]=tmp;
	}
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int main(){
	while(~scanf("%d%d%d%d",&n,&m,&x,&p)){
		for(int i=1;i<=n;++i){
			sum[i][0]=0;
			for(int j=1;j<=m;++j){
				scanf("%d",&num[i][j]);
				sum[i][j]=sum[i][j-1]+num[i][j];
			}
		}
		pre_pro();
		int ans=-INF;
		if(n==1)
			for(int j=1;j<=m;++j)
				Max(ans,dp[1][j]);
		for(int i=1;i<n;++i){
			for(int j=1;j<=m;++j)
				dp[i+1][j]=dp[i][j]+num[i+1][j];
			deque.init();
			for(int j=1;j<m;++j){
				deque.push(j,dp[i][j]-sum[i+1][j-1]);
				Max(dp[i+1][j+1],deque.front()+sum[i+1][j+1]);
				if(i==n-1)Max(ans,dp[i+1][j+1]);
				if(j>=p)deque.remove(j-p+1);
			}
			deque.init();
			for(int j=m;j>=2;--j){
				deque.push(m-j,dp[i][j]+sum[i+1][j]);
				Max(dp[i+1][j-1],deque.front()-sum[i+1][j-2]);
				if(i==n-1)Max(ans,dp[i+1][j-1]);
				if(j<=m-p+1)deque.remove(m-j-p+1);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	Dec.31.15
	
	Tags:dp,deque,classic
	Submissions:3
	
	Exe.Time 608MS
	Exe.Memory 12008K
	Code Len. 1640B
	
*/
