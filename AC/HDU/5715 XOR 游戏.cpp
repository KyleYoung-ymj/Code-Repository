#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e4+5,M=15,LEN=30;
int n,m,len,arr[N],sum[N];
bool bin[LEN],dp[N][M];
struct Trie{
	int allc,son[N][2],mul[N];
	Trie(){
		allc=0;
		memset(son,0,sizeof(son));
		memset(mul,0,sizeof(mul));
	}
	void init(){
		for(int i=0;i<=allc;++i)
			son[i][0]=son[i][1]=mul[i]=0;
		allc=0;
	}
	void convert(int num){
		for(int i=LEN-1;~i;--i,num>>=1)
			bin[i]=num&1;
	}
	int query_mx(int num){
		convert(num);
		int res=0;
		for(int i=0,cur=0;i<LEN;++i){
			res<<=1;
			if(mul[son[cur][bin[i]^1]]){
				res|=1;
				cur=son[cur][bin[i]^1];
			}
			else cur=son[cur][bin[i]];
		}
		return res;
	}
	void insert(int num){
		convert(num);
		for(int i=0,cur=0;i<LEN;++mul[cur=son[cur][bin[i++]]]){
			if(!son[cur][bin[i]])
				son[cur][bin[i]]=++allc;
		}
	}
	void erase(int num){
		convert(num);
		for(int i=0,cur=0;i<LEN;--mul[cur=son[cur][bin[i++]]]);
	}
}T;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
bool judge(int lim){
	memset(dp,false,sizeof(dp));
	for(int i=1;i<=n;++i)
		dp[i][1]=i<=len&&sum[i]>=lim;
	for(int j=2;j<=m;++j){
		T.init();
		for(int i=j;i<=n;++i){
			if(i-len>=j&&dp[i-len-1][j-1])T.erase(sum[i-len-1]);
			if(dp[i-1][j-1])T.insert(sum[i-1]);
			dp[i][j]=T.query_mx(sum[i])>=lim;
		}
	}
	return dp[n][m];
}
void solve(){
	rd(n);rd(m);rd(len);
	sum[0]=0;
	for(int i=1;i<=n;++i){
		rd(arr[i]);
		sum[i]=sum[i-1]^arr[i];
	}
	int L=0,R=1e9,ans;
	while(L<=R){
		int mid=L+R>>1;
		if(judge(mid)){
			ans=mid;
			L=mid+1;
		}
		else R=mid-1;
	}
	printf("%d\n",ans);
}
int main(){
	int cas,kase=0;
	rd(cas);
	while(cas--){
		printf("Case #%d:\n",++kase);
		solve();
	}
	return 0;
}
/*
	
	May.29.16
	
	Tags:dp,Trie
	Submissions:1
	
	Exe.Time 873MS
	Exe.Memory 1748K
	Code Len. 1842B
	
*/
