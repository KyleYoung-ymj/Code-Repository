#include<cstdio>
const int N=1005,MX=1000005;
int num[N],A[10][N];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		int tmp;
		scanf("%d",&tmp);
		num[i]=tmp+MX;
	}
	int d=1,len[10];
	for(int i=0;i<7;++i){
		for(int j=0;j<10;++j)len[j]=0;
		for(int j=0;j<n;++j){
			int k=num[j]/d%10;
			A[k][len[k]++]=num[j];
		}
		int cnt=0;
		for(int j=0;j<10;++j)
			for(int k=0;k<len[j];++k)
				num[cnt++]=A[j][k];
		d*=10;
	}
	for(int i=0;i<n;++i)
		printf("%d ",num[i]-MX);
	puts("");
	return 0;
}
