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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
void rd(int &res){
    res=0;
    char c;
    while(c=getchar(),c<48);
    do res=(res<<3)+(res<<1)+(c^48);
        while(c=getchar(),c>47);
}
inline void Max(int &a,int b){
    if(b>a)a=b;
}
inline void Min(int &a,int b){
    if(b<a)a=b;
}
inline void mod_add(int &a,int b){
    if((a+=b)>=mod)a-=mod;
}
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int main(){
	int n,m;
	rd(n);rd(m);
	++n;++m;
	ll ans=n*m;
	ans=ans*(ans-1)*(ans-2)/6;
	for(int i=0;i<=n;++i){
		for(int j=0;j<=m;++j){
			if(i|j){
				ans-=1ll*(gcd(i,j)-1)*(n-i)*(m-j)*(i&&j?2:1);
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
/*
	
	Jul.16.16

	Tags:math
	Submissions:2

	Memory 1288kb
	Time 352ms
	Code Length 1440B

*/
