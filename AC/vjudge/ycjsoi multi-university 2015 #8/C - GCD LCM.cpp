#include<cstdio>
#include<cstring>
const int N=1e6+5,mod=258280327;
int prime[N],H[N],G[N],F[N],S[N];
bool is_prime[N];
void sieve(){
	memset(is_prime,true,N);
	H[1]=1;
	for(int i=2,tot_prime=0;i<N;++i){
		if(is_prime[i]){
			prime[tot_prime++]=i;
			H[i]=2;
		}
		for(int j=0,prod;j<tot_prime&&(prod=i*prime[j])<N;++j){
			is_prime[prod]=false;
			if(i%prime[j])H[prod]=H[i]<<1;
			else{
				H[prod]=H[i];
				break;
			}
		}
	}
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
void solve(){
	sieve();
	memset(G,0,N<<2);
	for(int d=1;d<N;++d){
		for(int k=1,n;(n=k*d)<N;++k){
			mod_add(G[n],H[k-1]);
		}
	}
	F[1]=S[1]=1;
	for(int n=2;n<N;++n){
		F[n]=((F[n-1]+(n<<1)-1-G[n-1])%mod+mod)%mod;
		if((S[n]=S[n-1]+F[n])>=mod)S[n]-=mod;
	}
}
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
int main(){
	int cas,n;
	rd(cas);
	solve();
	while(cas--){
		rd(n);
		printf("%d\n",S[n]);
	}
	return 0;
}
/*
	
	Jul.05.16
	
	Tags:number theory,sieve
	Submissions:1
	
	Memory(KB) 18340
	Time(ms) 234
	Length(Bytes) 990
	
*/
