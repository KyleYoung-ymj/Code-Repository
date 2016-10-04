#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		int n,m;
		scanf("%d%d",&n,&m);
		int ans=0;
		while(n&&m){
			if(n>m)swap(n,m);
			++ans;
			m-=n;
		}
		if(n==m)++ans;// actually meaningless
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	Mar.13.16
	
	Tags:water,implementation
	Submissions:1
	
	Exe.Time 15MS
	Exe.Memory 1408K
	Code Len. 377B
	
*/
