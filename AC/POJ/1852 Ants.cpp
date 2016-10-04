#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF=1e6+5;
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int main(){
	int cas,tot,n,tmp;
	scanf("%d",&cas);
	while(cas--){
		scanf("%d%d",&tot,&n);
		int mi=0,mx=0;
		while(n--){
			scanf("%d",&tmp);
			Max(mi,min(tmp,tot-tmp));
			Max(mx,max(tmp,tot-tmp));
		}
		printf("%d %d\n",mi,mx);
	}
	return 0;
}
/*
	
	Dec.12.15
	
	Tags:Greedy
	Submissions:1
	
	Memory 708K
	Time 125MS
	Code Length 391B
	
*/
