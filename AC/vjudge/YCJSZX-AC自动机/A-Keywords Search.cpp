#include<cstdio>
#include<cstring>
const int N=1e6+5;
char str[N];
int que[N];
struct ACautomaton{
	int allc,trie[N][26],cnt[N],fail[N];
	ACautomaton(){
		allc=0;
		memset(trie,0,sizeof(trie));
		memset(cnt,0,sizeof(cnt));
		memset(fail,0,sizeof(fail));
	}
	void init(){
		for(int i=0;i<=allc;++i){
			for(int j=0;j<26;++j)
				trie[i][j]=0;
			cnt[i]=fail[i]=0;
		}
		allc=0;
	}
	void insert(){
		int len=strlen(str),cur=0;
		for(int i=0;i<len;++i){
			int nxt=str[i]-'a';
			if(!trie[cur][nxt])
				trie[cur][nxt]=++allc;
			cur=trie[cur][nxt];
		}
		++cnt[cur];
	}
	void build(){
		int L=0,R=0;
		for(int i=0;i<26;++i)
			if(trie[0][i])
				que[R++]=trie[0][i];
		while(L<R){
			int cur=que[L++];
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
	void solve(){
		int len=strlen(str),cur=0,ans=0;
		for(int i=0;i<len;++i){
			int tmp=cur=trie[cur][str[i]-'a'];
			while(~cnt[cur]){
				ans+=cnt[cur];
				cnt[cur]=-1;
				cur=fail[cur];
				if(!cur)break;
			}
			cur=tmp;
		}
		printf("%d\n",ans);
	}
}ac;
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		int n;
		scanf("%d",&n);
		while(n--){
			scanf("%s",str);
			ac.insert();
		}
		ac.build();
		scanf("%s",str);
		ac.solve();
		ac.init();
	}
	return 0;
}
/*
	
	Dec.04.15
	Submit:1
	
	Memory 112888KB
	Time 312ms
	Code Length 1351B
	
*/
