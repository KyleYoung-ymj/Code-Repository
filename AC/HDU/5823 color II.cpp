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
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
#define rep(i,s,t) for(register int i=s,_t=t;i<_t;++i)
#define per(i,s,t) for(register int i=t-1,_s=s;i>=_s;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int mod=(int)1e9+7,inf=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
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
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}


const int N=18,M=1<<N;
int n,bin[M],mask[N],col[M],A[M],B[M],C[M];
bool ind[M];
char str[N+5];
ui pw[M];

void init(){
	pw[0]=ind[0]=1;
	rep(i,1,M)pw[i]=pw[i-1]*233;
	rep(i,0,N)bin[1<<i]=i;
}
void or_conv(){
	rep(i,0,n)rep(j,1,1<<n)if(j&1<<i){
		A[j]+=A[j^1<<i];
		B[j]+=B[j^1<<i];
	}
	rep(i,0,1<<n)C[i]=A[i]*B[i];
	rep(i,0,n)rep(j,1,1<<n)if(j&1<<i)
		C[j]-=C[j^1<<i];
}

void solve(){
	rd(n);
	rep(i,0,n){
		mask[i]=0;
		scanf("%s",str);
		rep(j,0,n)if(str[j]=='1')mask[i]|=1<<j;
	}
	rep(S,1,1<<n){
		int sub=S^lowbit(S);
		col[S]=ind[S]=ind[sub]&!(mask[bin[lowbit(S)]]&sub);
	}
	for(int i=1;;){
		if(col[(1<<n)-1])break;
		rep(j,0,1<<n)A[j]=col[j]==i;
		rep(j,0,1<<n)B[j]=ind[j];
		or_conv();
		++i;
		rep(j,1,1<<n)if(C[j]&&!col[j])col[j]=i;
	}
	ui ans=0;
	rep(i,1,1<<n)ans+=col[i]*pw[i];
	ptn(ans);
}

int main(){
	int cas;
	init();
	for(rd(cas);cas--;)solve();
	return 0;
}
/*
	
	Aug.14.16

	Tags:dp,convolution
	Submissions:1

	Exe.Time 280MS
	Exe.Memory 7004K
	Code Len. 2431B

*/
