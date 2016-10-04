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


const int N=(int)1e3+5;

int n,m,a,b,deg[N],A[N],B[N],que[N],arr[N],dp[N];
bool in_A[N],in_B[N],adj[N][N];

bool topo_sort(bool *mark,int &cnt,int *arr,int tar){
	cnt=0;
	int L=0,R=0;
	rep(i,0,n)if(mark[i]&&!deg[i])que[R++]=i;
	while(L<R){
		int cur=que[L++];
		arr[cnt++]=cur;
		rep(i,0,n)if(mark[i]&&adj[cur][i]&&!--deg[i])que[R++]=i;
	}
	return cnt==tar;
}
bool check(int cur,int pos){
	rep(i,pos+1,a)if(!adj[B[cur]][A[i]])return false;
	return true;
}
int calc_LIS(int tot){
	if(!tot)return 0;
	dp[0]=1;
	int LIS=1;
	rep(i,1,tot){
		dp[i]=0;
		rep(j,0,i)if(arr[j]<=arr[i])Max(dp[i],dp[j]);
		Max(LIS,++dp[i]);
	}
	return LIS;
}

void solve(){
	rep(i,0,n){
		deg[i]=in_A[i]=0;
		rep(j,0,n)rd(adj[i][j]);
	}
	for(int i=0,x;i<m;++i){
		rd(x);
		in_A[x-1]=true;
	}
	rep(i,0,n)in_B[i]=in_A[i]^1;
	rep(i,0,n)rep(j,0,n)if(adj[i][j]){
		if(in_A[i]&&in_A[j]||in_B[i]&&in_B[j])++deg[j];
	}
	if(!topo_sort(in_A,a,A,m)){
		puts("NO");
		return;
	}
	if(!topo_sort(in_B,b,B,n-m)){
		puts("NO");
		return;
	}
	int cnt=0;
	rep(i,0,b){
		bool flag=false;
		rep(j,0,a){
			if(adj[B[i]][A[j]]){
				if(check(i,j))arr[cnt++]=j;
				flag=true;
				break;
			}
		}
		if(!flag)arr[cnt++]=a;
	}
	printf("YES %d\n",calc_LIS(cnt));
}

int main(){
	while(scanf("%d%d",&n,&m),n+m)solve();
	return 0;
}
/*
	
	Aug.12.16

	Tags:toposort,LIS
	Submissions:5

	Exe.Time 967MS
	Exe.Memory 2596K
	Code Len. 2824B

*/
