stk[++top]=1;
for(int i=0;i<m;++i){
	int anc;
	while(top){
		anc=lca(stk[top],node[i]);
		if(top>1&&dep[anc]<dep[stk[top-1]]){
			add_iedge(stk[top-1],stk[top]);
			--top;
		}
		else if(dep[anc]<dep[stk[top]]){
			add_iedge(anc,stk[top]);
			--top;
			break;
		}
		else break;
	}
	if(stk[top]!=anc)stk[++top]=anc;
	stk[++top]=node[i];
}
while(top>1){
	add_iedge(stk[top-1],stk[top]);
	--top;
}
