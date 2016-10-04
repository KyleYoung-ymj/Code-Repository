#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5e4+5;
int k,prime[N],mob[N],sum[N];
bool is_prime[N];
void Mobius(){
	memset(is_prime,true,N);
	sum[0]=0;
	sum[1]=mob[1]=1;
	for(int i=2,cnt=0;i<N;++i){
		if(is_prime[i]){
			prime[cnt++]=i;
			mob[i]=-1;
		}
		sum[i]=sum[i-1]+mob[i];
		for(int j=0,mul;j<cnt&&(mul=i*prime[j])<N;++j){
			is_prime[mul]=false;
			if(i%prime[j])mob[mul]=-mob[i];
			else{
				mob[mul]=0;
				break;
			}
		}
	}
}
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>=48);
}
int solve(int n,int m){
	if(n>m)swap(n,m);
	n/=k;m/=k;
	if(!n)return 0;
	int res=0;
	for(int d=1,last;d<=n;d=last+1){
		last=min(n/(n/d),m/(m/d));
		res+=(sum[last]-sum[d-1])*(n/d)*(m/d);
	}
	return res;
}
int main(){
	int cas,a,b,c,d;
	rd(cas);
	Mobius();
	while(cas--){
		rd(a);rd(b);rd(c);rd(d);rd(k);
		printf("%d\n",solve(b,d)-solve(a-1,d)-solve(b,c-1)+solve(a-1,c-1));
	}
	return 0;
}
/*
	
	Apr.11.16
	
	Tags:Mathematics,Mobius Inversion
	Submissions:1
	
	Memory 1440kb
	Time 10308ms
	Code Length 1171B
	
*/
