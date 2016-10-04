#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e5+5,MOD=1e9+7;
int n,m,p,par[N],dp[N],pre[N];
bool exist[N];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),!isdigit(c));
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),isdigit(c));
}
struct Limit{
	int x,y,c;
	inline bool operator <(const Limit &tmp)const{
		return c<tmp.c;
	}
	inline void Rd(){
		rd(x);rd(y);rd(c);
	}
}lim[N];
int get_root(int x){
	return par[x]==x?x:par[x]=get_root(par[x]);
}
int main(){
	while(~scanf("%d",&n)){
		rd(m);rd(p);
		for(int i=1;i<=n;++i){
			exist[i]=true;
			pre[i]=dp[par[i]=i]=0;
		}
		for(int i=0;i<p;++i)lim[i].Rd();
		sort(lim,lim+p);
		for(int i=0;i<p;++i){
			int x=lim[i].x,y=lim[i].y,c=lim[i].c;
			if(c==m)break;//if c==m then the limit is meaningless
			x=get_root(x);
			y=get_root(y);
			if(x==y)continue;
			dp[x]=(1LL*(dp[x]+c-pre[x])*(dp[y]+c-pre[y])+1)%MOD;
			pre[x]=c+1;
			par[y]=x;
			exist[y]=false;
		}
		int ans=1;
		for(int i=1;i<=n;++i){
			if(!exist[i])continue;
			ans=1LL*ans*(dp[i]+m-pre[i])%MOD;
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	Dec.24.15
	
	Tags:Unite_Find_Union,dp,count
	Submissions:4
	WA:Wrong usage of Unite_Find_Union
	
	Code Length 1125B
	Time 154ms
	Memory 2972KB
		
*/
