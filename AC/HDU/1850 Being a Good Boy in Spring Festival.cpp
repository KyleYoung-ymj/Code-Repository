#include<cstdio>
const int N=105;
int num[N];
int main(){
	int n;
	while(scanf("%d",&n),n){
		int sum=0,ans=0;
		for(int i=0;i<n;++i){
			scanf("%d",&num[i]);
			sum^=num[i];
		}
		for(int i=0;i<n;++i)
			ans+=(sum^num[i])<num[i];
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	May.18.16
	
	Tags:Game Theory,Nim
	Submissions:1
	
	Exe.Time 0MS
	Exe.Memory 1404K
	Code Len. 284B
	
*/
