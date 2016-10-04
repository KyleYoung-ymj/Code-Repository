#include<cstdio>
const int N=5e5+5;
int n,m,sum[N],dp[N],deque[N];
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>=48);
}
inline int sqr(int x){
	return x*x;
}
inline int f(int x){
	return dp[x]+sqr(sum[x]);
}
inline int get_up(int a,int b){
	return f(b)-f(a);
}
inline int get_down(int a,int b){
	return sum[b]-sum[a];
}
int main(){
	int tmp;
	dp[0]=sum[0]=0;
	while(~scanf("%d",&n)){
		rd(m);
		int head=0,rear=-1;
		deque[++rear]=0;
		for(int i=1;i<=n;++i){
			rd(tmp);
			sum[i]=sum[i-1]+tmp;
			while(head<rear&&get_up(deque[head],deque[head+1])<=sum[i]*get_down(deque[head],deque[head+1])<<1)++head;	
			dp[i]=dp[deque[head]]+sqr(sum[i]-sum[deque[head]])+m;
			while(head<rear&&get_up(deque[rear-1],i)*get_down(deque[rear-1],deque[rear])<=get_up(deque[rear-1],deque[rear])*get_down(deque[rear-1],i))--rear;
			deque[++rear]=i;
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
/*
	
	Jan.19.16
	
	Tags:dp,slope,deque,classic
	Submissions:7
	
	Exe.Time 280MS
	Exe.Memory 7520K
	Code Len. 994B
	
*/
