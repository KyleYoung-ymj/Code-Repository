#include<cstdio>
#include<cstring>
const int N=1005,INF=0x7fffffff;
char str[N];
int mp(char c){
	switch (c){
		case 'A':return 0;
		case 'T':return 1;
		case 'G':return 2;
		case 'C':return 3;
	}
}
struct ACautomaton{
	int allc,trie[N][4],fail[N],que[N],dp[N][N];
	bool en[N];
	ACautomaton(){
		allc=0;
		memset(trie,0,sizeof(trie));
		memset(fail,0,sizeof(fail));
		memset(en,false,sizeof(en));
	}
	void init(){
		for(int i=0;i<=allc;++i){
			for(int j=0;j<4;++j)
				trie[i][j]=0;
			fail[i]=en[i]=0;
		}
		allc=0;
	}
	void insert(){
		int len=strlen(str),cur=0;
		for(int i=0;i<len;++i){
			int c=mp(str[i]);
			if(!trie[cur][c])
				trie[cur][c]=++allc;
			cur=trie[cur][c];
		}
		en[cur]=true;
	}
	void build(){
		int L=0,R=0;
		for(int i=0;i<4;++i)
			if(trie[0][i])
				que[R++]=trie[0][i];
		while(L<R){
			int cur=que[L++];
			if(en[fail[cur]])en[cur]=true;
			for(int i=0;i<4;++i){
				int nxt=trie[cur][i];
				if(nxt){
					que[R++]=nxt;
					fail[nxt]=trie[fail[cur]][i];
				}
				else trie[cur][i]=trie[fail[cur]][i];
			}
		}
	}
	int DP(){
		int len=strlen(str),ans=INF;
		for(int i=0;i<=len;++i)
			for(int j=0;j<=allc;++j)
				dp[i][j]=INF;
		dp[0][0]=0;
		for(int i=0;i<len;++i){
			int c=mp(str[i]);
			for(int j=0;j<=allc;++j){
				if(dp[i][j]==INF)continue;
				for(int k=0;k<4;++k){
					int nxt=trie[j][k];
					if(en[nxt])continue;
					int cost=dp[i][j]+(k!=c);
					if(cost<dp[i+1][nxt]){
						dp[i+1][nxt]=cost;
						if(i+1==len&&cost<ans)
							ans=cost;
					}
				}
			}
		}
		if(ans==INF)ans=-1;
		init();
		return ans;
	}
}ac;
int main(){
	int n,kase=0;
	while(~scanf("%d",&n)&&n){
		while(n--){
			scanf("%s",str);
			ac.insert();
		}
		ac.build();
		scanf("%s",str);
		printf("Case %d: %d\n",++kase,ac.DP());
	}
	return 0;
}
/*
	
	Tags:String,ACautomaton,dp
	
	Dec.05.15
	Submit:1
	
	Memory 5368KB
	Time 62ms
	Code Length 1763B
	
*/
