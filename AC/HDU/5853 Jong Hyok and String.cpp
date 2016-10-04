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


const int N=(int)1e5+5;

char str[N];

struct Suffix_Automaton{
	static const int NODE=N<<2,C=27;
	int allc,last,par[NODE],len[NODE],trans[NODE][C],mx[NODE];
	int NewNode(){
		int ret=++allc;
		memset(trans[ret],0,C<<2);
		return ret;
	}
	void init(){
		allc=0;
		last=NewNode();
		par[last]=len[last]=mx[last]=0;
	}
	void extend(int c,int id){
		int np=NewNode(),p=last;
		len[np]=len[last]+1;
		mx[np]=id;
		for(;p&&!trans[p][c];p=par[p])trans[p][c]=np;
		if(!p)par[np]=1;
		else{
			int q=trans[p][c];
			if(len[q]==len[p]+1)par[np]=q;
			else{
				int nq=++allc;
				par[nq]=par[q];
				len[nq]=len[p]+1;
				mx[nq]=min(len[nq],mx[q]);
				memcpy(trans[nq],trans[q],C<<2);
				par[np]=par[q]=nq;
				for(trans[p][c]=nq,p=par[p];p&&trans[p][c]==q;p=par[p])trans[p][c]=nq;
			}
		}
		last=np;
	}
	int solve(){
		int cur=1;
		rep(i,0,strlen(str)){
			cur=trans[cur][str[i]-'a'];
			if(!cur)return 0;
		}
		return mx[cur]-len[par[cur]];
	}
}SAM;

void solve(){
	int n,m;
	rd(n),rd(m);
	SAM.init();
	while(n--){
		scanf("%s",str);
		rep(i,0,strlen(str))SAM.extend(str[i]-'a',i+1);
		SAM.extend(26,0);
	}
	while(m--){
		scanf("%s",str);
		ptn(SAM.solve());
	}
}

int main(){
	int cas;
	rd(cas);
	rep(i,1,cas+1){
		printf("Case #%d:\n",i);
		solve();
	}
	return 0;
}

/*
	
	Sept.09.16

	Tags:SAM
	Submissions:3

	Exe.Time 452MS
	Exe.Memory 31644K
	Code Len. 3242B


*/
