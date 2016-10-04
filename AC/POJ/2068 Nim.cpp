#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int TOT=8200,N=15;
int n,num[N<<1];
int win[TOT][N<<1];
int solve(int tot,int cur){
	if(!tot)return true;
	int &res=win[tot][cur];
	if(~res)return res;
	res=false;
	int nxt=cur==n-1?0:cur+1;
	for(int i=1;i<=num[cur];++i){
		if(tot<i)break;
		if(!solve(tot-i,nxt)){
			res=true;
			break;
		}
	}
	return res;
}
int main(){
	while(scanf("%d",&n),n){
		n<<=1;
		int tot;
		scanf("%d",&tot);
		for(int i=0;i<n;++i)
			scanf("%d",&num[i]);
		memset(win,-1,sizeof(win));
		puts(solve(tot,0)?"1":"0");
	}
	return 0;
}
/*
	
	May.20.16
	
	Tags:Game Theory
	Submissions:2
	
	Memory 1564K
	Time 32MS
	Code Length 592B
	
*/
