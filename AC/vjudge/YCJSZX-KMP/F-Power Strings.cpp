#include<cstdio>
#include<cstring>
const int N=1e6+5;
char str[N];
int n,f[N]={0};
void get_fail(){
	for(int i=1;i<n;++i){
		int j=f[i];
		while(j&&str[i]!=str[j])j=f[j];
		f[i+1]=str[i]==str[j]?j+1:0;
	}
}
int main(){
	while(~scanf("%s",str)){
		if(str[0]=='.')return 0;
		n=strlen(str);
		get_fail();
		printf("%d\n",!(n%(n-f[n]))?n/(n-f[n]):1);
	}
}
/*
	
	Nov.25.15
	Submit:2
	
	Memory 5248KB
	Time 110ms
	Code Length 352B
	
*/
