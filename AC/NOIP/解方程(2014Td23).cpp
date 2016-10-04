#include<cstdio>
#include<cstring>
const int N=105,M=1e4+5,P[]={9887,9901,9907,9923,9929,9931,9941,9949,9967,9973};
int A[10][N]={0},f[10][M],ans[N];
char str[M];
int main(){
//	freopen("equation.in","r",stdin);
//	freopen("equation.out","w",stdout);
	int n,m,tot=0;
	scanf("%d %d",&n,&m);
	for(int k=0;k<=n;++k){
		scanf("%s",str);
		bool flag=str[0]=='-';
		int len=strlen(str);
		for(int i=(int)flag;i<len;++i)
			for(int j=0;j<10;++j)
				A[j][k]=((A[j][k]<<3)+(A[j][k]<<1)+(str[i]^48))%P[j];
		if(flag)
			for(int i=0;i<10;++i)
				A[i][k]=P[i]-A[i][k];
	}
	for(int i=0;i<10;++i)
		for(int j=0;j<P[i];++j){
			f[i][j]=(A[i][n]*j+A[i][n-1])%P[i];
			for(int k=n-1;k;--k)
				f[i][j]=(f[i][j]*j+A[i][k-1])%P[i];
		}
	for(int i=1;i<=m;++i){
		int j;
		for(j=0;j<10;++j)
			if(f[j][i%P[j]])break;
		if(j==10)ans[tot++]=i;
	}
	printf("%d\n",tot);
	for(int i=0;i<tot;++i)
		printf("%d\n",ans[i]);
	return 0;
}

/*
	
	Oct.29.15
	Score:40
	
	Memory 1096K
	Time 297MS
	Code Length 0.95K
	
*/
