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

const int P=(7*17<<23)+1,r=3;

inline void mod_add(int &a,int b){
    if((a+=b)>=P)a-=P;
}
inline void mod_minus(int &a,int b){
    if((a-=b)<0)a+=P;
}
int fast_mod_pow(int a,int b){
    int res=1;
    for(;b;b>>=1,a=1ll*a*a%P)
        if(b&1)res=1ll*res*a%P;
    return res;
}
inline int calc_inv(int x){
    return fast_mod_pow(x,P-2);
}


const int N=(1<<18)+5;

int rev[N],A[N],B[N],C[N];

void DFT(int *arr,int n,bool flag){
    rep(i,0,n)if(i<rev[i])swap(arr[i],arr[rev[i]]);
    for(int m=2;m<=n;m<<=1){
        int g=fast_mod_pow(r,(P-1)/m);
        if(flag)g=calc_inv(g);
        for(int i=0;i<n;i+=m){
            int cur=1;
            rep(j,0,m>>1){
                int x=arr[i+j],y=1ll*cur*arr[i+j+(m>>1)]%P;
                mod_add(arr[i+j]=x,y);
                mod_minus(arr[i+j+(m>>1)]=x,y);
                cur=1ll*cur*g%P;
            }
        }
    }
}
void NTT(int n,int m){
    int _n,S;
    for(_n=1,S=0;_n<n+m;_n<<=1,++S);
    rep(i,1,_n)rev[i]=(rev[i>>1]>>1)|((i&1)<<S-1);
    rep(i,n,_n)A[i]=0;
    rep(i,m,_n)B[i]=0;
    DFT(A,_n,false);
    DFT(B,_n,false);
    rep(i,0,_n)C[i]=1ll*A[i]*B[i]%P;
    DFT(C,_n,true);
    int inv=calc_inv(_n);
    rep(i,0,_n)C[i]=1ll*C[i]*inv%P;
}

int main(){
    int n,m;
    rd(n),rd(m);
    ++n,++m;
    rep(i,0,n)rd(A[i]);
    rep(i,0,m)rd(B[i]);
    NTT(n,m);
    rep(i,0,n+m-1)pt(C[i]),putchar(" \n"[i==n+m-2]);
    return 0;
}
/*
	
	Aug.16.16

	Problem:UOJ #34
	
*/
