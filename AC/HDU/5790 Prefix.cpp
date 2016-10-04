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
#define lson (k<<1)
#define rson (k<<1|1)
#define Debug(x) cout<<endl<<#x<<"="<<x<<"!!!!!"<<endl<<endl
#define rep(i,s,t) for(int i=s,_t=t;i<t;++i)
#define per(i,s,t) for(int i=t-1,_s=s;i>=_s;--i)
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
typedef complex<db> Com;
const int mod=(int)1e9+7,inf=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const ll INF=1ll<<60;
const db pi=acos(-1.0),eps=1e-8;
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

const int N=(int)1e5+5;
int n,cnt,pre[N],st[N],en[N];
char str[N];

struct Trie{
	static const int S=26;
	int allc,mx[N],ch[S][N];
	void init(){
		allc=0;
		rep(i,0,S)ch[i][0]=0;
	}
	void NewNode(int &cur){
		cur=++allc;
		mx[cur]=0;
		rep(i,0,S)ch[i][cur]=0;
	}
	void ins(int id){
		int len=strlen(str);
		for(int i=0,cur=0,nxt;i<len;++i){
			nxt=str[i]-'a';
			if(!ch[nxt][cur])NewNode(ch[nxt][cur]);
			cur=ch[nxt][cur];
			pre[++cnt]=mx[cur];
			mx[cur]=id;
		}
	}
}trie;

int Tid[N];
struct Chairman_Tree{
	static const int LG=18,M=N*LG;
	int allc,Lson[M],Rson[M],sum[M];
	inline void init(){
		allc=0;
	}
	void cons(int oid,int &tid,int L,int R,int val){
		tid=++allc;
		Lson[tid]=Lson[oid];
		Rson[tid]=Rson[oid];
		sum[tid]=sum[oid]+1;
		// debug(L),debug(R),debug(oid),debug(sum[tid]);//
		if(L==R)return;
		int mid=L+R>>1;
		if(val<=mid)cons(Lson[oid],Lson[tid],L,mid,val);
		else cons(Rson[oid],Rson[tid],mid+1,R,val);
	}
	int query(int l,int r,int L,int R,int val){
		if(L>=val)return 0;
		if(R<val)return sum[r]-sum[l];
		int mid=L+R>>1;
		return query(Lson[l],Lson[r],L,mid,val)+query(Rson[l],Rson[r],mid+1,R,val);
	}
	inline int solve(int L,int R){
		// debug(st[L]-1),debug(en[R]);//
		return query(Tid[st[L]-1],Tid[en[R]],0,n,L);
	}
}cmt;
void solve(){
	trie.init();
	cnt=0;
	rep(i,1,n+1){
		st[i]=cnt+1;
		scanf("%s",str);
		trie.ins(i);
		en[i]=cnt;
		// debug(i),debug(st[i]),debug(en[i]);//
	}
	cmt.init();
	// rep(i,1,cnt+1)debug(i),debug(pre[i]);//
	rep(i,1,cnt+1)cmt.cons(Tid[i-1],Tid[i],0,n,pre[i]);
	int m;
	rd(m);
	for(int last_ans=0,L,R;m--;putchar('\n')){
		rd(L),rd(R);
		L=(last_ans+L)%n+1;
		R=(last_ans+R)%n+1;
		if(L>R)swap(L,R);
		// debug(L),debug(R);//
		print(last_ans=cmt.solve(L,R));
	}
}
int main(){
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	Aug.05.16

	Tags:trie,chairman tree
	Submissions:1

	Exe.Time 1638MS
	Exe.Memory 31276K
	Code Len. 3550B

*/
