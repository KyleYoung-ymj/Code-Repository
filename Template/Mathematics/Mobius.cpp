#include<cstdio>
#include<cstring>
const int M=1e5+5;
bool is_prime[M];
int cnt=0,prime[M],mob[M];
void Mobius(){
	memset(is_prime,true,sizeof(is_prime));
	mob[1]=1;
	for(int i=2;i<M;i++){
		if(is_prime[i]){
			prime[cnt++]=i;
			mob[i]=-1;
		}
		for(int j=0;j<cnt&&i*prime[j]<M;j++){
			is_prime[i*prime[j]]=false;
			if(i%prime[j])mob[i*prime[j]]=-mob[i];
			else{
				mob[i*prime[j]]=0;
				break;
			}
		}
	}
}
