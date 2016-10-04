#include<cstdio>
#include<cstring>
const int N=55,NODE=505;
int n,m,mp[256];
char str[N];
inline int max(int a,int b){
	return a>b?a:b;
}
struct BigInt{
	static const int BASE=1e9;
	int num[N],len;
	BigInt(){
		memset(num,0,sizeof(num));
		len=1;
	}
	void print(){
		printf("%d",num[len-1]);
		for(int i=len-2;i>=0;--i)
			printf("%09d",num[i]);
		puts("");
	}
	void operator =(const int &tmp){
		memset(num,0,sizeof(num));
		num[0]=tmp;
		len=1;
	}
	inline bool operator ==(const int &tmp)const{
		return len==1&&num[0]==tmp;
	}
	BigInt operator +(const BigInt &tmp)const{
		BigInt res;
		res.len=max(len,tmp.len);
		for(int i=0;i<res.len;++i){
			res.num[i]+=num[i]+tmp.num[i];
			if(res.num[i]>=BASE){
				res.num[i]-=BASE;
				++res.num[i+1];
			}
		}
		if(res.num[res.len])++res.len;
		return res;
	}
	inline void operator +=(const BigInt &tmp){
		*this=*this+tmp;
	}
	inline void operator ++(){
		++num[0];
	}
};
struct ACautomaton{
	int allc,trie[NODE][N],fail[NODE],que[NODE];
	BigInt dp[N][NODE];
	bool en[NODE];
	ACautomaton(){
		allc=0;
		memset(trie,0,sizeof(trie));
		memset(fail,0,sizeof(fail));
		memset(en,false,sizeof(en));
	}
	void init(){
		for(int i=0;i<=allc;++i){
			int tmp=max(n,m+1);
			for(int j=0;j<tmp;++j)
				dp[j][i]=trie[i][j]=0;
			fail[i]=en[i]=0;
		}
		allc=0;
	}
	void insert(){
		int len=strlen(str),cur=0;
		for(int i=0;i<len;++i){
			int c=mp[str[i]+128];
			if(!trie[cur][c])
				trie[cur][c]=++allc;
			cur=trie[cur][c];
		}
		en[cur]=true;
	}
	void build(){
		int L=0,R=0;
		for(int i=0;i<n;++i)
			if(trie[0][i])
				que[R++]=trie[0][i];
		while(L<R){
			int cur=que[L++];
			if(en[fail[cur]])en[cur]=true;
			for(int i=0;i<n;++i){
				int nxt=trie[cur][i];
				if(nxt){
					que[R++]=nxt;
					fail[nxt]=trie[fail[cur]][i];
				}
				else trie[cur][i]=trie[fail[cur]][i];
			}
		}
	}
	void DP(){
		BigInt ans;
		ans=0;
		for(int i=0;i<n;++i)
			if(!en[trie[0][i]])
				++dp[1][trie[0][i]];
		for(int i=1;i<m;++i)
			for(int j=0;j<=allc;++j){
				if(dp[i][j]==0)continue;
				BigInt tmp;
				tmp=dp[i][j];
				for(int k=0;k<n;++k){
					int nxt=trie[j][k];
					if(en[nxt])continue;
					dp[i+1][nxt]+=tmp;
					if(i+1==m)ans+=tmp;
				}
			}
		ans.print();
		init();
	}
}ac;
int main(){
	int p;
	while(~scanf("%d%d%d\n",&n,&m,&p)){
		gets(str);
		for(int i=0;i<n;++i)
			mp[str[i]+128]=i;
		while(p--){
			gets(str);
			ac.insert();
		}
		ac.build();
		ac.DP();
	}
	return 0;
}
/*
	
	Dec.05.15
	Submit:1
	
	Origin:PKU1625
	Tags:String,ACautomaton,dp
	
	Memory 6588KB
	Time 172ms
	Code Length 2421B
	
	
*/
