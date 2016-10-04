#include<cstdio>
const int N=505,mod=1e9+7;
int n,Cat[N],dp[N][N],que[N],L,R,ans,cnt_node,cnt_tree;
struct Node{
	int par,lson,rson,sz;
	Node(int par=0,int lson=0,int rson=0,int sz=0):
		par(par),lson(lson),rson(rson),sz(sz){}
}tree[N];
void init(){
	Cat[0]=1;
	for(int i=1;i<N;++i){
		Cat[i]=0;
		for(int j=0;j<i;++j)
			Cat[i]=(Cat[i]+1ll*Cat[j]*Cat[i-1-j])%mod;
	}
	dp[0][0]=1;
	for(int i=1;i<N;++i)
		dp[0][i]=0;
	for(int i=1;i<N;++i){
		for(int j=0;j<N;++j){
			dp[i][j]=0;
			for(int k=0;k<=j;++k)
				dp[i][j]=(dp[i][j]+1ll*dp[i-1][j-k]*Cat[k])%mod;
		}
	}
}
void dfs(int cur){
	--cnt_node;
	if(tree[cur].lson){
		if(tree[tree[cur].lson].sz){
			que[R++]=tree[cur].lson;
		}
		else dfs(tree[cur].lson);
	}
	else ++cnt_tree;
	if(tree[cur].rson){
		if(tree[tree[cur].rson].sz){
			que[R++]=tree[cur].rson;
		}
		else dfs(tree[cur].rson);
	}
	else ++cnt_tree;
}
int solve(){
	int allc=0,cur=0,sum=0,ope,x;
	tree[allc++]=Node(0,0,0,0);
	while(n--&&scanf("%d",&ope)){
		switch(ope){
			case 0:
				cur=tree[cur].par;
				break;
			case 1:
				if(!tree[cur].lson)
					tree[tree[cur].lson=allc++]=Node(cur,0,0,0);
				cur=tree[cur].lson;
				break;
			case 2:
				if(!tree[cur].rson)
					tree[tree[cur].rson=allc++]=Node(cur,0,0,0);
				cur=tree[cur].rson;
				break;
			case 3:
				scanf("%d",&x);
				tree[tree[cur].lson=allc++]=Node(cur,0,0,x);
				sum+=x;
				break;
			case 4:
				scanf("%d",&x);
				tree[tree[cur].rson=allc++]=Node(cur,0,0,x);
				sum+=x;
				break;
		}	
	}
	ans=1;
	L=R=0;
	if(tree[0].lson)que[R++]=tree[0].lson;
	if(tree[0].rson)que[R++]=tree[0].rson;
	while(L<R){
		int elm=que[L++];
		cnt_node=tree[elm].sz;
		cnt_tree=0;
		dfs(elm);
		ans=1ll*ans*dp[cnt_tree][cnt_node]%mod;
	}
	return ans;
}
int main(){
	int kase=0;
	init();
	while(~scanf("%d",&n)){
		printf("Case #%d: %d\n",++kase,solve());
	}
	return 0;
}
/*
	
	Jun.28.16
	
	Tags:Catalan Number
	Submissions:2
	
	Memory(KB) 2440
	Time(ms) 748
	Length(Bytes) 1841
	
*/
