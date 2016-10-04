#include<cstdio>
const int N=15e3+5,M=32e3+5;
int bit[M]={0},ans[N]={0};
void add(int k,int x){
	while(k<M){
		bit[k]+=x;
		k+=k&-k;
	}
}
int sum(int k){
	int res=0;
	while(k){
		res+=bit[k];
		k&=k-1;
	}
	return res;
}
int main(){
	int n,x,y;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d%d",&x,&y);
		++ans[sum(++x)];
		add(x,1);
	}
	for(int i=0;i<n;++i)
		printf("%d\n",ans[i]);
	return 0;
}
/*
	
	Dec.14.15
	
	Tags:Data Structure,BIT
	Submissions:1
	
	Memory 568K
	Time 391MS
	Code Length 400B
	
*/
