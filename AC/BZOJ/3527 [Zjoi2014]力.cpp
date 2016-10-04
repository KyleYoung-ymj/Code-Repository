#include<cstdio>
#include<cmath>
#include<complex>
#include<algorithm>
using namespace std;
typedef complex<double> C;
const int N=1e5+5,M=(1<<18)+5;
const double pi=acos(-1.0);
int rev[M];
C A[M],B[M],ans[2][M];
void FFT(C *arr,int n,int flag){
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
void calc_FFT(int n,bool id){
	int _n=n,m=n<<1,S=0;
	for(n=1;n<=m;n<<=1,++S);
	rev[0]=0;
	for(int i=1;i<n;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<S-1);
	for(int i=_n+1;i<n;++i)
		A[i]=B[i]=0;
	FFT(A,n,1);
	FFT(B,n,1);
	for(int i=0;i<n;++i)
		ans[id][i]=A[i]*B[i];
	FFT(ans[id],n,-1);
	for(int i=0;i<m;++i)
		ans[id][i]/=n;
}
double num[N];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%lf",&num[i]);
	for(int i=0;i<n;++i){
		A[i]=num[i];
		B[i]=1.0/(i+1)/(i+1);
	}
	calc_FFT(n-1,0);
	for(int i=0;i<n-1-i;++i)
		swap(num[i],num[n-1-i]);
	for(int i=0;i<n;++i){
		A[i]=num[i];
		B[i]=1.0/(i+1)/(i+1);
	}
	calc_FFT(n-1,1);
	for(int i=n-1;i;--i){
		ans[0][i]=ans[0][i-1];
		ans[1][i]=ans[1][i-1];
	}
	ans[0][0]=ans[1][0]=0;
	for(int i=0;i<n-1-i;++i)
		swap(ans[1][i],ans[1][n-1-i]);
	for(int i=0;i<n;++i)
		printf("%f\n",(ans[0][i]-ans[1][i]).real());
	return 0;
}
/*
	
	Jun.20.16
	
	Tags:FFT
	Submissions:1
	
	Memory 19000kb
	Time 8356ms
	Code Length 1639B
	
*/
