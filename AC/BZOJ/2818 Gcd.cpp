#include<cstdio>
#include<cstring>
const int N=1e7+5;
int n,tot_prime,prime[N],mob[N],sum[N]={0};
bool is_prime[N];
typedef long long ll;
void sieve(){
	tot_prime=0;
	memset(is_prime,true,n+1);
	is_prime[0]=is_prime[1]=true;
	mob[1]=1;
	for(int i=2;i<=n;++i){
		if(is_prime[i]){
			prime[tot_prime++]=i;
			mob[i]=-1;
		}
		for(int j=0,mul;j<tot_prime&&(mul=i*prime[j])<=n;++j){
			is_prime[mul]=false;
			if(i%prime[j])mob[mul]=-mob[i];
			else{
				mob[mul]=0;
				break;
			}
		}
	}
}
inline ll sqr(int x){
	return 1ll*x*x;
}
int main(){
	scanf("%d",&n);
	sieve();
	for(int i=0;i<tot_prime;++i)
		for(int j=prime[i],cnt=1;j<=n;j+=prime[i],++cnt)
			sum[j]+=mob[cnt];
	for(int i=1;i<=n;++i)
		sum[i]+=sum[i-1];
	ll ans=0;
	for(int D=1,last;D<=n;D=last+1){
		last=n/(n/D);
		ans+=sqr(n/D)*(sum[last]-sum[D-1]);
	}
	printf("%lld\n",ans);
	return 0;
}
/*
	
	Apr.25.16
	
	Tags:Number Theory
	Submissions:2
	
	Memory 127760kb
	Time 2800ms
	Code Length 987B
	
*/
