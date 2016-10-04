#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int M=1005;
char str[M];
struct BigInt{
	int num[M],len;
	BigInt(){
		memset(num,0,sizeof(num));
		len=0;
	}
	void Rd(){
		scanf("%s",str);
		for(int i=strlen(str)-1;i>=0;i-=4){
			int tmp=0;
			for(int j=max(0,i-3);j<=i;j++)
				tmp=tmp*10+str[j]-'0';
			num[len++]=tmp;
		}
	}
	void Print(){
		printf("%d",num[len-1]);
		for(int i=len-2;i>=0;i--)
			printf("%04d",num[i]);
		puts("");
	}
	BigInt operator +(const BigInt &tmp)const{
		BigInt res;
		res.len=max(len,tmp.len);
		for(int i=0;i<res.len;i++){
			res.num[i]+=num[i]+tmp.num[i];
			if(res.num[i]>=10000){
				res.num[i]-=10000;
				res.num[i+1]++;
			}
		}
		if(res.num[res.len])res.len++; 
		return res;
	}
	BigInt operator *(const BigInt &tmp)const{
		BigInt res;
		for(int i=0;i<len;i++)
			for(int j=0;j<tmp.len;j++){
				res.num[i+j]+=num[i]*tmp.num[j];
				if(res.num[i+j]>=10000){
					res.num[i+j+1]+=res.num[i+j]/10000;
					res.num[i+j]%=10000;
				}
			}
		res.len=len+tmp.len-1;
		if(res.num[res.len])res.len++;
		while(res.len>=2&&!res.num[res.len-1])res.len--;
		return res;
	}
};
int main(){
	BigInt A,B,sum,pro;
	A.Rd();
	B.Rd();	
	sum=A+B;
	pro=A*B;
	sum.Print(); 
	pro.Print();
	return 0;
}
