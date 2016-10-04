#include<cstdio>
int main(){
	int cas,n,num;
	scanf("%d",&cas);
	while(cas--&&scanf("%d",&n)){
		bool flag=false;
		int SG=0;
		while(n--&&scanf("%d",&num)){
			SG^=num;
			if(num>1)flag=true;
		}
		puts(SG&&flag||!SG&&!flag?"John":"Brother");
	}
	return 0;
}
/*
	
	May.18.16
	
	Tags:Game Theory,Anti-Nim
	Submissions:1
	
	Exe.Time 0MS
	Exe.Memory 1408K
	Code Len. 273B
	
*/
