#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+5,MX=1e5,mod=258280327;
int n,mx,cnt[N]={0},pow_2[N],fact[N],inv[N],prime[N],mob[N],f[2][N],F[2][N];
bool is_prime[N];
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}
inline int calc_inv(int x){
	return fast_mod_pow(x,mod-2);
}
void init(){
	memset(is_prime,true,sizeof is_prime);
	mob[1]=fact[0]=inv[0]=pow_2[0]=1;
	for(int i=1,tot_prime=0;i<=MX;++i){
		pow_2[i]=2ll*pow_2[i-1]%mod;
		fact[i]=1ll*fact[i-1]*i%mod;
		inv[i]=calc_inv(fact[i]);
		if(i==1)continue;
		if(is_prime[i]){
			prime[tot_prime++]=i;
			mob[i]=-1;
		}
		for(int j=0,mul;j<tot_prime&&(mul=i*prime[j])<=MX;++j){
			is_prime[mul]=false;
			if(i%prime[j])mob[mul]=-mob[i];
			else{
				mob[mul]=0;
				break;
			}
		}
	}
}
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline int A(int n,int m){
	return 1ll*fact[n]*inv[n-m]%mod;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
	else if(a<0)a+=mod;
}
void calc(){
	for(int i=1;i<=mx;++i){
		F[0][i]=0;
		for(int j=1;j<=cnt[i];++j)
			F[0][i]=(F[0][i]+1ll*A(cnt[i],j)*fact[n+1-j])%mod;
		F[1][i]=1ll*cnt[i]*pow_2[cnt[i]-1]%mod;
	}
	for(int i=1;i<=mx;++i){
		for(int j=0;j<2;++j){
			f[j][i]=0;
			for(int k=i;k<=mx;k+=i){
				if(!mob[k/i])continue;
				mod_add(f[j][i],mob[k/i]*F[j][k]);
			}
		}
	}
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
void solve(){
	mx=0;
	for(int i=0,num;i<n;++i){
		rd(num);
		Max(mx,num);
		++cnt[num];
	}
	for(int i=1;i<=mx;++i)
		for(int j=i<<1;j<=mx;j+=i)
			cnt[i]+=cnt[j];
	calc();
	int ans[2]={0};
	for(int i=1;i<=mx;++i)
		for(int j=0;j<2;++j){
			if(!f[j][i])continue;
			ans[j]=(ans[j]+1ll*i*f[j][i])%mod;
		}
	if(ans[0]>ans[1])printf("Mr. Zstu %d\n",ans[0]);
	else if(ans[1]>ans[0])printf("Mr. Hdu %d\n",ans[1]);
	else printf("Equal %d\n",ans[0]);
	memset(cnt,0,mx+1<<2);
}
int main(){
	init();
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	Jun.23.16
	
	Tags:math,mobius
	Submissions:1
	
	Memory(KB) 5076
	Time(ms) 717
	Length(Bytes) 2051
	
*/
