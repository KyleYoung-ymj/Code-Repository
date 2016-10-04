#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,K,m,num[N];
typedef __int64 ll;
ll sum[N];
typedef pair<int,int> P;
priority_queue<int,vector<int>,greater<int> >pque;
P itv[N];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void Max(ll &a,ll b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
void solve(){
	sum[0]=0;
	for(int i=1;i<=n;++i){
		rd(num[i]);
		sum[i]=sum[i-1]+num[i];
	}
	for(int i=0;i<m;++i){
		rd(itv[i].first);
		rd(itv[i].second);
	}
	ll ans=0;
	if(K==1){
		for(int i=0;i<m;++i)
			Max(ans,sum[itv[i].second]-sum[itv[i].first-1]);
		printf("%I64d\n",ans);
		return;
	}
	sort(itv,itv+m);
	while(!pque.empty())pque.pop();
	for(int i=0;i<K-1;i++)
		pque.push(itv[i].second);
	for(int i=K-1;i<m;++i){
		int L=itv[i].first,R=itv[i].second,
			elm=pque.top();
		pque.pop();
		Min(R,elm);
		if(L<=R)Max(ans,sum[R]-sum[L-1]);
		pque.push(max(elm,itv[i].second));
	}
	printf("%I64d\n",ans);
}
int main(){
	while(~scanf("%d%d%d",&n,&K,&m))solve();
	return 0;
}
/*
	
	May.26.16
	
	Tags:Greedy,Data Structure
	Submissions:1
	
	Exe.Time 1606MS
	Exe.Memory 4360K
	Code Len. 1344B
	
*/
