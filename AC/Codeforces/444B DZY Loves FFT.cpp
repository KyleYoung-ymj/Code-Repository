#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,d,x,A[N],C[N],pos[N];
bool B[N];
inline int get_x(){
	return x=(37ll*x+10007)%1000000007;
}
void init(){
	for(int i=0;i<n;++i)
		A[i]=i+1;
	for(int i=0;i<n;++i)
		swap(A[i],A[get_x()%(i+1)]);
	for(int i=0;i<n;++i)
		B[i]=i<d;
	for(int i=0;i<n;++i){
		C[i]=0;
		swap(B[i],B[get_x()%(i+1)]);
	}
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int main(){
	scanf("%d%d%d",&n,&d,&x);
	init();
	if(d<500){
		for(int i=0;i<n;++i){
			if(!B[i])continue;
			for(int j=0;i+j<n;++j)
				Max(C[i+j],A[j]);
		}
	}
	else{
		for(int i=0;i<n;++i){
			pos[A[i]]=i;
		}
		for(int i=0;i<n;++i){
			for(int j=n;j;--j){
				if(pos[j]<=i&&B[i-pos[j]]){
					C[i]=j;
					break;
				}
			}
		}
	}
	for(int i=0;i<n;++i)
		printf("%d\n",C[i]);
	return 0;
}
/*
	
	Jun.25.16
	
	Tags:brute force
	Submissions:2
	
	Time 171ms
	Memory 1100KB
	
*/
