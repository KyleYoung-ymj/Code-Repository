#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e4+5,M=1e5+5;
int n,tot_edge,dfs_clock,scc_cnt,top,stk[N],pre[N],scc_id[N],head[N];
struct Edge{
	int to,nxt;
}edge[M];
inline void add_edge(int from,int to){
	edge[tot_edge]=(Edge){to,head[from]};
	head[from]=tot_edge++;
}
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>=48);
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int Tarjan(int cur){
	int lowlink=pre[cur]=++dfs_clock;
	stk[top++]=cur;
	for(int i=head[cur];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(!pre[to])Min(lowlink,Tarjan(to));
		else if(!scc_id[to])Min(lowlink,pre[to]);
	}
	if(lowlink==pre[cur]){
		++scc_cnt;
		while(true){
			int elm=stk[top-1];
			--top;
			scc_id[elm]=scc_cnt;
			if(elm==cur)break;
		}
	}
	return lowlink;
}
void scc(){
	dfs_clock=scc_cnt=top=0;
	memset(scc_id,0,n+1<<2);
	for(int i=1;i<=n;++i)
		if(!scc_id[i])Tarjan(i);
}
int main(){
	int m;
	while(true){
		rd(n);rd(m);
		if(!n&&!m)return 0;
		tot_edge=0;
		memset(head,-1,n+1<<2);
		int a,b;
		while(m--){
			rd(a);rd(b);
			add_edge(a,b);
		}
		scc();
		puts(scc_cnt==1?"Yes":"No");
	}
}
/*
	
	Apr.06.16
	
	Tags:scc
	Submissions:2
	
	Exe.Time 78MS
	Exe.Memory 3124K
	Code Len. 1276B
	
*/
