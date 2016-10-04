#include <cstdio>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb push_back
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
typedef complex<double> Com;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
template<class T>void rd(T &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_print(T x){
	if(!x)return;
	rec_print(x/10);
	putchar(x%10^48);
}
template<class T>void print(T x){
	if(!x)putchar('0');
	else rec_print(x);
}
template<class T>inline void Max(T &a,T b){
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b){
	if(b<a)a=b;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}
const int N=(int)1e6+5;
char str[N];
struct ACautomaton{
	static const int NODE=(int)1e6+5,S=26;
	int allc,trie[NODE][S],cnt[NODE],fail[NODE],que[NODE];
	ACautomaton(){
		allc=0;
		memset(trie,0,sizeof trie);
		memset(cnt,0,sizeof cnt);
		memset(fail,0,sizeof fail);
	}
	void init(){
		for(int i=0;i<=allc;++i){
			for(int j=0;j<S;++j)
				trie[i][j]=0;
			cnt[i]=fail[i]=0;
		}
		allc=0;
	}
	void insert(){
		int cur=0;
		for(int i=0,len=strlen(str);i<len;++i){
			int nxt=str[i]-'a';
			if(!trie[cur][nxt])
				trie[cur][nxt]=++allc;
			cur=trie[cur][nxt];
		}
		++cnt[cur];
	}
	void construct(){
		int L=0,R=0;
		for(int i=0;i<S;++i)
			if(trie[0][i])
				que[R++]=trie[0][i];
		while(L<R){
			int cur=que[L++];
			for(int i=0;i<S;++i){
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
		int ans=0;
		for(int i=0,len=strlen(str),cur=0;i<len;++i){
			cur=trie[cur][str[i]-'a'];
			for(int tmp=cur;tmp&&~cnt[tmp];tmp=fail[tmp]){
				ans+=cnt[tmp];
				cnt[tmp]=-1;
			}
		}
		printf("%d\n",ans);
	}
}ac;
int main(){
	int cas,n;
	for(rd(cas);cas--;){
		rd(n);
		while(n--&&scanf("%s",str))
			ac.insert();
		ac.construct();
		scanf("%s",str);
		ac.solve();
		ac.init();
	}
	return 0;
}
/*
	
	Jul.23.16

	Problem:HDU2222
	
*/
