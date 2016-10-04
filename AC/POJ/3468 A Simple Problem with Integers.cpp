#include<cstdio>
const int N=1e5+5;
typedef long long ll;
int n;
ll bit0[N]={0},bit1[N]={0};
ll sum(ll *b,int k){
	ll ans=0;
	while(k){
		ans+=b[k];
		k&=k-1;
	}
	return ans;
}
void add(ll *b,int k,ll x){
	while(k<=n){
		b[k]+=x;
		k+=k&-k;
	}
}
int main(){
	int m,L,R;
	char str[5];
	ll x;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%I64d",&x);
		add(bit0,i,x);
	}
	while(m--){
		scanf("%s%d%d",str,&L,&R);
		if(str[0]=='C'){
			scanf("%I64d",&x);
			add(bit0,L,x*(1-L));
			add(bit0,R+1,x*R);
			add(bit1,L,x);
			add(bit1,R+1,-x);
		}
		else{
			x=sum(bit0,R)+sum(bit1,R)*R;
			x-=sum(bit0,L-1)+sum(bit1,L-1)*(L-1);
			printf("%I64d\n",x);
		}
	}
	return 0;
}
/*
	
	Dec.13.15
	
	Tags:Data Structure,BIT
	Submissions:1
	
	Memory 1944K
	Time 1875MS
	Code Length 674B
	
*/
