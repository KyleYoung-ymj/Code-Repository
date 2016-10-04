#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1005;
char str[N];
struct bigint{
	static const int BASE=1e4;
	int num[N],len;
	bigint(){
		memset(num,0,sizeof(num));
		len=0;
	}
	void rd(){
		memset(num,0,sizeof(num));
		len=0;
		scanf("%s",str);
		for(int i=strlen(str)-1;i>=0;i-=4){
			int res=0;
			for(int j=max(0,i-3);j<=i;++j)
				res=(res<<3)+(res<<1)+(str[j]^48);
			num[len++]=res;
		}
	}
	void print(){
		printf("%d",num[len-1]);
		for(int i=len-2;i>=0;--i)
			printf("%04d",num[i]);
	}
	bigint operator +(bigint const &tmp)const{
		bigint res;
		res.len=max(len,tmp.len);
		for(int i=0;i<res.len;++i){
			res.num[i]+=num[i]+tmp.num[i];
			if(res.num[i]>=BASE){
				res.num[i]-=BASE;
				++res.num[i+1];
			}
		}
		if(res.num[res.len])++res.len;
		return res;
	}
}a,b,sum;
int main(){
	int cas;
	scanf("%d",&cas);
	for(int i=0;i<cas;++i){
		a.rd();
		b.rd();
		sum=a+b;
		printf("Case %d:\n",i+1);
		a.print();
		printf(" + ");
		b.print();
		printf(" = ");
		sum.print();
		if(i<cas-1)puts("\n");
		else puts("");
	}
	return 0;
}
/*
	
	Nov.06.15
	Submit:2
	
	Exe.Time 0MS
	Exe.Memory 1580K
	Code Len. 1161B
	
*/
