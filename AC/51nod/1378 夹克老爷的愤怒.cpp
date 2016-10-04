#include<cstdio>
#include<cctype>
#include<cstring>
#include<vector>
using namespace std;
const int N=1e5+5;
int n,m,que[N],dep[N],par[N];
bool used[N]={false};
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),!isdigit(c));
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),isdigit(c));
}
vector<int>T[N],node[N];
void pre_pro(){
	int L=0,R=0;
	node[0].push_back(0);
	que[R++]=par[0]=dep[0]=0;
	used[0]=true;
	while(L<R){
		int now=que[L++];
		for(int i=0;i<T[now].size();++i){
			int to=T[now][i];
			if(used[to])continue;
			used[to]=true;
			par[to]=now;
			dep[que[R++]=to]=dep[now]+1;
			node[dep[to]].push_back(to);
		}
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
int solve(){
	memset(used,false,sizeof(used));
	int ans=0; 
	for(int i=n-1;~i;--i)
		for(int j=0;j<node[i].size();++j){
			int now=node[i][j];
			if(used[now])continue;
			for(int k=0;k<m&&now;++k)now=par[now];
			paint(-1,now,m);
			++ans;
		}
	return ans;
}
int main(){
	int a,b;
	rd(n);
	rd(m);
	for(int i=0;i<n;++i){
		T[i].clear();
		node[i].clear();
	}
	for(int i=1;i<n;++i){
		rd(a);
		rd(b);
		T[a].push_back(b);
		T[b].push_back(a);
	}
	pre_pro();
	printf("%d\n",solve());
	return 0;
}
/*
	
	Dec.24.15
	
	Tags:Greedy,Tree
	Submissions:11
	
	Time 171ms
	Memory 11044KB
	
*/
