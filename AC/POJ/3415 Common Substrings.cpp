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
const int mod=(int)1e9+7,inf=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const ll INF=1ll<<60;
const double pi=acos(-1.0),eps=1e-8;
template<class T>void rd(T &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
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
const int N=(int)2e5+5;
int K;
char str[N];
struct Suffix_Array{
	int n,sa[N],rk[N],height[N],cnt[N];
	pii stk[N];
	void construct(){
		int m='z'+1,*a=rk,*b=height;
		str[(n=strlen(str))++]='#';
		memset(cnt,0,m<<2);
		for(int i=0;i<n;++i)++cnt[a[i]=str[i]];
		for(int i=1;i<m;++i)cnt[i]+=cnt[i-1];
		for(int i=n-1;~i;--i)sa[--cnt[a[i]]]=i;
		for(int j=1,p=0;p<n;j<<=1,m=p){
			p=0;
			for(int i=n-j;i<n;++i)b[p++]=i;
			for(int i=0;i<n;++i)if(sa[i]>=j)b[p++]=sa[i]-j;
			memset(cnt,0,m<<2);
			for(int i=0;i<n;++i)++cnt[a[b[i]]];
			for(int i=1;i<m;++i)cnt[i]+=cnt[i-1];
			for(int i=n-1;~i;--i)sa[--cnt[a[b[i]]]]=b[i];
			swap(a,b);
			p=1;
			a[sa[0]]=0;
			for(int i=1;i<n;++i)
				a[sa[i]]=b[sa[i-1]]==b[sa[i]]&&b[sa[i-1]+j]==b[sa[i]+j]?p-1:p++;
		}
		--n;
		for(int i=1;i<=n;++i)
			rk[sa[i]]=i;
		for(int i=0,h=0;i<n;height[rk[i++]]=h){
			if(h)--h;
			for(int j=sa[rk[i]-1];str[i+h]==str[j+h];++h);
		}
		// puts(str);//
		// for(int i=1;i<=n;++i){
		// 	for(int j=sa[i];j<n;++j)
		// 		putchar(str[j]);//
		// 	putchar('\n');//
		// 	debug(height[i]);//
		// }
	}
	void solve(int m){
		ll ans=0,sum=0;
		for(int i=2,top=0;i<=n;++i){
			if(height[i]<K)sum=top=0;
			else{
				int cnt=0;
				if(sa[i-1]<m){
					++cnt;
					sum+=height[i]-K+1;
				}
				while(top&&stk[top-1].fi>=height[i]){
					--top;
					cnt+=stk[top].se;
					sum-=stk[top].se*(stk[top].fi-height[i]);
				}
				if(cnt)stk[top++]=pii(height[i],cnt);
				if(sa[i]>m)ans+=sum;
			}
		}
		sum=0;
		for(int i=2,top=0;i<=n;++i){
			if(height[i]<K)sum=top=0;
			else{
				int cnt=0;
				if(sa[i-1]>m){
					++cnt;
					sum+=height[i]-K+1;
				}
				while(top&&stk[top-1].fi>=height[i]){
					--top;
					cnt+=stk[top].se;
					sum-=stk[top].se*(stk[top].fi-height[i]);
				}
				if(cnt)stk[top++]=pii(height[i],cnt);
				if(sa[i]<m)ans+=sum;
			}
		}
		print(ans);
		putchar('\n');
	}
}SA;
int main(){
	while(rd(K),K){
		scanf("%s",str);
		int m=strlen(str);
		str[m]='$';
		scanf("%s",str+m+1);
		SA.construct();
		SA.solve(m);
	}
	return 0;
}
/*
	
	Jul.28.16

	Tags:SA,stack
	Submissions:1

	Memory 5568K
	Time 782MS
	Code Length 3417B

*/
