#include<cstdio>
#include<cmath>
#include<cstring>
#include<complex>
#include<iostream>
#include<algorithm>
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
const int N=1e5+5,M=(1<<17)+5;
const long double pi=acos(-1.0);
typedef complex<long double> C;
typedef long long ll;
int sum[N],rev[M];
C A[M],B[M],ans[2][M];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
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
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(S-1));
	for(int i=_n+1;i<n;++i)
		A[i]=B[i]=0;
	FFT(A,n,1);
	FFT(B,n,1);
	for(int i=0;i<n;++i)
		ans[id][i]=A[i]*B[i];
	FFT(ans[id],n,-1);
	for(int i=0;i<=m;++i)
		ans[id][i]=ans[id][i].real()/n;
}
void solve(){
	int n;
	ll ans0=0;
	rd(n);
	sum[0]=0;
	for(int i=1,num,cnt=0;i<=n;++i){
		rd(num);
		sum[i]=sum[i-1]+num;
		if(!num){
			++cnt;
			ans0+=1ll*cnt*(cnt+1)/2;
		}
		else cnt=0;
	}
	printf("%I64d\n",ans0);
	for(int i=0;i<=sum[n];++i){
		A[i]=B[i]=0;
	}
	for(int i=1;i<=n;++i){
		A[sum[i]]+=i;
		B[-sum[i-1]+sum[n]]+=1;
	}
	calc_FFT(sum[n],0);
	for(int i=0;i<=sum[n];++i){
		A[i]=B[i]=0;
	}
	for(int i=1;i<=n;++i){
		A[sum[i]]+=1;
		B[-sum[i-1]+sum[n]]+=i-1;
	}
	calc_FFT(sum[n],1);
	for(int i=1;i<=sum[n];++i){
		printf("%I64d\n",(ll)(ans[0][i+sum[n]].real()-ans[1][i+sum[n]].real()+0.5));
	}
}
int main(){
	int cas;
	rd(cas);
	while(cas--)solve();
	return 0;
}
/*
	
	Jun.19.16
	
	Tags:math,FFT
	Submissions:4
	
	Memory(KB) 18864
	Time(ms) 3010
	Length(Bytes) 1798
	
*/
