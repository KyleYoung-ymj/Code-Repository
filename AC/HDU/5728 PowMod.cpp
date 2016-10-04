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
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
typedef complex<double> Com;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
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
int fast_mod_pow(int a,int b,int mod){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}
const int N=(int)1e7+5;
bool is_prime[N];
int tot_prime,prime[N],phi[N],sum[N];
void sieve(){
	memset(is_prime,true,N);
	sum[1]=phi[1]=1;
	for(int i=2;i<N;++i){
		if(is_prime[i]){
			prime[tot_prime++]=i;
			phi[i]=i-1;
		}
		for(int j=0,prod;j<tot_prime&&(prod=i*prime[j])<N;++j){
			is_prime[prod]=false;
			if(i%prime[j])phi[prod]=phi[i]*phi[prime[j]];
			else{
				phi[prod]=phi[i]*prime[j];
				break;
			}
		}
		sum[i]=sum[i-1];
		mod_add(sum[i],phi[i]);
	}
}
inline int sqr(int x){
	return x*x;
}
int S(int n,int m){
	if(!m)return 0;
	if(n==1)return sum[m];
	int p=-1;
	for(int i=0;sqr(prime[i])<n;++i){
		if(!(n%prime[i])){
			p=prime[i];
			break;
		}
	}
	if(p==-1)p=n;
	return (1ll*phi[p]*S(n/p,m)+S(n,m/p))%mod;
}
int solve(int K,int p){
	if(p==1)return 0;
	return fast_mod_pow(K,phi[p]+solve(K,phi[p]),p);
}
int main(){
	int n,m,p;
	for(sieve();~scanf("%d%d%d",&n,&m,&p);){
		if(p==1){
			puts("0");
			continue;
		}
		int K=S(n,m);
		if(K==1){
			puts("1");
			continue;
		}
		printf("%d\n",solve(K,p));
	}
	return 0;
}
/*
	
	Jul.22.16

	Tags:number theory,Euler phi,recursion
	Submissions:1

	Exe.Time 280MS
	Exe.Memory 92248K
	Code Len. 2540B

*/
