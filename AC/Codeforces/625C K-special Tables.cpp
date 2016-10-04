#include<cstdio>
const int N=505;
int num[N][N]; 
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int cnt=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<m;++j)
			num[i][j]=cnt++;
	for(int i=1;i<=n;++i)
		for(int j=m;j<=n;++j)
			num[i][j]=cnt++;
	cnt=0;
	for(int i=1;i<=n;++i)
		cnt+=num[i][m];
	printf("%d\n",cnt);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			printf("%d%c",num[i][j],j==n?'\n':' ');
		}
	}
	return 0;
}
/*
	
	Feb.07.16
	
	Tags:YY,Mathematics
	Submissions:1
	
	Time 78ms
	Memory 800KB
	
*/
