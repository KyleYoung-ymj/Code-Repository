#include<cstdio>
const int M=100005;
int sum[M];
int main(){
	int n,m,a,b,ans=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		sum[a]++,sum[b+1]--;
	}
	for(int i=1;i<=n;i++){
		ans+=sum[i];
		printf("%d ",ans);
	}
	puts("");
	return 0;
}
/*
	Memory 988K
	Time 110MS
	Code Length 0.27K
*/
