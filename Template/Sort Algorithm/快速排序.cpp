#include<cstdio>
const int M=20005;
int num[M];
void qsort(int L,int R){
	int i=L,j=R,tmp=num[L];
	while(i<j){
		while(i<j&&tmp<=num[j])j--;
		if(i<j)num[i]=num[j];
		while(i<j&&tmp>=num[i])i++;
		if(i<j)num[j]=num[i];
	}
	num[i]=tmp;
	if(L<i-1)qsort(L,i-1);
	if(i+1<R)qsort(i+1,R);
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&num[i]);
	qsort(0,n-1);
	for(int i=0;i<n;i++)
		printf("%d ",num[i]);
	puts("");
	return 0;
}
