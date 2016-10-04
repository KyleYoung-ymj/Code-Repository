#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e7+5;
int mod,tot_prime,fact[N],prime[N],phi[N];
bool is_prime[N];
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}
inline int mod_inverse(int x){
	return fast_mod_pow(x,mod-2);
}
void pre_pro(){
	tot_prime=0;
	memset(is_prime,true,N);
	is_prime[0]=is_prime[1]=false;
	fact[0]=fact[1]=phi[1]=1;
	for(int i=2;i<N;++i){
		fact[i]=1ll*fact[i-1]*i%mod;
		if(is_prime[i]){
			prime[tot_prime++]=i;
			phi[i]=1ll*phi[i-1]*(i-1)%mod*mod_inverse(i)%mod;
		}
		else phi[i]=phi[i-1];
		for(int j=0,mul;j<tot_prime&&(mul=i*prime[j])<N;++j){
			is_prime[mul]=false;
			if(!(i%prime[j]))break;
		}
	}
}
void solve(){
	int n,m;
	scanf("%d%d",&n,&m);
	printf("%d\n",1ll*fact[n]*phi[m]%mod);
}
int main(){
	int cas;
	scanf("%d%d",&cas,&mod);
	pre_pro();
	while(cas--)solve();
	return 0;
}
/*
	
	Apr.25.15
	
	Tags:Mathematics,Number Theory,Euler Phi
	Submissions:3
	
	Memory 127760kb
	Time 9636ms
	Code Length 1069B
	
*/
