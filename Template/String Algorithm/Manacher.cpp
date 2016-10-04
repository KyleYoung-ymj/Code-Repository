#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int LEN=11e4+5;
int p[LEN<<1]={0};
char org[LEN],str[LEN<<1];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int Manacher(){
	int mx=0,id=0,ans=1;
	for(int i=1;str[i];++i){
		p[i]=mx>i?min(p[(id<<1)-i],mx-i):1;
		while(str[i-p[i]]==str[i+p[i]])++p[i];
		Max(ans,p[i]-1);
		if(i+p[i]>mx){
			mx=i+p[i];
			id=i;
		}
	}
	return ans;
}
int main(){
	str[0]='#';
	while(~scanf("%s",org)){
		int n=strlen(org),ptr=1;
		for(int i=0;i<n;++i){
			str[ptr++]='$';
			str[ptr++]=org[i];
		}
		str[ptr++]='$';
		str[ptr]=0;
		printf("%d\n",Manacher());
	}
	return 0;
}
/*
	
	Mar.04.16
	
	Problem:HDU3068
	
*/
