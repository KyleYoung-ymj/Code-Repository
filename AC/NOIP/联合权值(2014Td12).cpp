#include<cstdio>
#include<cctype>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N=2e5+5,P=1e4+7;
void Rd(int &res){
	res=0;
	char c;
	while(c=getchar(),!isdigit(c));
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),isdigit(c));
}
vector<int>G[N];
int val[N];
int main(){
//	freopen("link.in","r",stdin);
//	freopen("link.out","w",stdout);
	int n,x,y,mx=0,mod_sum=0;
	Rd(n);
	for(int i=0;i<n-1;++i){
		Rd(x);Rd(y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int i=1;i<=n;++i)
		Rd(val[i]);
	for(int i=1;i<=n;++i){
		int sum=0,sz=G[i].size(),mx0=0,mx1=0;
		for(int j=0;j<sz;++j){
			int to=G[i][j];
			mod_sum=(P+(mod_sum-val[to]*val[to])%P)%P;
			sum=(sum+val[to])%P;
			if(val[to]>mx0){
				mx1=mx0;
				mx0=val[to];
			}
			else if(val[to]>mx1)mx1=val[to];
		}
		mod_sum=(mod_sum+1LL*sum*sum)%P;
		mx=max(mx,mx1*mx0);
	}
	printf("%d %d\n",mx,mod_sum);
	return 0;
}
/*
	
	Oct.29.15
	Score:60
	
	Memory 7804K
	Time 172MS
	Code Length 0.94K
	
*/
