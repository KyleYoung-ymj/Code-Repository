#include<cstdio>
const int N=1e5+5;
int main(){
//	freopen("block.in","r",stdin);
//	freopen("block.out","w",stdout);
	int n,now,h=0,ans=0;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&now);
		if(now>h)ans+=now-h;
		h=now;
	}
	printf("%d\n",ans);
	return 0;
}
/*
	
	Nov.01.15
	Score 100
	
	Memory 692K
	Time 47MS
	Code Length 0.27K
	
*/
