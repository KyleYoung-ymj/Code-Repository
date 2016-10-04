#include<cstdio>
#include<cctype>
#include<cstring>
const int N=1005;
char str[N],sub[N];
int n,m,f[N]={0};
char get_visible(){
	char c;
	while(c=getchar(),isspace(c));
	return c;
}
void get_fail(){
	for(int i=1;i<m;++i){
		int j=f[i];
		while(j&&f[i]!=f[j])j=f[j];
		f[i+1]=f[i]==f[j]?j+1:0;
	}
}
int KMP(){
	get_fail();
	int j=0,res=0;
	for(int i=0;i<n;++i){
		while(j&&str[i]!=sub[j])j=f[j];
		if(str[i]==sub[j])++j;
		if(j==m){
			++res;
			j=0;
		}
	}
	return res;
}
int main(){
	char c;
	while(true){
		str[0]=get_visible();
		if(str[0]=='#')return 0;
		scanf("%s %s",str+1,sub);
		n=strlen(str);
		m=strlen(sub);
		printf("%d\n",KMP());
	}
}
/*
	
	Nov.23.15
	Submit:1
	
	Memory 1412KB
	Time 0ms
	Code Length 648B
	
*/
