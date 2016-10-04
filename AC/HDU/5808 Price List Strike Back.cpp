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
#define rep(i,s,t) for(int i=s,_t=t;i<_t;++i)
#define per(i,s,t) for(int i=t-1,_s=s;i>=_s;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
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


const int N=(int)2e4+5,M=(int)1e5+5,V=105;

int val[N],cost[N],arr[M],dp[N][V];
bool ans[M];

struct Query{
	int id,L,R,lim,sum;
	void Rd(){
		rd(L),rd(R),rd(lim),rd(sum);
		--L,--R;
	}
}query[M];

inline void DP(int *tar,int v,int c){
	per(i,v,V)Min(tar[i],max(tar[i-v],c));
}
void conquer(int L,int R,int tot){
	int mid=L+R>>1;
	rep(i,1,V)dp[mid-1][i]=dp[mid][i]=inf;
	per(i,L,mid){
		if(i<mid-1)rep(j,0,V)dp[i][j]=dp[i+1][j];
		DP(dp[i],val[i],cost[i]);
	}
	rep(i,mid,R){
		if(i>mid)rep(j,0,V)dp[i][j]=dp[i-1][j];
		DP(dp[i],val[i],cost[i]);
	}
	rep(i,0,tot){
		Query &tar=query[arr[i]];
		ans[tar.id]=false;
		rep(j,0,tar.sum+1){
			if(dp[tar.L][j]<=tar.lim&&dp[tar.R][tar.sum-j]<=tar.lim){
				ans[tar.id]=true;
				break;
			}
		}
	}
}
void divide(int L,int R,int tot){
	if(!tot)return;
	if(L+1==R){
		rep(i,0,tot)ans[query[arr[i]].id]=cost[L]<=query[arr[i]].lim&&val[L]==query[arr[i]].sum;
		return;
	}

	int mid=L+R>>1,cnt;

	cnt=0;
	rep(i,0,tot)if(query[arr[i]].R<mid)
		swap(arr[i],arr[cnt++]);
	divide(L,mid,cnt);

	cnt=0;
	rep(i,0,tot)if(query[arr[i]].L>=mid)
		swap(arr[i],arr[cnt++]);
	divide(mid,R,cnt);

	cnt=0;
	rep(i,0,tot)if(query[arr[i]].L<mid&&query[arr[i]].R>=mid)
		swap(arr[i],arr[cnt++]);
	conquer(L,R,cnt);

}

void solve(){
	int n,m;
	rd(n),rd(m);
	rep(i,0,n)rd(val[i]);
	rep(i,0,n)rd(cost[i]);
	rep(i,0,m){
		arr[i]=i;
		query[i].Rd();
		query[i].id=i;
	}
	divide(0,n,m);
	rep(i,0,m)putchar(ans[i]^1^48);
	putchar('\n');
}
int main(){
	int cas;
	for(rd(cas);cas--;)solve();
	return 0;
}
/*
	
	Aug.12.16

	Tags:divide and conquer,dp
	Submissions:1

	Exe.Time 1076MS
	Exe.Memory 12384K
	Code Len. 3072B

*/
