#include<cstdio>
#include<cstring>
const int N=4e4+5;
int n,prime[N],mob[N];
bool is_prime[N];
inline int sqr(int x){
	return x*x;
}
void sieve(){
	memset(is_prime,true,n);
	--n;
	is_prime[0]=is_prime[1]=false;
	mob[1]=1;
	int ans=sqr(n)+2;
	for(int i=2,tot_prime=0;i<=n;++i){
		if(is_prime[i]){
			prime[tot_prime++]=i;
			mob[i]=-1;
		}
		ans+=mob[i]*sqr(n/i);
		for(int j=0,mul;j<tot_prime&&(mul=i*prime[j])<=n;++j){
			is_prime[mul]=false;
			if(i%prime[j])mob[mul]=-mob[i];
			else{
				mob[mul]=0;
				break;
			}
		}
	}
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&n);
	if(n==1){
		puts("0");
		return 0;
	}
	sieve();
	return 0;
}
/*
	
	Apr.25.16
	
	Tags:Mathematics,Number Theory
	Submissions:1
	
	Memory 1156kb
	Time 24ms
	Code Length 711B
	
*/
