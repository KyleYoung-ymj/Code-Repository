#include<cstdio>
#include<cstring>
const int N=1e5+5,M=35;
char str[N],sub[M];
int main(){
	scanf("%s%s",str,sub);
	int n=strlen(str),m=strlen(sub),ans=0;
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j){
			if(str[i+j]!=sub[j])break;
			if(j==m-1){
				str[i+j]='#';
				++ans;
			}
		}
	printf("%d\n",ans);
	return 0;
}
/*
	
	Feb.07.16
	
	Tags:String,Brute force
	Submissions:5
	
	Time 15ms
	Memory 0KB
	
*/
