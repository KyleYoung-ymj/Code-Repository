#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
const int N=1e5+5,P=99999997;
int n,ans=0,A[N],a[N],B[N],b[N];
map<int,int>mp;
void Rd(int &res){
	res=0;
	char c;
	while(c=getchar(),!isdigit(c));
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),isdigit(c));
}
void merge_cnt(int L,int R){
	if(L==R)return;
	int mid=L+R>>1,i=L,j=mid+1,k=L;
	merge_cnt(L,mid);
	merge_cnt(mid+1,R);
	while(i<=mid&&j<=R){
		if(B[i]<B[j])a[k++]=B[i++];
		else{
			ans=(ans+mid-i+1)%P;
			a[k++]=B[j++];
		}
	}
	while(i<=mid)a[k++]=B[i++];
	while(j<=R)a[k++]=B[j++];
	for(i=L;i<=R;++i)
		B[i]=a[i];
}
int main(){
//	freopen("match.in","r",stdin);
//	freopen("match.out","w",stdout);
	Rd(n);
	for(int i=0;i<n;++i){
		Rd(A[i]);
		a[i]=A[i];
	}
	for(int i=0;i<n;++i){
		Rd(B[i]);
		b[i]=B[i];
	}
	sort(a,a+n);
	sort(b,b+n);
	for(int i=0;i<n;++i){
		A[i]=lower_bound(a,a+n,A[i])-a;
		mp[A[i]]=i;
		B[i]=lower_bound(b,b+n,B[i])-b;
	}
	for(int i=0;i<n;++i)
		B[i]=mp[B[i]];
	merge_cnt(0,n-1);
	printf("%d\n",ans);
	return 0;
}
/*
	
	Oct.30.15
	Score:0
	
	Memory 5496K
	Time 187MS
	Code Length 1.11K
	
*/
