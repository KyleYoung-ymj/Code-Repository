#include <bits/stdc++.h>
#define fi first
#define se second
#define y0 vjfuyg
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


const int N=(int)2e5+5;

int tot_y,K[N],ans[N],bit[N];
ll X[N],Y[N];
pll dat[N];

struct Ope{
	int x,y,id;
	Ope(){}
	Ope(int x,int y,int id):x(x),y(y),id(id){}
	bool operator <(const Ope &rhs)const{
		if(x!=rhs.x)return x<rhs.x;
		return y<rhs.y;
	}
}ope[N];

void modify(int &x,int &y){
	int K=(int)21e8/max(abs(x),abs(y));
	x*=K,y*=K;
	++x;
}

inline void add(int x,int val){
	for(;x<=tot_y;x+=lowbit(x))bit[x]+=val;
}
int sum(int x){
	int res=0;
	for(;x;x-=lowbit(x))res+=bit[x];
	return res;
}

void solve(int l,int r,int L,int R){
	if(l==r)return;
	if(L==R-1){
		rep(i,l,r)ans[ope[i].id]=L;
		return;
	}
	int mid=L+R>>1,ptr=l;
	sort(ope+l,ope+r);
	rep(i,l,r){
		int cnt=sum(ope[i].y);
		if(ope[i].id<mid||cnt>=K[ope[i].id]){
			add(ope[i].y,1);
			swap(ope[i],ope[ptr++]);
		}
		else K[ope[i].id]-=cnt;
	}
	rep(i,l,ptr)add(ope[i].y,-1);
	solve(l,ptr,L,mid);
	solve(ptr,r,mid,R);
}

int main(){
	int n,x0,y0,x1,y1;
	rd(n);
	scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
	if((ll)x1*y0==(ll)x0*y1)modify(x0,y0);
	if((ll)x1*y0<(ll)x0*y1)swap(x0,x1),swap(y0,y1);
	for(int i=0,x,y;i<n;++i){
		scanf("%d%d",&x,&y);
		ll x_=(ll)y*x1-(ll)x*y1,y_=(ll)x*y0-(ll)y*x0;
		dat[i]=pll(x_,y_);
		X[i]=x_,Y[i]=y_;
	}
	rep(i,0,n)rd(K[i]);
	sort(X,X+n),sort(Y,Y+n);
	int tot_x=unique(X,X+n)-X;
	tot_y=unique(Y,Y+n)-Y;
	rep(i,0,n){
		int x=lower_bound(X,X+tot_x,dat[i].fi)-X,
			y=lower_bound(Y,Y+tot_y,dat[i].se)-Y+1;
		ope[i]=Ope(x,y,i);
	}
	solve(0,n,0,n);
	rep(i,0,n)pt(ans[i]+1),putchar(" \n"[i==n-1]);
	return 0;
}

/*
	
	Oct.18.16
	
	Tags:data structure,geometry,binary search
	Submissions:1
	
	Memory 12644KB
	Time 948MS
	Code Length 3527B
	
*/

