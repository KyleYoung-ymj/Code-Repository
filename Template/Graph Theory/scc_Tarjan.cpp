int n,dfs_clock,scc_cnt,top,stk[N],pre[N],scc_id[N];
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
			int elm=stk[--top];
			scc_id[elm]=scc_cnt;
			if(elm==cur)break;
		}
	}
	return lowlink;
}
void scc(){
	dfs_clock=scc_cnt=top=0;
	memset(pre,0,n<<2);
	memset(scc_id,0,n<<2);
	for(int i=0;i<n;++i)
		if(!pre[i])Tarjan(i);
}
/*
	
	Apr.06.16
	
	Problem:HDU1269
	
*/
