#include<cstdio>
#include<cctype>
#include<cstring>
const int N=1005,SUB_LEN=55,LEN=2e6+5,NODE=5e4+5;
int n,que[NODE],cnt[N]={0};
char virus[N][SUB_LEN],str[LEN];
struct ACautomaton{
	int allc,trie[NODE][26],fail[NODE],en[NODE];
	ACautomaton(){
		allc=0;
		memset(trie,0,sizeof(trie));
		memset(fail,0,sizeof(fail));
		memset(en,-1,sizeof(en));
	}
	void insert(int id){
		int len=strlen(virus[id]),cur=0;
		for(int i=0;i<len;++i){
			int nxt=virus[id][i]-'A';
			if(!trie[cur][nxt])
				trie[cur][nxt]=++allc;
			cur=trie[cur][nxt];
		}
		en[cur]=id;
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
		int len=strlen(str),cur=0;
		for(int i=0;i<len;++i){
			if(!isupper(str[i])){
				cur=0;
				continue;
			}
			int tmp=cur=trie[cur][str[i]-'A'];
			while(cur){
				if(~en[cur])++cnt[en[cur]];
				cur=fail[cur];
			}
			cur=tmp;
		}
		for(int i=0;i<n;++i)
			if(cnt[i]){
				printf("%s: %d\n",virus[i],cnt[i]);
				cnt[i]=0;
			}
		for(int i=0;i<=allc;++i){
			for(int j=0;j<26;++j)
				trie[i][j]=0;
			fail[i]=0;
			en[i]=-1;
		}
		allc=0;
	}
}ac;
int main(){
	while(~scanf("%d",&n)){
		for(int i=0;i<n;++i){
			scanf("%s",virus[i]);
			ac.insert(i);
		}
		ac.build();
		scanf("%s",str);
		ac.solve();
	}
	return 0;
}
/*
	
	Origin:HDU3065
	Tags:String,ACautomaton
	
	Dec.04.15
	Submit:4
	
	Memory 8968KB
	Time 265ms
	Code Length 1501B
	
*/
