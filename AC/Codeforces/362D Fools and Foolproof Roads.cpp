#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,p,q,x,y,tot_edge,head[N],id[N],tot_cmp,id_cmp[N],cnt[N];
bool vis[N];
typedef __int64 ll;
const ll MX=1e9;
ll sum_cmp[N];
struct EDGE{
	int u,v,cost;
}es[N];
struct Edge{
	int to,nxt,cost;
}edge[N<<1];
struct UNIT{
	ll amt;
	int id;
	inline bool operator <(const UNIT &tmp)const{
		return amt>tmp.amt;
	}
};
priority_queue<UNIT>pque;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void add_edge(int from,int to,int len){
	edge[tot_edge]=(Edge){to,head[from],len};
	head[from]=tot_edge++;
}
void dfs(int cur){
	vis[cur]=true;
	id[cur]=tot_cmp;
	if(++cnt[tot_cmp]==2){
		x=cur;
		y=id_cmp[tot_cmp];
	}
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(vis[to])continue;
		dfs(to);
	}
}
void solve(){
	int need=tot_cmp-q;
	if(q>tot_cmp||need>p||!need&&p&&x==-1){
		puts("NO");
		return;
	}
	puts("YES");
	while(!pque.empty())pque.pop();
	for(int i=0;i<tot_cmp;++i)
		pque.push((UNIT){sum_cmp[i],id_cmp[i]});
	while(need--){
		UNIT a=pque.top();
		pque.pop();
		UNIT b=pque.top();
		pque.pop();
		printf("%d %d\n",a.id,b.id);
		if(x==-1){
			x=a.id;
			y=b.id;
		}
		ll cost=min(a.amt+b.amt+1,MX);
		pque.push((UNIT){a.amt+b.amt+cost,a.id});
		--p;
	}
	while(p--)printf("%d %d\n",x,y);
}
int main(){
	int m,u,v,len;
	rd(n);rd(m);rd(p);rd(q);
	tot_edge=0;
	memset(head,-1,n+1<<2);
	memset(id,-1,n+1<<2);
	for(int i=0;i<m;++i){
		rd(u);rd(v);rd(len);
		add_edge(u,v,len);
		add_edge(v,u,len);
		es[i]=(EDGE){u,v,len};
	}
	tot_cmp=0;
	memset(vis,false,n+1);
	x=-1;
	for(int i=1;i<=n;++i){
		if(vis[i])continue;
		sum_cmp[tot_cmp]=cnt[tot_cmp]=0;
		id_cmp[tot_cmp]=i;
		dfs(i);
		++tot_cmp;
	}
	for(int i=0;i<m;++i){
		sum_cmp[id[es[i].u]]+=es[i].cost;
	}
	solve();
	return 0;
}
/*
	
	Jun.13.16

	Tags:greedy,priority_queue
	Submissions:6

	Time 93ms
	Memory 11296KB

*/