#include<cstdio>
#include<cmath>
#include<complex>
#include<algorithm>
using namespace std;
const int N=(1<<18)+5;
const double pi=acos(-1.0);
typedef complex<double> C;
int n,rev[N];
C A[N],B[N];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
void FFT(C *arr,int flag){
	for(int i=0;i<n;++i)
		if(i<rev[i])
			swap(arr[i],arr[rev[i]]);
	for(int m=2;m<=n;m<<=1){
		C wm(cos(2*pi/m),flag*sin(2*pi/m));
		for(int i=0;i<n;i+=m){
			C w(1,0);
			for(int j=0;j<m>>1;++j,w*=wm){
				C x=arr[i+j],y=w*arr[i+j+(m>>1)];
				arr[i+j]=x+y;
				arr[i+j+(m>>1)]=x-y;
			}
		}
	}
}
int main(){
	int m,S;
	rd(n);rd(m);
	for(int i=0,tmp;i<=n;++i){
		rd(tmp);
		A[i]=tmp;
	}
	for(int i=0,tmp;i<=m;++i){
		rd(tmp);
		B[i]=tmp;
	}
	m=n+m;
	for(n=1,S=0;n<=m;n<<=1,++S);
	rev[0]=0;
	for(int i=1;i<n;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(S-1));
	FFT(A,1);
	FFT(B,1);
	for(int i=0;i<=n;++i)
		A[i]*=B[i];
	FFT(A,-1);
	for(int i=0;i<=m;++i)
		printf("%d%c",(int)(A[i].real()/n+0.5)," \n"[i==m]);
	return 0;
}
/*
	
	Jun.18.16
	
	Tags:FFT
	Submissions:3
	
	Time 1051ms
	Memory 9848kb
	Code Length 1.1kb
	
	
*/
