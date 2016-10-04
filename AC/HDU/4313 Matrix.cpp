#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int N=1e5+5;
const ull INF=1LL<<60;
int n;
bool mark[N];
ull dp[N][2];
struct edge{
	int to,cost;
};
vector<edge>T[N];
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>=48);
}
inline void Min(ull &a,ull b){
	if(b<a)a=b;
}
void dfs(int pre,int cur){
	if(T[cur].size()==1&&cur){
		if(mark[cur]){
			dp[cur][0]=INF;
			dp[cur][1]=0;
		}
		else dp[cur][0]=dp[cur][1]=0;
		return;
	}
	if(mark[cur]){
		dp[cur][0]=INF;
		dp[cur][1]=0;
		for(int i=0;i<T[cur].size();++i){
			if(T[cur][i].to==pre)continue;
			dfs(cur,T[cur][i].to);
			dp[cur][1]+=min(dp[T[cur][i].to][0],dp[T[cur][i].to][1]+T[cur][i].cost);
		}
	}
	else{
		dp[cur][0]=0;
		dp[cur][1]=INF;
		for(int i=0;i<T[cur].size();++i){
			if(T[cur][i].to==pre)continue;
			dfs(cur,T[cur][i].to);
			dp[cur][0]+=min(dp[T[cur][i].to][0],dp[T[cur][i].to][1]+T[cur][i].cost);
		}
		for(int i=0;i<T[cur].size();++i){
			int to=T[cur][i].to,cost=T[cur][i].cost;
			if(to==pre)continue;
			Min(dp[cur][1],dp[cur][0]-min(dp[to][0],dp[to][1]+cost)+dp[to][1]);
		}
	}
}
int main(){
	int cas,m,a,b,c;
	rd(cas);
	while(cas--){
		rd(n);rd(m);
		for(int i=0;i<n;++i){
			T[i].clear();
			mark[i]=false;
		}
		for(int i=1;i<n;++i){
			rd(a);rd(b);rd(c);
			T[a].push_back((edge){b,c});
			T[b].push_back((edge){a,c});
		}
		while(m--){
			rd(a);
			mark[a]=true;
		}
		dfs(-1,0);
		printf("%I64u\n",min(dp[0][0],dp[0][1]));
	}
	return 0;
}
/*
	
	Dec.27.15
	
	Tags:dp on Tree
	Submissions:1
	
	Exe.Time 249MS
	Exe.Memory 8540K
	Code Len. 1641B
	
*/
