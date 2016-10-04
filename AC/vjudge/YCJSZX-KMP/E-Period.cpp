#include<cstdio>
const int N=1e6+5;
char str[N];
int f[N]={0};
int main(){
	int n,kase=0;
	while(scanf("%d",&n)&&n){
		scanf("%s",str);
		for(int i=1;i<n;++i){
			int j=f[i];
			while(j&&str[i]!=str[j])j=f[j];
			f[i+1]=str[i]==str[j]?j+1:0;
		}
		printf("Test case #%d\n",++kase);
		for(int i=2;i<=n;++i)
			if(f[i]&&!(i%(i-f[i])))printf("%d %d\n",i,i/(i-f[i]));
		puts("");
	}
	return 0;
}
/*
	
	Nov.24.15
	Submit:1
	
	Memory 3296KB
	Time 109ms
	Code Length 391B
	
*/
