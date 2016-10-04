#include<cstdio>
#include<cstring>
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
const int N=1e4+5,M=505,NODE=6e4+5;
char str[N];
int que[NODE];
set<int>used;
struct ACautomaton{
	int allc,tot,trie[NODE][128],fail[NODE],en[NODE],ans[3];
	ACautomaton(){
		allc=0;
		memset(trie,0,sizeof(trie));
		memset(fail,0,sizeof(fail));
		memset(en,0,sizeof(en));
	}
	void insert(int id){
		int len=strlen(str),cur=0;
		for(int i=0;i<len;++i){
			if(!trie[cur][str[i]])
				trie[cur][str[i]]=++allc;
			cur=trie[cur][str[i]];
		}
		en[cur]=id;
	}
	void build(){
		int L=0,R=0;
		for(int i=0;i<128;++i)
			if(trie[0][i])
				que[R++]=trie[0][i];
		while(L<R){
			int cur=que[L++];
			for(int i=0;i<128;++i){
				int nxt=trie[cur][i];
				if(nxt){
					que[R++]=nxt;
					fail[nxt]=trie[fail[cur]][i];
				}
				else trie[cur][i]=trie[fail[cur]][i];
			}
		}
	}
	void solve(int id){
		int len=strlen(str),cur=0,cnt=0;
		used.clear();
		for(int i=0;i<len;++i){
			int tmp=cur=trie[cur][str[i]];
			while(used.find(cur)==used.end()){
				if(en[cur])ans[cnt++]=en[cur];
				used.insert(cur);
				cur=fail[cur];
				if(!cur)break;
			}
			if(cnt==3)break;
			cur=tmp;
		}
		if(cnt){
			++tot;
			printf("web %d:",id);
			sort(ans,ans+cnt);
			for(int i=0;i<cnt;++i)
				printf(" %d",ans[i]);
			puts("");
		}
	}
	void output_init(){
		printf("total: %d\n",tot);
		for(int i=0;i<=allc;++i){
			for(int j=0;j<128;++j)
				trie[i][j]=0;
			fail[i]=en[i]=0;
		}
		tot=allc=0;
	}
}ac;
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%s",str);
		ac.insert(i);
	}
	ac.build();
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%s",str);
		ac.solve(i);
	}
	ac.output_init();
	return 0;
}
/*
	
	Origin:HDU2896
	Tags:ACautomaton,string
	
	Dec.04.15
	Submit:2
	
	Memory 32524KB
	Time 889ms
	Code Length 1711B
	
*/
