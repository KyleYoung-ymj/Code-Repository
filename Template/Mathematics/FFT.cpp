#include <cstdio>
#include <cmath>
#include <complex>
#include <algorithm>
using namespace std;
const int N=(1<<18)+5;
const double pi=acos(-1.0);
typedef complex<double> Com;
int rev[N];
Com A[N],B[N],C[N];
template<class T>void rd(T &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
		while(c=getchar(),c>47);
}
void DFT(Com *arr,int n,int sgn){
	for(int i=0;i<n;++i)
		if(i<rev[i])
			swap(arr[i],arr[rev[i]]);
	for(int m=2;m<=n;m<<=1){
		Com wm(cos(2*pi/m),sgn*sin(2*pi/m));
		for(int i=0;i<n;i+=m){
			Com w(1,0);
			for(int j=0;j<m>>1;++j,w*=wm){
				Com x=arr[i+j],y=w*arr[i+j+(m>>1)];
				arr[i+j]=x+y;
				arr[i+j+(m>>1)]=x-y;
			}
		}
	}
}
void FFT(int n,int m){
	int _n,S;
	for(_n=1,S=0;_n<n+m;_n<<=1,++S);
	for(int i=1;i<_n;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<S-1);
	for(int i=n;i<_n;++i)
		A[i]=0;
	for(int i=m;i<_n;++i)
		B[i]=0;
	DFT(A,_n,1);
	DFT(B,_n,1);
	for(int i=0;i<_n;++i)
		C[i]=A[i]*B[i];
	DFT(C,_n,-1);
	for(int i=0;i<n+m;++i)
		C[i]/=_n;
}
int main(){
	int n,m,S;
	rd(n);rd(m);
	++n;++m;
	for(int i=0,tmp;i<n;++i){
		rd(tmp);
		A[i]=tmp;
	}
	for(int i=0,tmp;i<m;++i){
		rd(tmp);
		B[i]=tmp;
	}
	FFT(n,m);
	for(int i=0;i<=n+m-2;++i)
		printf("%d%c",(int)(C[i].real()+0.5)," \n"[i==n+m-2]);
	return 0;
}
/*
	
	Jul.21.16

	Problem:UOJ #34
	
*/
