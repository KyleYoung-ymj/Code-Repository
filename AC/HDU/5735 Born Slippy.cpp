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
    do res=(res<<3)+(res<<1)+(c^48);
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
const int N=(1<<16)+5,M=(1<<8)+5;
uint ans,tot_edge,head[N],val[N],mark[M],mx[M][M],tmp[N][M];
char str[5];
struct Edge{
    int to,nxt;
    Edge(){}
    Edge(int to,int nxt):to(to),nxt(nxt){}
}edge[N];
inline void add_edge(int u,int v){
    edge[++tot_edge]=Edge(v,head[u]);
    head[u]=tot_edge;
}
inline int calc(int a,int b){
    if(str[0]=='A')return a&b;
    return a^b;
}
void or_dfs(int cur,int par,int sum){
    if(~par)mod_add(sum,val[cur]|val[par]);
    ans=(ans+1ll*cur*(val[cur]+sum))%mod;
    for(int i=head[cur];i;i=edge[i].nxt){
        int son=edge[i].to;
        or_dfs(son,cur,sum);
    }
}
void dfs(int cur){
    uint dp=0,x=val[cur]>>8,y=val[cur]&255;
    for(int i=0;i<256;++i){
        if(mark[i]){
            Max(dp,mx[y][i]+(calc(x,i)<<8));
        }
    }
    ans=(ans+1ll*cur*(dp+val[cur]))%mod;
    ++mark[x];
    for(int i=0;i<256;++i){
        tmp[cur][i]=mx[i][x];
        Max(mx[i][x],dp+calc(y,i));
    }
    for(int i=head[cur];i;i=edge[i].nxt)
        dfs(edge[i].to);
    --mark[x];
    for(int i=0;i<256;++i)
        mx[i][x]=tmp[cur][i];
}
void solve(){
    int n;
    rd(n);
    scanf("%s",str);
    tot_edge=0;
    for(int i=1;i<=n;++i){
        head[i]=0;
        rd(val[i]);
    }
    for(int i=2,par;i<=n;++i){
        rd(par);
        add_edge(par,i);
    }
    ans=0;
    if(str[0]=='O')or_dfs(1,-1,0);
    else dfs(1);
    print(ans);
    putchar('\n');
}
int main(){
    int cas;
    for(rd(cas);cas--;)solve();
    return 0;
}
/*
	
	Jul.22.16
	
	Tags:tree,meet-in-the-middle
	Submissions:20
	
	Exe.Time 3556MS
	Exe.Memory 73036K
	Code Len. 3256B
	
*/
