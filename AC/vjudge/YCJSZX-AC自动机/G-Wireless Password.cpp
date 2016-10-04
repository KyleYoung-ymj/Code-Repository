#include<cstdio>
#include<cstring>
const int N=30,LEN=15,NODE=105,S_MAX=1<<10,P=20090717;
int n,m,k;
char str[LEN];
struct ACautomaton{
	int allc,trie[NODE][26],fail[NODE],en[NODE],que[NODE],dp[N][NODE][S_MAX],bit_num[S_MAX];
	ACautomaton(){
		allc=0;
		memset(trie,0,sizeof(trie));
		memset(fail,0,sizeof(fail));
		memset(en,0,sizeof(en));
	}
	void pre_pro(){
		bit_num[0]=0;
		for(int i=0;i<S_MAX;++i)
			bit_num[i]=bit_num[i>>1]+(i&1);
	}
	void init(){
		for(int i=0;i<=allc;++i){
			for(int j=0;j<26;++j)
				trie[i][j]=0;
			fail[i]=en[i]=0;
		}
		allc=0;
	}
	void insert(int id){
		int len=strlen(str),cur=0;
		for(int i=0;i<len;++i){
			int nxt=str[i]-'a';
			if(!trie[cur][nxt])
				trie[cur][nxt]=++allc;
			cur=trie[cur][nxt];
		}
		en[cur]=1<<id;
	}
	void construct(){
		int L=0,R=0;
		for(int i=0;i<26;++i)
			if(trie[0][i])
				que[R++]=trie[0][i];
		while(L<R){
			int cur=que[L++];
			en[cur]|=en[fail[cur]];
			for(int i=0;i<26;++i){
				int nxt=trie[cur][i];
				if(nxt){
					que[R++]=nxt;
					fail[nxt]=trie[fail[cur]][i];
				}
				else trie[cur][i]=trie[fail[cur]][i];
			}
		}
	}
	inline void mod_plus(int &a,int b){
		a=(a+b)%P;
	}
	void solve(){
		int S_max=1<<m,ans=0;
		for(int i=0;i<=n;++i)
			for(int j=0;j<=allc;++j)
				for(int S=0;S<S_max;++S)
					dp[i][j][S]=0;
		dp[0][0][0]=1;
		for(int i=0;i<n;++i)
			for(int j=0;j<=allc;++j)
				for(int S=0;S<S_max;++S){
					if(!dp[i][j][S])continue;
					for(int t=0;t<26;++t){
						int nxt=trie[j][t],nxt_S=S|en[nxt];
						mod_plus(dp[i+1][nxt][nxt_S],dp[i][j][S]);
						if(i+1==n&&bit_num[nxt_S]>=k)mod_plus(ans,dp[i][j][S]);
					}
				}
		printf("%d\n",ans);
	}
}ac;
int main(){
	ac.pre_pro();
	while(~scanf("%d%d%d",&n,&m,&k)&&n){
		for(int i=0;i<m;++i){
			scanf("%s",str);
			ac.insert(i);
		}
		ac.construct();
		ac.solve();
		ac.init();
	}
	return 0;
}
/*
	
	Dec.11,15
	
	Origin:HDU 2825
	Tags:String,ACautomaton,dp,binary
	
	Memory 7896KB
	Time 577ms
	Code Length 1839B
	
*/
