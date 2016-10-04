#include<cstdio>
typedef long long ll;
ll phi(int n){
	ll res=n;
	for(int i=2;1ll*i*i<=n;++i){
		if(!(n%i)){
			res=res/i*(i-1);
			while(!(n%i))n/=i;
		}
	}
	if(n>1)res=res/n*(n-1);
	return res;
}
int main(){
	ll n;
	scanf("%lld",&n);
	ll sqr,ans=0;
	for(int i=1;(sqr=1ll*i*i)<=n;++i){
		if(!(n%i)){
			ans+=phi(i)*n/i;
			if(sqr<n)ans+=phi(n/i)*i;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
/*
	
	Apr.25.16
	
	Tags:Number Theory
	Submissions:3
	
	Memory 804kb
	Time 12ms
	Code Length 472B
	
*/
