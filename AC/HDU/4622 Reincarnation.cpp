#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define y1 jfskav
#define pb push_back
#define lson (k<<1)
#define rson (k<<1|1)
#define lowbit(x) ((x)&-(x))
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define debug(x) cout<<#x<<" = "<<(x)<<endl
#define rep(i,s,t) for(register int i=(s),_t=(t);i<_t;++i)
#define per(i,s,t) for(register int i=(t)-1,_s=(s);i>=_s;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int mod=(int)1e9+7,inf=0x7fffffff,dxy[]={-1,0,1,0,-1};
const ll INF=1ll<<60;
const db pi=acos(-1),eps=1e-6;
template<class T>void rd(T &x){
	x=0;
	char c;
	while(c=getchar(),c<48);
	do x=(x<<3)+(x<<1)+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_pt(T x){
	if(!x)return;
	rec_pt(x/10);
	putchar(x%10^48);
}
template<class T>void pt(T x){
	if(!x)putchar('0');
	else rec_pt(x);
}
template<class T>inline void ptn(T x){
	pt(x),putchar('\n');
}
template<class T>inline void Max(T &a,T b){
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b){
	if(b<a)a=b;
}
template<class T>T gcd(T a,T b){
	return b?gcd(b,a%b):a;
}
inline void mod_add(int &a,int b,int m=mod){
	if((a+=b)>=m)a-=m;
}
inline void mod_minus(int &a,int b,int m=mod){
	if((a-=b)<0)a+=m;
}
int mod_pow(int a,int b,int m=mod){
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}
inline int calc_inv(int x,int m=mod){
	return mod_pow(x,m-2);
}


const int N=(int)2e3+5;

char str[N];

struct Suffix_Automaton{
	static const int NODE=N<<1,C=26;
	int allc,last,par[NODE],len[NODE],trans[NODE][C],tot,ans[N][N];
	int NewNode(){
		int ret=++allc;
		memset(trans[ret],0,C<<2);
		return ret;
	}
	void init(){
		allc=tot=0;
		last=NewNode();
		par[last]=len[last]=0;
	}
	void extend(int c){
		int np=NewNode(),p=last;
		len[np]=len[last]+1;
		for(;p&&!trans[p][c];p=par[p])trans[p][c]=np;
		if(!p)par[np]=1;
		else{
			int q=trans[p][c];
			if(len[q]==len[p]+1)par[np]=q;
			else{
				int nq=++allc;
				par[nq]=par[q];
				len[nq]=len[p]+1;
				memcpy(trans[nq],trans[q],C<<2);
				tot+=len[nq]-len[par[q]]+len[par[q]];
				par[np]=par[q]=nq;
				tot-=len[nq];
				for(trans[p][c]=nq,p=par[p];trans[p][c]==q;p=par[p])trans[p][c]=nq;
			}
		}
		tot+=len[np]-len[par[np]];
		last=np;
	}
	void cons(){
		int n=strlen(str);
		rep(i,0,n)str[i]-='a';
		rep(i,0,n){
			init();
			rep(j,i,n){
				extend(str[j]);
				ans[i][j]=tot;
			}
		}
	}
	void solve(){
		int m;
		rd(m);
		for(int L,R;m--;){
			rd(L),rd(R);
			ptn(ans[L-1][R-1]);
		}
	}
}SAM;

void solve(){
	scanf("%s",str);
	SAM.cons();
	SAM.solve();
}

int main(){
	int cas;
	for(rd(cas);cas--;)solve();
	return 0;
}

/*
	
	Sept.09.16

	Tags:string,SAM
	Submissions:1

	Exe.Time 764MS
	Exe.Memory 15828K
	Code Len. 3194B


*/
