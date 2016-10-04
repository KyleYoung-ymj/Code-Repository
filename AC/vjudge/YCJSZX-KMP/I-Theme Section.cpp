#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e6+5;
char str[N],sub[N/3];
int n,tot=0,f[N]={0},len[N/3];
void get_fail(){
	for(int i=1;i<n;++i){
		int j=f[i];
		while(j&&str[i]!=str[j])j=f[j];
		f[i+1]=str[i]==str[j]?j+1:0;
	}
	int j=f[n];
	while(true){
		len[tot++]=j;
		j=f[j];
		if(!j)break;
	}
}
bool judge(int sub_len){
	for(int i=0;i<sub_len;++i)
		sub[i]=str[i];
	bool flag=false;
	int j=0,en=n+1-sub_len;
	for(int i=sub_len;i<en;++i){
		while(j&&str[i]!=sub[j])j=f[j];
		if(str[i]==sub[j])++j;
		if(j==sub_len){
			flag=true;
			break;
		}
	}
	if(!flag)return false;
	for(int i=n-sub_len;i<n;++i)
		if(str[i]!=sub[i-n+sub_len])
			return false;
	return true;
}
int solve(){
	get_fail();
	for(int i=0;i<tot;++i){
		if(len[i]>n/3)continue;
		if(judge(len[i]))return len[i];
	}
	return 0;
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		scanf("%s",str);
		n=strlen(str);
		printf("%d\n",solve());
		tot=0;
	}
	return 0;
}
/*
	
	Nov.27.15
	Submit:2
	
	Memory 6776KB
	Time 46ms
	Code Length 1000B
	
*/
