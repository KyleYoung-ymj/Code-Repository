struct SplayTree{
	int sz,root,ch[N][2],par[N],val[N];
	inline void clear(){
		sz=root=0;
	}
	void NewNode(int &now,int fa,int v){
		now=++sz;
		par[now]=fa;
		ch[now][0]=ch[now][1]=0;
		val[now]=v;
	}
	void rotate(int x,bool f){
		int y=par[x];
		par[ch[x][f]]=y;
		ch[y][!f]=ch[x][f];
		par[x]=par[y];
		if(par[y])ch[par[y]][ch[par[y]][1]==y]=x;
		par[y]=x;
		ch[x][f]=y;
	}
	void Splay(int x,int goal=0){
		while(par[x]!=goal){
			int y=par[x];
			if(par[y]==goal)rotate(x,ch[y][0]==x);
			else{
				bool flag=ch[par[y]][0]==y;
				if(ch[y][flag]==x){
					rotate(x,!flag);
					rotate(x,flag);
				}
				else{
					rotate(y,flag);
					rotate(x,flag);
				}
			}
		}
		if(!goal)root=x;
	}
	bool insert(int x){
		int cur=root;
		for(;ch[cur][x>val[cur]];cur=ch[cur][x>val[cur]])
			if(val[cur]==x){
				Splay(cur);
				return false;
			}
		NewNode(ch[cur][x>val[cur]],cur,x);
		Splay(ch[cur][x>val[cur]]);
		return true;
	}
	int Get_Pre(){
		int x=ch[root][0];
		if(!x)return INF;
		while(ch[x][1])x=ch[x][1];
		return val[x];
	}
	int Get_Next(){
		int x=ch[root][1];
		if(!x)return INF;
		while(ch[x][0])x=ch[x][0];
		return val[x];
	}
};
