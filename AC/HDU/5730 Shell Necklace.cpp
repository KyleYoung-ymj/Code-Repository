#include <cstdio>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb push_back
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
typedef complex<double> Com;
const int mod=313,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
template<class T>void rd(T &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_print(T x){
	if(!x)return;
	rec_print(x/10);
	putchar(x%10^48);
}
template<class T>void print(T x){
	if(!x)putchar('0');
	else rec_print(x);
}
template<class T>inline void Max(T &a,T b){
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b){
	if(b<a)a=b;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}
const int N=(int)1e5+5,M=(1<<18)+5;
int a[N],dp[N],rev[M];
Com A[M],B[M],C[M];
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
void conquer(int L,int R){
	int mid=L+R>>1,
		n=mid-L+1,m=R-L+1;
	for(int i=0;i<n;++i)
		A[i]=dp[L+i];
	for(int i=0;i<m;++i)
		B[i]=a[i];
	FFT(n,m);
	for(int i=mid+1,j=n;i<=R;++i,++j)
		dp[i]=(dp[i]+(ll)(C[j].real()+0.5))%mod;
}
void divide(int L,int R){
	if(L==R)return;
	int mid=L+R>>1;
	divide(L,mid);
	conquer(L,R);
	divide(mid+1,R);
}
void solve(int n){
	for(int i=1;i<=n;++i){
		rd(a[i]);
		a[i]%=mod;
	}
	memset(dp,0,n+1<<2);
	dp[0]=1;
	divide(0,n);
	print(dp[n]);
	putchar('\n');
}
int main(){
	int n;
	while(rd(n),n)solve(n);
	return 0;
}
