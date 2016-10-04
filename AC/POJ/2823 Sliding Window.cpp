#include<cstdio>
const int N=1e6+5;
int n,m,num[N],deque[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
		scanf("%d",&num[i]);
	int s=0,t=0;
	for(int i=0;i<n;++i){
		while(s<t&&num[deque[t-1]]>=num[i])--t;
		deque[t++]=i;
		while(deque[s]<i-m+1)++s;
		if(i>=m-1){
			printf("%d",num[deque[s]]);
			if(i<n-1)putchar(' ');
			else putchar('\n');
		}
	}
	s=t=0;
	for(int i=0;i<n;++i){
		while(s<t&&num[deque[t-1]]<=num[i])--t;
		deque[t++]=i;
		while(deque[s]<i-m+1)++s;
		if(i>=m-1){
			printf("%d",num[deque[s]]);
			if(i<n-1)putchar(' ');
			else putchar('\n');
		}
	}
	return 0;
}
/*
	
	Dec.27.15
	
	Tags:Double-Ended Queue
	Submissions:2
	TLE:Using G++ instead of C++
	
	Memory 4080K
	Time 5891MS
	Code Length 594B
	
*/
