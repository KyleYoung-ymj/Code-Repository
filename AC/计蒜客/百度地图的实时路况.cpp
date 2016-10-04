#include<cstdio>
#include<cstring>
#include<cassert>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=305,LG=10,INF=1e9;
int n;
ll ans=0;
int mat[LG][N][N];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(a==-1||b<a)a=b;
}
void solve(int L,int R,int dep){
	if(L==R){
		for(int i=1;i<=n;++i){
			if(i==L)continue;
			for(int j=1;j<=n;++j){
				if(j==L)continue;
				ans+=mat[dep][i][j];
			}
		}
		return;
	}
	int mid=L+R>>1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			mat[dep+1][i][j]=mat[dep][i][j];
	for(int k=mid+1;k<=R;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(mat[dep+1][i][k]!=-1&&mat[dep+1][k][j]!=-1)
					Min(mat[dep+1][i][j],mat[dep+1][i][k]+mat[dep+1][k][j]);
	solve(L,mid,dep+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			mat[dep+1][i][j]=mat[dep][i][j];
	for(int k=L;k<=mid;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(mat[dep+1][i][k]!=-1&&mat[dep+1][k][j]!=-1)
					Min(mat[dep+1][i][j],mat[dep+1][i][k]+mat[dep+1][k][j]);
	solve(mid+1,R,dep+1);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			scanf("%d",&mat[0][i][j]);
		}
	solve(1,n,0);
	cout<<ans<<endl;
	return 0;
}