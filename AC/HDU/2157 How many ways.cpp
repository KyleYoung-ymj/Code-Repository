#include<cstdio>
#include<cstring>
const int N=25,P=1000;
int n;
struct Matrix{
	int num[N][N];
	void operator =(const int &tmp){
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				num[i][j]=(i==j)*tmp;
	}
	Matrix operator *(const Matrix &tmp)const{
		Matrix res;
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j){
				res.num[i][j]=0;
				for(int k=0;k<n;++k)
					res.num[i][j]=(res.num[i][j]+num[i][k]*tmp.num[k][j])%P;
			}
		return res;
	}
};
Matrix fast_mod_pow(Matrix mat,int b){
	Matrix res;
	res=1;
	while(b){
		if(b&1)res=res*mat;
		mat=mat*mat;
		b>>=1;
	}
	return res;
}
int main(){
	int m,a,b,c,cas;
	while(~scanf("%d%d",&n,&m)&&n+m){
		Matrix mat;
		mat=0;
		while(m--){
			scanf("%d%d",&a,&b);
			mat.num[a][b]=1;
		}
		scanf("%d",&cas);
		while(cas--){
			scanf("%d%d%d",&a,&b,&c);
			printf("%d\n",fast_mod_pow(mat,c).num[a][b]);
		}
	}
	return 0;
}
/*
	
	Dec.27.15
	
	Tags:Graph Theory,Mathematics,Matrix
	Submissions:1
	
	Exe.Time 171MS
	Exe.Memory 1408K
	Code Len. 911B
	
*/
