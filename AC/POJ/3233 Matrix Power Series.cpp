#include<cstdio>
#include<cstring>
const int N=205;
int n,P;
struct Matrix{
	int num[N][N];
	inline Matrix(){
		memset(num,0,sizeof(num));
	}
	inline int* operator [](const int id){
		return num[id];
	}
	void operator =(const int tmp){
		for(int i=0;i<n<<1;++i)
			for(int j=0;j<n<<1;++j)
				num[i][j]=i==j*tmp;
	}
	Matrix operator *(const Matrix &tmp)const{
		Matrix res;
		for(int i=0;i<n<<1;++i)
			for(int j=0;j<n<<1;++j)
				for(int k=0;k<n<<1;++k)
					res[i][j]=(res[i][j]+num[i][k]*tmp.num[k][j])%P;
		return res;
	}
	Matrix operator ^(int b)const{
		Matrix mat=*this,res;
		res=1;
		while(b){
			if(b&1)res=res*mat;
			mat=mat*mat;
			b>>=1;
		}
		return res;
	}
};
int main(){
	int m;
	scanf("%d%d%d",&n,&m,&P);
	Matrix mat;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j){
			scanf("%d",&mat.num[i][j]);
			if(i==j)mat[i+n][j]=mat[i+n][j+n]=1;
		}
	mat=mat^m+1;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j){
			int ans=mat[i+n][j];
			if(i==j){
				--ans;
				if(ans<0)ans+=P;
			}
			printf("%d%c",ans,j==n-1?'\n':' ');
		}
	return 0;
}
/*
	
	Jan.09.16
	
	Tags:classic,matrix
	Submissions:1
	
	Memory 1148K
	Time 641MS
	Code Length 1046B
	
*/
