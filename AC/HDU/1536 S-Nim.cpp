#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=105,NUM=1e4+5;
int tot,arr[N],SG[NUM];
bool mark[NUM]={false};
void init(){
	SG[0]=0;
	for(int i=1;i<NUM;++i){
		for(int j=0;j<tot&&i-arr[j]>=0;++j)
			mark[SG[i-arr[j]]]=true;
		for(int j=0;;++j){
			if(!mark[j]){
				SG[i]=j;
				break;
			}
		}
		for(int j=0;j<tot&&i-arr[j]>=0;++j)
			mark[SG[i-arr[j]]]=false;
	}
}
void solve(){
	int n,num,sum=0;
	scanf("%d",&n);
	while(n--&&scanf("%d",&num))
		sum^=SG[num];
	putchar(sum?'W':'L');
}
int main(){
	while(scanf("%d",&tot),tot){
		for(int i=0;i<tot;++i)
			scanf("%d",&arr[i]);
		sort(arr,arr+tot);
		init();
		int cas;
		scanf("%d",&cas);
		while(cas--)solve();
		putchar('\n');
	}
	return 0;
}
/*
	
	May.18.16
	
	Tags:Game Theory,SG
	Submissions:1
	
	Exe.Time 140MS
	Exe.Memory 1456K
	Code Len. 777B
	
*/
