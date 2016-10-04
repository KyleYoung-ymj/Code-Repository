#include<cstdio>
#include<cstring>
const int N=1e4+5,M=1e6+5;
char sub[N],str[M];
int n,m,f[N];
void get_fail(){
	for(int i=1;i<n;++i){
		int j=f[i];
		while(j&&sub[j]!=sub[i])j=f[j];
		f[i+1]=sub[j]==sub[i]?j+1:0;
	}
}
int KMP(){
	get_fail();
	int j=0,res=0;
	for(int i=0;i<m;++i){
		while(j&&str[i]!=sub[j])j=f[j];
		if(str[i]==sub[j])++j;
		if(j==n)++res;
	}
	return res;
}
int main(){
	int cas;
	scanf("%d",&cas);
	f[0]=f[1]=0;
	while(cas--){
		scanf("%s %s",sub,str);
		n=strlen(sub);
		m=strlen(str);
		printf("%d\n",KMP());
	}
	return 0;
}
/*
	
	Nov.23.15
	Submit:1
	
	Memory 2424KB
	Time 124ms
	Code Length 546B
	
*/
