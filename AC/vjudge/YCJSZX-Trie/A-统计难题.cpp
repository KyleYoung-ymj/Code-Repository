#include<cstdio>
#include<cstring>
const int N=8e5+5;
int allc=0,pre[N][26]={0},pass[N]={0};
char str[15];
int main(){
	while(gets(str)){
		int len=strlen(str);
		if(!len)break;
		int cur=0;
		for(int i=0;i<len;++i){
			if(!pre[cur][str[i]-'a'])
				pre[cur][str[i]-'a']=++allc;
			cur=pre[cur][str[i]-'a'];
			++pass[cur];
		}
	}
	while(gets(str)){
		int len=strlen(str),cur=0;
		for(int i=0;i<len;++i){
			cur=pre[cur][str[i]-'a'];
			if(!cur)break;
		}
		printf("%d\n",pass[cur]);
	}
	return 0;
}
/*
	
	Submit:1
	Nov.19.15
	
	Memory 40548KB
	Time 31ms
	Code Length 499B
	
*/
