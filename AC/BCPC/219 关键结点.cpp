#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=2005;
int n,m,dep[N],par[N],ans[N];
bool used[N];
vector<int>T[N],node[N];
inline void Min(int &a,int b){
	if(b<a)a=b;
}
void dfs(int pre,int now,int dis){
	par[now]=pre;
	node[dep[now]=dis].push_back(now);
	for(int i=0;i<T[now].size();++i){
		if(T[now][i]==pre)continue;
		dfs(now,T[now][i],dis+1);
	}
}
void paint(int pre,int now,int left){
	if(left<0)return;
	used[now]=true;
	for(int i=0;i<T[now].size();++i){
		if(T[now][i]==pre)continue;
		paint(now,T[now][i],left-1);
	}
}
int solve(int m){
	for(int i=1;i<=n;++i)
		used[i]=false;
	int ans=0;
	for(int i=n;i;--i)
		for(int j=0;j<node[i].size();++j){
			int now=node[i][j];
			if(used[now])continue;
			for(int k=0;k<m&&now>1;++k)now=par[now];
			paint(now,now,m);
			++ans;
		}
	return ans;
}
int bin_search(int m){
	int L=0,R=n-1,res=n;
	while(L<=R){
		int mid=L+R>>1;
		if(ans[mid]<=m){
			Min(res,mid);
			R=mid-1;
		}
		else L=mid+1;
	}
	return res;
}
int main(){
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;++i){
			T[i].clear();
			node[i].clear();
		}
		int x;
		for(int i=2;i<=n;++i){
			scanf("%d",&x);
			T[i].push_back(x);
			T[x].push_back(i);
		}
		dfs(0,1,1);
		for(int i=0;i<n;++i)
			ans[i]=solve(i);
		for(int i=1;i<=n;++i){
			if(i>1)putchar(' ');
			printf("%d",bin_search(i));
		}
		putchar('\n');
	}
	return 0;
}
/*
	
	Dec.24.15
	
	Tags:Tree,Greedy
	Submissions:7
	
	Code Length 1450B
	Time 896ms
	Memory 1472KB
	
*/
