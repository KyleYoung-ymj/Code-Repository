#include<cstdio>
const int N=205;
int A[N],B[N],ans_a=0,ans_b=0;
void judge(int a,int b){
	if(a==b)return;
	if(a==1&&b==0
	 ||a==0&&b==2
	 ||a==2&&b==1
	 ||a==0&&b==3
	 ||a==1&&b==3
	 ||a==3&&b==2
	 ||a==4&&b==0
	 ||a==4&&b==1
	 ||a==2&&b==4
	 ||a==3&&b==4)
		++ans_a;
	else ++ans_b;
}
int main(){
//	freopen("rps.in","r",stdin);
//	freopen("rps.out","w",stdout);
	int n,a,b;
	scanf("%d %d %d",&n,&a,&b);
	for(int i=0;i<a;++i)
		scanf("%d",&A[i]);
	for(int i=0;i<b;++i)
		scanf("%d",&B[i]);
	for(int i=0;i<n;++i)
		judge(A[i%a],B[i%b]);
	printf("%d %d\n",ans_a,ans_b);
	return 0;
}
/*
	
	Oct.29.15
	Socre:100
	
	Memory 692K
	Time 16MS
	Code Length 0.60K
	
*/
