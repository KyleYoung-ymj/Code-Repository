#include<cstdio>
const int N=1e5+5;
typedef long long ll;
int n,bit0[N]={0},bit1[N]={0};
int sum(int *b,int k){
	int res=0;
	while(k){
		res+=b[k];
		k&=k-1;
	}
	return res;
}
void add(int *b,int k,int x){
	while(k<=n){
		b[k]+=x;
		k+=k&-k;
	}
}
int query(int k){
	ll res;
	res=sum(bit0,k)+1LL*sum(bit1,k)*k;
	res-=sum(bit0,k-1)+sum(bit1,k-1)*(k-1);
	return (int)res;
}
int main(){
	int L,R;
	while(~scanf("%d",&n)&&n){
		for(int i=0;i<n;++i){
			scanf("%d%d",&L,&R);
			add(bit0,L,1-L);
			add(bit0,R+1,R);
			add(bit1,L,1);
			add(bit1,R+1,-1);
		}
		for(int i=1;i<n;++i)
			printf("%d ",query(i));
		printf("%d\n",query(n));
		for(int i=1;i<=n;++i)
			bit0[i]=bit1[i]=0;
	}
	return 0;
}
/*
	
	Dec.13.15
	
	Tags:Data Structure,BIT
	Submissions:2
	
	Exe.Time 748MS
	Exe.Memory 2180K
	Code Len. 731B
	
*/
