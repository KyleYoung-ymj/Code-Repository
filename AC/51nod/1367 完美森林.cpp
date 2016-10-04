#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=5e5+5;
int n,m,ans=1,dep[N],tmp[N];
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
inline bool cmp(int a,int b){
	return a>b;
}
void dfs(int now,int pre){
	int cnt=0,ptr=0;
	for(int i=0;i<T[now].size();++i){
		if(T[now][i].to==pre)continue;
		dfs(T[now][i].to,now);
	}
	for(int i=0;i<T[now].size();++i){
		if(T[now][i].to==pre)continue;
		dep[T[now][i].to]+=T[now][i].cost;
		if(dep[T[now][i].to]>m)++ans;
		else tmp[cnt++]=dep[T[now][i].to];
	}
	if(!cnt){
		dep[now]=0;
		return;
	}
	sort(tmp,tmp+cnt,cmp);
	for(;ptr+1<cnt;++ptr)
		if(tmp[ptr]+tmp[ptr+1]>m)++ans;
		else break;
	dep[now]=tmp[ptr];
}
int main(){
	rd(n);rd(m);
	for(int i=0;i<n;++i)
		T[i].clear();
	int a,b,c;
	for(int i=1;i<n;++i){
		rd(a);rd(b);rd(c);
		T[a].push_back((edge){b,c});
		T[b].push_back((edge){a,c});
	}
	dfs(0,0);
	printf("%d\n",ans);
	return 0;
}
/*
	
	Dec.25.15
	
	Tags:Tags:Greedy,dp,Graph,Tree
	Submissions:1
	
	Time 984ms
	Memory 30700KB
	
*/
