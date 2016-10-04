#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e3+5;
int num[N];
inline bool cmp(int a,int b){
	return a>b;
}
int main(){
	int cas,n;
	scanf("%d",&cas);
	while(cas--&&scanf("%d",&n)){
		for(int i=0;i<n;++i)
			scanf("%d",&num[i]);
		sort(num,num+n,cmp);
		num[n]=0;
		int sum=0;
		for(int i=0;i<n;i+=2)
			sum^=num[i]-num[i+1]-1;
		puts(sum?"Georgia will win":"Bob will win");
	}
	return 0;
}
/*
	
	May.19.16
	
	Tags:Staircase Nim
	Submissions:1
	
	Memory 164K
	Time 0MS
	Code Length 416B
	
*/
