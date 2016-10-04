#include<cstdio>
#include<cstring>
const int N=1005,NODE=20005;
char str[N][25];
int len[N],allc=0,pre[NODE][26]={0},pass[NODE]={0};
int main(){
	int n;
	for(int i=0;;++i){
		if(!gets(str[i])){
			n=i;
			break;
		}
		len[i]=strlen(str[i]);
		int cur=0;
		for(int j=0;j<len[i];++j){
			if(!pre[cur][str[i][j]-'a'])
				pre[cur][str[i][j]-'a']=++allc;
			cur=pre[cur][str[i][j]-'a'];
			++pass[cur];
		}
	}
	for(int i=0;i<n;++i){
		printf("%s ",str[i]);
		int cur=0,res=1;
		for(int j=0;j<len[i];++j){
			if(pass[cur]>1)res=j+1;
			cur=pre[cur][str[i][j]-'a'];
		}
		for(int j=0;j<res;++j)
			printf("%c",str[i][j]);
		puts("");
	}
	return 0;
}
/*
	
	Nov.20.15
	Submit:4
	
	Memory 636KB
	Time 47ms
	Code Length 643B
	
*/
