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


static const int N=(int)1e5+5;

char str[N];

struct Suffix_Automaton{
	static const int NODE=N<<1,C=26;
	int allc,last,par[NODE],len[NODE],trans[NODE][C],
		cnt[NODE],arr[NODE],mx[NODE],mi[NODE];
	int NewNode(){
		int ret=++allc;
		memset(trans[ret],0,C<<2);
		return ret;
	}
	void init(){
		allc=0;
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
				memcpy(trans[nq],trans[q],C<<2);
				len[nq]=len[p]+1;
				par[np]=par[q]=nq;
				for(;p&&trans[p][c]==q;p=par[p])trans[p][c]=nq;
			}
		}
		last=np;
	}
	void cons(){
		init();
		int n=strlen(str);
		rep(i,0,n)extend(str[i]-'a');
		memset(cnt,0,allc+1<<2);
		rep(i,1,allc+1){
			mi[i]=len[i];
			++cnt[len[i]];
		}
		rep(i,1,n+1)cnt[i]+=cnt[i-1];
		rep(i,1,allc+1)arr[--cnt[len[i]]]=i;
	}
	void consider(){
		memset(mx,0,allc+1<<2);
		int cur=1,cur_len=0;
		rep(i,0,strlen(str)){
			int c=str[i]-'a';
			if(trans[cur][c]){
				cur=trans[cur][c];
				++cur_len;
			}
			else{
				for(;cur&&!trans[cur][c];cur=par[cur]);
				if(!cur){
					cur=1;
					cur_len=0;
				}
				else{
					cur_len=len[cur]+1;
					cur=trans[cur][c];
				}
			}
			Max(mx[cur],cur_len);
		}
		per(i,0,allc){
			int tar=arr[i];
			Min(mi[tar],mx[tar]);
			if(mx[tar]&&par[tar])mx[par[tar]]=len[par[tar]];
		}
	}
	int solve(){
		int ans=0;
		rep(i,1,allc+1)Max(ans,mi[i]);
		return ans;
	}
}SAM;

int main(){
	scanf("%s",str);
	SAM.cons();
	while(~scanf("%s",str))SAM.consider();
	ptn(SAM.solve());
	return 0;
}

/*
	
	Sept.08.16

	Tags:string,SAM
	Submissions:3

	TIME 0.09
	MEM 27M

*/
