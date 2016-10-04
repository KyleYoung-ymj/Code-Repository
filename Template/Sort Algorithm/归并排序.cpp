#include<cstdio>
const int M=1005;
int num[M],tmp[M];
void merge_sort(int L,int R){
	if(L==R)return;
	int mid=L+R>>1;
	merge_sort(L,mid);
	merge_sort(mid+1,R);
	int i=L,j=mid+1,k=L;
	while(i<=mid&&j<=R)
		if(num[i]<=num[j])tmp[k++]=num[i++];
		else tmp[k++]=num[j++];
	while(i<=mid)tmp[k++]=num[i++];
	while(j<=R)tmp[k++]=num[j++];
	for(int i=L;i<=R;i++)
		num[i]=tmp[i];
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&num[i]);
	merge_sort(0,n-1);
	for(int i=0;i<n;i++)
		printf("%d ",num[i]);
	puts("");
	return 0;
}
