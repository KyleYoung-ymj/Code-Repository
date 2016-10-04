#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e4+5,NEG_INF=0x80000000;
int n,L,R,num[N],memo[N];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int solve(int cur){
	int &res=memo[cur];
	if(~res)return res;
	int mx=NEG_INF;
	for(int i=lower_bound(num+cur+1,num+n,num[cur]+L)-num;i<n;++i){
		if(num[i]-num[cur]>R)break;
		Max(mx,solve(i));
	}
	return res=num[cur]-(mx>NEG_INF)*mx;
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		scanf("%d%d%d",&n,&L,&R);
		for(int i=0;i<n;++i){
			scanf("%d",&num[i]);
			memo[i]=-1;
		}
		sort(num,num+n);
		n=unique(num,num+n)-num;
		int ans=NEG_INF;
		for(int i=lower_bound(num,num+n,L)-num;i<n;++i){
			if(num[i]>R)break;
			Max(ans,solve(i));
		}
		printf("%d\n",(ans>NEG_INF)*ans);
	}
	return 0;
}
/*
	
	May.20.16
	
	Tags:Game Theory
	Submissions:3
	
	Memory 448K
	Time 16MS
	Code Length 771B
	
*/
