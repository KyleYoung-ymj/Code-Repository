#include<cstdio>
#include<cstring>
#include<algorithm>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
const int N=1e3+5;
int dp[N][N];
char str[N];
pii dir[100],pos[2][N];
void init(){
	dir['N']=pii(0,1);
	dir['S']=pii(0,-1);
	dir['W']=pii(-1,0);
	dir['E']=pii(1,0);
}
inline int sqr(int x){
	return x*x;
}
inline int dist(int a,int b){
	return sqr(pos[0][a].fi-pos[1][b].fi)+sqr(pos[0][a].se-pos[1][b].se);
}
inline void Min(int &a,int b){
	if(a==-1||b<a)a=b;
}
int main(){
	freopen("radio.in","r",stdin);
	freopen("radio.out","w",stdout);
	int len[2];
	for(int i=0;i<2;++i)
		scanf("%d",&len[i]);
	init();
	for(int i=0;i<2;++i)
		scanf("%d%d",&pos[i][0].fi,&pos[i][0].se);
	for(int k=0;k<2;++k){
		scanf("%s",str);
		for(int i=0;i<len[k];++i){
			pos[k][i+1]=pii(pos[k][i].fi+dir[str[i]].fi,pos[k][i].se+dir[str[i]].se);
		}
	}
	memset(dp,-1,sizeof dp);
	dp[0][0]=0;
	for(int i=0;i<len[0];++i)
		for(int j=0;j<len[1];++j){
			Min(dp[i+1][j],dp[i][j]+dist(i+1,j));
			Min(dp[i][j+1],dp[i][j]+dist(i,j+1));
			Min(dp[i+1][j+1],dp[i][j]+dist(i+1,j+1));
		}
	printf("%d\n",dp[len[0]][len[1]]);
	return 0;
}
