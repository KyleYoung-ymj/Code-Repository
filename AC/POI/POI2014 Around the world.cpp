#include <bits/stdc++.h>
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
const int inf=0x7fffffff,mod=(int)1e9+7,dxy[]={-1,0,1,0,-1};
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


const int N=(int)2e6+5;

int dist[N],nxt[N],par[N],dep[N],arr[N];

int get_root(int x){
	return par[x]==x?x:par[x]=get_root(par[x]);
}

int main(){
	int size = 32 << 20; // 32MB
	char *p = (char*)malloc(size) + size;
	__asm__("movl %0, %%esp\n" :: "r"(p));
	freopen("doo16a.in","r",stdin);//
	freopen("data.out","w",stdout);//
	int n,m,mx=0;
	rd(n),rd(m);
	int _n=n<<1;
	rep(i,1,_n+1){
		int j=i+1;
		if(i<=n){
			rd(dist[j]);
			Max(mx,dist[j]);
		}
		else dist[j]=dist[j-n]-dist[i-n];
		dist[j]+=dist[i];
	}
	nxt[_n]=par[_n]=_n;
	for(int K;m--;){
		rd(K);
		if(K<mx)puts("NIE");
		else{
			per(i,1,_n){
				int &res=nxt[i];
				for(res=nxt[i+1];dist[res]-dist[i]>K;--res);
				par[i]=i;
				dep[i]=dep[res]+1;
			}
			int ans=inf;
			rep(i,1,n+1){
				int tot=0;
				for(int u=get_root(i);;){
					if(u>=i+n){
						Min(ans,dep[i]-dep[u]);
						rep(i,0,tot)par[arr[i]]=u;
						break;
					}
					arr[tot++]=u;
					u=get_root(nxt[get_root(u)]);
				}
			}
			ptn(ans);
		}
	}
	return 0;
}

/*
	
	Oct.06.16
	
	Tags:implementation,dsu
	Submissions:2
	
	Memory 64076KB
	Time 8696MS
	Code Length 2623B
	
*/

