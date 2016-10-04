#include<cstdio>
const int N=1e6+5,M=1e4+5;
int n,m,A[N],B[M],f[M];
void get_fail(){
	f[0]=f[1]=0;
	for(int i=1;i<m;++i){
		int j=f[i];
		while(j&&B[i]!=B[j])j=f[j];
		f[i+1]=B[i]==B[j]?j+1:0;
	}
}
int KMP(){
	get_fail();
	int j=0;
	for(int i=0;i<n;++i){
		while(j&&A[i]!=B[j])j=f[j];
		if(A[i]==B[j])++j;
		if(j==m)return i-m+2;
	}
	return -1;
}
int main(){
	int cas;
	scanf("%d",&cas);
	f[0]=f[1]=0;
	while(cas--){
		scanf("%d %d",&n,&m);
		for(int i=0;i<n;++i)
			scanf("%d",&A[i]);
		for(int i=0;i<m;++i)
			scanf("%d",&B[i]);
		printf("%d\n",KMP());
	}
	return 0;
}
/*
	
	Mar.09.16
	
	Problem:HDU1711
	
*/
