#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int N=305,INF=1e9;
int dp[N][N],mi[2][N][N];
typedef pair<int,int> pii;
vector<pii>loc[N*N];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int main(){
	int n,m,K;
	rd(n);rd(m);rd(K);
	for(int i=0;i<=K;++i)
		loc[i].clear();
	loc[0].push_back(pii(0,0));
	for(int i=0,num;i<n;++i)
		for(int j=0;j<m;++j){
			rd(num);
			loc[num].push_back(pii(i,j));
		}
	bool cur=0,pre=1;
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			dp[i][j]=mi[pre][i][j]=mi[cur][i][j]=INF;
	for(int i=0;i<m;++i)
		mi[pre][0][i]=i;
	for(int i=1;i<=K;++i,cur^=1,pre^=1){
		for(int j=0;j<loc[i].size();++j){
			pii tmp=loc[i][j];
			int x=tmp.first,y=tmp.second;
			for(int k=0;k<n;++k)
				Min(dp[x][y],mi[pre][k][y]+abs(k-x));
			for(int k=0;k<m;++k)
				Min(mi[cur][x][k],dp[x][y]+abs(k-y));
		}
		for(int j=0;j<loc[i-1].size();++j){
			int x=loc[i-1][j].first;
			for(int k=0;k<m;++k)
				mi[pre][x][k]=INF;
		}
	}
	printf("%d\n",dp[loc[K][0].first][loc[K][0].second]);
	return 0;
}
/*
	
	Jun.08.16
	
	Tags:dp
	Submissions:2
	
	Time 124ms
	Memory 6400KB
	
*/
