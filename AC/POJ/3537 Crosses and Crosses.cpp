#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e3+5;
int SG[N];
bool vis[N];
void calc_SG(int n){
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;++i)
		vis[SG[max(i-3,0)]^SG[max(n-i-2,0)]]=true;
	for(SG[n]=0;;++SG[n]){
		if(!vis[SG[n]])return;
	}
}
int main(){
	int n;
	scanf("%d",&n);
	SG[0]=0;
	for(int i=1;i<=n;++i)
		calc_SG(i);
	printf("%d\n",SG[n]?1:2);
	return 0;
}
/*
	
	May.19.16
	
	Tags:Game Theory,SG
	Submissions:1
	
	Memory 176K
	Time 110MS
	Code Length 417B
	
*/
