#include<cstdio>
#include<cstring>
const int N=1e5+5;
char str[N<<1],sub[N];
int n,m,f[N]={0};
void get_fail(){
	for(int i=1;i<m;++i){
		int j=f[i];
		while(j&&sub[i]!=sub[j])j=f[j];
		f[i+1]=sub[i]==sub[j]?j+1:0;
	}
}
bool KMP(){
	get_fail();
	int j=0;
	for(int i=0;i<n;++i){
		while(j&&str[i]!=sub[j])j=f[j];
		if(str[i]==sub[j])++j;
		if(j==m)return true;
	}
	return false;
}
int main(){
	while(~scanf("%s %s",str,sub)){
		n=strlen(str);
		m=strlen(sub);
		if(m>n){
			puts("no");
			continue;
		}
		for(int i=0;i<n;++i)
			str[n+i]=str[i];
		n<<=1;
		puts(KMP()?"yes":"no");
	}
	return 0;
}
/*
	Nov.25.15
	Submit:12
	
	Memory 1752KB
	Time 0ms
	Code Length 594B
	
*/
