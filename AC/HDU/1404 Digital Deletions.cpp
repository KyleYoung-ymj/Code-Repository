#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int LEN=10,N=1e6+5;
char str[LEN];
bool SG[N];
void update(int n,int len){
	for(int i=1,pow_10=1;i<=len;++i,pow_10*=10){
		int num=n/pow_10%10;
		for(int j=num+1;j<10;++j)
			SG[n+(j-num)*pow_10]=1;
	}
	for(int i=len,pow_10=1;i<6;++i,pow_10*=10){
		n*=10;
		for(int j=0;j<pow_10;++j)
			SG[n+j]=1;
	}
}
void init(){
	memset(SG,0,sizeof(SG));
	for(int i=1,len=1,pow_10=10;;++i){
		if(i==pow_10){
			if(++len==7)return;
			pow_10*=10;
		}
		if(!SG[i])update(i,len);
	}
}
int main(){
	init();
	while(~scanf("%s",str)){
		if(str[0]=='0')puts("Yes");
		else{
			int num=0;
			for(int i=0,len=strlen(str);i<len;++i)
				(num*=10)+=str[i]-'0';
			puts(SG[num]?"Yes":"No");
		}
	}
	return 0;
}
/*
	
	May.18.16
	
	Tags:Game Theory,SG
	Submissions:2
	
	Exe.Time 624MS
	Exe.Memory 2388K
	Code Len. 808B
	
*/
