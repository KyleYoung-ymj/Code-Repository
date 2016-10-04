#include<cstdio>
#include<cstring>
const int LEN=5e4+5;
typedef unsigned long long ull;
const ull B=1e9+7;
char str[LEN],sub[LEN];
int n,m;
void solve(){
	n=strlen(str);
	m=strlen(sub);
	int mx=0,en=n<m?n:m;
	ull pow=1,hash0=0,hash1=0;
	for(int i=0;i<en;++i){
		hash0=hash0*B+str[i];
		hash1+=sub[m-i-1]*pow;
		pow*=B;
		if(hash0==hash1)mx=i+1;
	}
	if(!mx)puts("0");
	else{
		for(int i=0;i<mx;++i)
			printf("%c",str[i]);
		printf(" %d\n",mx);
	}
}
int main(){
	while(~scanf("%s%s",str,sub))
		solve();
	return 0;
}
/*
	
	Nov.27.15
	Submit:1
	
	Memory 1504KB
	Time 15ms
	Code Length 515B
	
*/
