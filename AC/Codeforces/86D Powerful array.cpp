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
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
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
const int N=(int)2e5+5,MX=(int)1e6+5;
int S,num[N],cnt[MX];
ll res,ans[N];
struct Query{
	int id,L,R;
	inline void Rd(){
		rd(L);rd(R);
	}
	inline bool operator <(const Query &tmp)const{
		int a=L/S,b=tmp.L/S;
		if(a!=b)return a<b;
		return R<tmp.R;
	}
}query[N];
ll sqr(int x){
	return 1ll*x*x;
}
void adjust(int tar,int sgn){
	res-=tar*sqr(cnt[tar]);
	cnt[tar]+=sgn;
	res+=tar*sqr(cnt[tar]);
}
int main(){
	int n,m;
	rd(n);rd(m);
	for(int i=1;i<=n;++i)
		rd(num[i]);
	for(int i=0;i<m;++i){
		query[i].Rd();
		query[i].id=i;
	}
	S=(int)sqrt(n);
	if(!S)++S;
	sort(query,query+m);
	for(int i=0,L=1,R=0;i<m;++i){
		while(R<query[i].R)adjust(num[++R],1);
		while(L>query[i].L)adjust(num[--L],1);
		while(R>query[i].R)adjust(num[R--],-1);
		while(L<query[i].L)adjust(num[L++],-1);
		ans[query[i].id]=res;
	}
	for(int i=0;i<m;++i)
		printf("%I64d\n",ans[i]);
	return 0;
}
/*
	
	Jul.12.16

	Tags:mo-algorithm
	Submissions:2

	Time 3524ms
	Memory 8600KB

*/
