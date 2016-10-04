#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5,P=1e9+7;
int fact[N],rev[N];
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%P){
		if(b&1)res=1ll*res*a%P;
	}
	return res;
}
void init(){
	fact[0]=rev[0]=1;
	for(int i=1;i<N;++i){
		fact[i]=1ll*fact[i-1]*i%P;
		rev[i]=fast_mod_pow(fact[i],P-2);
	}
}
int C(int n,int m){
	int res=fact[n];
	res=1ll*res*rev[m]%P;
	res=1ll*res*rev[n-m]%P;
	return res;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=P)a-=P;
}
int main(){
	init();
	int n,m;
	while(~scanf("%d%d",&n,&m)){
		if(n>m)swap(n,m);
		int ans=0;
		for(int step=1;step<n;++step)
			mod_add(ans,1ll*C(n-2,step-1)*C(m-2,step-1)%P);
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	May.26.16
	
	Tags:Mathematics
	Submissions:1
	
	Exe.Time 62MS
	Exe.Memory 2188K
	Code Len. 858B
	
*/
