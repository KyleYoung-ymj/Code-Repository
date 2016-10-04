#include<cstdio>
#include<cctype>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e4+5,M=1e3+5,INF=0x7fffffff;
void Rd(int &res){
	res=0;
	char c;
	while(c=getchar(),!isdigit(c));
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),isdigit(c));
}
int n,m,cnt=0,X[N],Y[N],L[N],H[N],dp[2][M];
bool cur=0,nxt=1,flag[N]={0};
inline void check(int &a,int b){
	if(a==-1||b<a)a=b;
}
bool lose(int k){
	for(int i=L[k]+1;i<H[k];++i)
		if(dp[cur][i]!=-1)return false;
	return true;
}
void solve(){
	for(int i=1;i<=m;++i)
		dp[cur][i]=0;
	for(int i=0;i<n;++i){
		for(int j=1;j<=m;++j)
			dp[nxt][j]=-1;
		for(int j=L[i]+1;j<H[i];++j){
			if(dp[cur][j]==-1)continue;
			int to=min(m,j+X[i]);
			check(dp[nxt][to],dp[cur][j]+1);
		}
		for(int j=X[i]+1;j<=m;++j)
			if(dp[nxt][j-X[i]]!=-1)
				check(dp[nxt][j],dp[nxt][j-X[i]]+1);
		for(int j=m-X[i]+1;j<m;++j)
			if(dp[nxt][j]!=-1)
				check(dp[nxt][m],dp[nxt][j]+1);
		for(int j=Y[i]+1;j<H[i];++j)
			if(dp[cur][j]!=-1)
				check(dp[nxt][j-Y[i]],dp[cur][j]);
		for(int j=0;j<=L[i+1];++j)
			dp[nxt][j]=-1;
		for(int j=H[i+1];j<=m;++j)
			dp[nxt][j]=-1;
		cur^=1;
		nxt^=1;
		if(lose(i+1))break;
		if(flag[i+1])++cnt;
	}
}
int main(){
//	freopen("bird.in","r",stdin);
//	freopen("bird.out","w",stdout);
	int t;
	Rd(n);Rd(m);Rd(t);
	for(int i=0;i<n;++i){
		Rd(X[i]);
		Rd(Y[i]);
	}
	for(int i=0;i<=n;++i){
		L[i]=0;
		H[i]=m+1;
	}
	int p,l,h;
	for(int i=0;i<t;++i){
		Rd(p);Rd(l);Rd(h);
		flag[p]=true;
		L[p]=l;
		H[p]=h;
	}
	solve();
	if(cnt==t){
		int ans=INF;
		for(int i=1;i<=m;++i)
			if(dp[cur][i]!=-1)
				check(ans,dp[cur][i]);
		printf("1\n%d\n",ans);
	}
	else printf("0\n%d\n",cnt);
	return 0;
}
/*
	
	Oct.31.15
	Score:75
	
	Memory 940K
	Time 125MS
	Code Length 1.71K
	
*/
