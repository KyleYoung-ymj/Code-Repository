#include<cstdio>
typedef __int64 ll;
ll calc(ll n){
	if(n<=1)return n;
	ll k;
	for(int i=0;;++i){
		if((1ll<<i)>n){
			k=i;
			break;
		}
	}
	ll cnt=(1ll<<k-2)+1;
	k=1ll<<k-1;
	if(k==n)return cnt;
	return cnt+(n-(k+1)+1)-(calc(k-1)-calc(2*k-n-1));
}
void solve(){
	ll L,R;
	scanf("%I64d%I64d",&L,&R);
	printf("%I64d\n",calc(R)-calc(L-1));
}
int main(){
	int cas,kase=0;
	scanf("%d",&cas);
	while(cas--)solve();
	return 0;
}
/*
	
	May.21.16
	
	Tags:implementation
	Submissions:3
	
	Exe.Time 46MS
	Exe.Memory 1404K
	Code Len. 449B
	
*/
