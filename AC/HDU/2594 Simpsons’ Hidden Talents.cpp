#include<cstdio>
#include<cstring>
const int N=5e4+5;
char str0[N],str1[N];
int n,m,f[N]={0};
void get_fail(){
	for(int i=1;i<n;++i){
		int j=f[i];
		while(j&&str0[i]!=str0[j])j=f[j];
		f[i+1]=str0[i]==str0[j]?j+1:0;
	}
}
void solve(){
	n=strlen(str0);
	m=strlen(str1);
	get_fail();
	int j=0;
	for(int i=0;i<m;++i){
		while(j&&str1[i]!=str0[j])j=f[j];
		if(str1[i]==str0[j])++j;
	}
	if(!j)puts("0");
	else{
		for(int i=0;i<j;++i)
			printf("%c",str0[i]);
		printf(" %d\n",j);
	}
}
int main(){
	while(~scanf("%s%s",str0,str1))
		solve();
	return 0;
}
/*
	
	Nov.27.15
	Submit:1
	
	Exe.Time 15MS
	Exe.Memory 1700K
	Code Len. 581B
	
*/
