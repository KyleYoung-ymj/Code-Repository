#include<cstdio>
const int P=1e4+7;
struct Matrix{
	static const int sz=3;
	int num[sz][sz];
	Matrix(){
		for(int i=0;i<sz;++i)
			for(int j=0;j<sz;++j)
				num[i][j]=0;
	}
	void operator =(const bool &tmp){
		for(int i=0;i<sz;++i)
			for(int j=0;j<sz;++j)
				num[i][j]=i==j&tmp;
	}
	Matrix operator *(const Matrix &tmp)const{
		Matrix res;
		for(int i=0;i<sz;++i)
			for(int j=0;j<sz;++j)
				for(int k=0;k<sz;++k)
					res.num[i][j]=(res.num[i][j]+num[i][k]*tmp.num[k][j])%P;
		return res;
	}
	Matrix operator ^(int &b)const{
		Matrix mat=*(this),res;
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
	int cas,n;
	scanf("%d",&cas);
	Matrix mat;
	mat.num[0][0]=2;mat.num[0][1]=1;mat.num[0][2]=0;
	mat.num[1][0]=2;mat.num[1][1]=2;mat.num[1][2]=2;
	mat.num[2][0]=0;mat.num[2][1]=1;mat.num[2][2]=2;
	while(cas--){
		scanf("%d",&n);
		printf("%d\n",(mat^n).num[0][0]);
	}
	return 0;
}
/*
	
	Jan.09.16
	
	Tags:dp,matrix
	Submissions:1
	
	Memory 164K
	Time 0MS
	Code Length 939B
	
*/
