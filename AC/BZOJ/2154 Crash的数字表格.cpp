#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e7+5,mod=20101009;
bool is_prime[N];
int prime[N],f[N],sum[N];
void sieve(){
    memset(is_prime,true,N);
    is_prime[0]=is_prime[1]=false;
    sum[0]=0;
    sum[1]=f[1]=1;
    for(int i=2,tot_prime=0;i<N;++i){
        if(is_prime[i]){
            prime[tot_prime++]=i;
            f[i]=(i-1ll*i*i)%mod+mod;
        }
        if((sum[i]=sum[i-1]+f[i])>=mod)sum[i]-=mod;
        for(int j=0,mul;j<tot_prime&&(mul=i*prime[j])<N;++j){
            is_prime[mul]=false;
            if(i%prime[j])f[mul]=f[i]*(prime[j]-1ll*prime[j]*prime[j])%mod+mod;
            else{
                f[mul]=1ll*f[i]*prime[j]%mod;
                break;
            }
        }
    }
}
int fast_mod_pow(int a,int b){
    int res=1;
    for(;b;a=1ll*a*a%mod,b>>=1)
        if(b&1)res=1ll*res*a%mod;
    return res;
}
inline int Sum(int n,int m){
    return 1ll*n*(n+1)%mod*m%mod*(m+1)%mod*fast_mod_pow(4,mod-2)%mod;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    sieve();
    if(n>=m)swap(n,m);
    int ans=0;
    for(int i=1,last;i<=n;i=last+1){
        last=min(n/(n/i),m/(m/i));
        ans=(ans+1ll*Sum(n/i,m/i)*(sum[last]-sum[i-1]))%mod;
        if(ans<0)ans+=mod;
    }
    printf("%d\n",ans);
    return 0;
}
/*
	
	Apr.21.16
	
	Tags:Mathematics,Number Theory,Mobius Inversion
	Submissions:2
	
	Memory 127760kb
	Time 12952ms
	Code Length 1257B
	
*/
