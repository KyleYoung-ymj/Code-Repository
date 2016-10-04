#include<cstdio>
const int N=5e4+5,LG=20;
int num[N],lg[N],f[N][LG];
inline bool isdigit(char c){
	return c>='0'&&c<='9';
}
inline int max(int a,int b){
	return a>b?a:b;
}
int main(){
	int n,m,L,R,cnt=1;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&num[i]);
		f[i][0]=num[i];
	}
	for(int j=1;1<<j<=n;++j)
		for(int i=1;i+(1<<j)-1<=n;++i)
			f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
	lg[1]=0;
	for(int i=2;i<=n+1;++i){
		lg[i]=cnt;
		if(!(i&(i-1)))++cnt;
	}
	while(m--){
		scanf("%d %d",&L,&R);
		int k=lg[R-L+2]-1;
		printf("%d\n",max(f[L][k],f[R-(1<<k)+1][k]));
	}
	return 0;
}
/*
	
	Oct.29.15
	
*/
