#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int LEN=1e5+5,SUB_LEN=1e3+5;
char str[LEN],sub[SUB_LEN];
int len,sub_len,pre[LEN],suf[LEN],L[LEN]={0},R[LEN]={0};
void get_fail(){
	suf[sub_len]=suf[sub_len-1]=sub_len;
	for(int i=2;i<=sub_len;++i){
		int j=pre[i];
		while(j>1&&sub[i]!=sub[j])j=pre[j];
		pre[i+1]=sub[i]==sub[j]?j+1:1;
	}
	for(int i=sub_len-1;i;--i){
		int j=suf[i];
		while(j<sub_len&&sub[i]!=sub[j])j=suf[j];
		suf[i-1]=sub[i]==sub[j]?j-1:sub_len;
	}
}
bool judge(){
	if(sub_len==1)return false;
	get_fail();
	int j=1;
	for(int i=1;i<=len;++i){
		while(j>1&&str[i]!=sub[j])j=pre[j];
		if(str[i]==sub[j])++j;
		L[i]=max(L[i-1],j-1);
	}
	j=sub_len;
	for(int i=len;i;--i){
		while(j<sub_len&&str[i]!=sub[j])j=suf[j];
		if(str[i]==sub[j])--j;
		R[i]=max(R[i+1],sub_len-j);
	}
	bool flag=false;
	for(int i=1;i<=len;++i)
		if(L[i-1]+R[i]==sub_len||L[i]+R[i+1]==sub_len){
			flag=true;
			break;
		}
	for(int i=0;i<=len+1;++i)
		L[i]=R[i]=0;
	return flag;
}
int main(){
	int n,ans=0;
	scanf("%s%d",str+1,&n);
	len=strlen(str+1);
	pre[1]=pre[2]=1;
	while(n--){
		scanf("%s",sub+1);
		sub_len=strlen(sub+1);
		ans+=judge();
	}
	printf("%d\n",ans);
	return 0;
}
/*
	
	Nov.27.15
	Submit:3
	
	Memory 1672KB
	Time 310ms
	Code Length 1221B
	
*/
