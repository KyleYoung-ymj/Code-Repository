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
const int N=(int)1e3+5;
int tot,num[N],Bit[N][N],buf[N];
struct Item{
	int a,b;
	inline void Rd(){
		rd(a);rd(b);
	}
	inline bool operator <(const Item &tmp)const{
		if(a!=tmp.a)return a>tmp.a;
		return b<tmp.b;
	}
}item[N];
void update(int *bit,int x,int val){
	for(;x<=tot;x+=lowbit(x))
		Max(bit[x],val);
}
int query(int *bit,int x){
	int mx=0;
	for(;x;x-=lowbit(x))
		Max(mx,bit[x]);
	return mx;
}
void solve(){
	int n;
	rd(n);
	tot=0;
	for(int i=0;i<n;++i){
		item[i].Rd();
		num[tot++]=item[i].b;
	}
	sort(item,item+n);
	sort(num,num+tot);
	tot=unique(num,num+tot)-num;
	int ans=0;
	memset(Bit,0,sizeof Bit);
	for(int i=0;i<n;++i){
		int cur=lower_bound(num,num+tot,item[i].b)-num+1;
		for(int j=1;j<=tot;++j)
			Max(ans,buf[j]=query(Bit[j],cur)+1);
		for(int j=1;j<=tot;++j){
			update(Bit[cur],j,buf[j]);
			update(Bit[j],cur,buf[j]);
		}
	}
	printf("%d\n",ans);
}
int main(){
	int cas;
	for(rd(cas);cas--;)solve();
	return 0;
}
/*
	
	Jul.14.16

	Tags:dp,LIS,bit
	Submissions:2

	Memory(KB) 5520
	Time(ms) 2542
	Length(Bytes) 1896

*/
