#include<cstdio>
typedef long long ll;
inline void Max(ll &a,ll b){
	if(b>a)a=b;
}
int main(){
	ll n,a,b,c;
	scanf("%I64d%I64d%I64d%I64d",&n,&a,&b,&c);
	ll ans=n/a;
	if(n%a>=b)ans+=(n%a-c)/(b-c);
	if(n>=b){
		ll tmp=(n-c)/(b-c);
		if(n-tmp*(b-c)>0)tmp+=(n-tmp*(b-c))/a;
		Max(ans,tmp);
	}
	printf("%I64d\n",ans);
	return 0;
}
/*
	
	Feb.07.16
	
	Tags:Methematics
	Submissions:3
	
	Time 15ms
	Memory 0KB
	
*/
