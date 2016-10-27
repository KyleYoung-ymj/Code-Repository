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
template<class T>void rd(T &x)
{
    x=0;
    char c;
    while(c=getchar(),c<48);
    do x=(x<<3)+(x<<1)+(c^48);
        while(c=getchar(),c>47);
}
template<class T>void rec_pt(T x)
{
    if(!x)return;
    rec_pt(x/10);
    putchar(x%10^48);
}
template<class T>void pt(T x)
{
    if(!x)putchar('0');
    else rec_pt(x);
}
template<class T>inline void ptn(T x)
{
    pt(x),putchar('\n');
}
template<class T>inline void Max(T &a,T b)
{
    if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b)
{
    if(b<a)a=b;
}
template<class T>T gcd(T a,T b)
{
    return b?gcd(b,a%b):a;
}
inline void mod_add(int &a,int b,int m=mod)
{
    if((a+=b)>=m)a-=m;
}
inline void mod_minus(int &a,int b,int m=mod)
{
    if((a-=b)<0)a+=m;
}
int mod_pow(int a,int b,int m=mod)
{
    int res=1;
    for(;b;b>>=1,a=(ll)a*a%m)
        if(b&1)res=(ll)res*a%m;
    return res;
}
inline int calc_inv(int x,int m=mod)
{
    return mod_pow(x,m-2);
}


const int N=(int)1e6+5;

int val[N],arr[N],pos[N],nxt[N],cnt[N];
ll org[N];

struct Segment_Tree
{
	struct Node
	{
		ll mx,tag;
		inline void operator +=(ll val)
		{
			mx+=val,tag+=val;
		}
	}
	tree[N<<2];
	inline void push_up(int k)
	{
		tree[k].mx=max(tree[lson].mx,tree[rson].mx);
	}
	void push_down(int k)
	{
		ll &tag=tree[k].tag;
		if(!tag)return;
		tree[lson]+=tag,tree[rson]+=tag;
		tag=0;
	}
	void cons(int L,int R,int k=1)
	{
		if(L==R)
		{
			tree[k].mx=org[L];
			return;
		}
		int mid=L+R>>1;
		cons(L,mid,lson);
		cons(mid+1,R,rson);
		push_up(k);
	}
	ll query(int L,int R,int l,int r,int k=1)
	{
		if(l==L&&r==R)return tree[k].mx;
		push_down(k);
		int mid=l+r>>1;
		if(R<=mid)return query(L,R,l,mid,lson);
		if(L>mid)return query(L,R,mid+1,r,rson);
		return max(query(L,mid,l,mid,lson),query(mid+1,R,mid+1,r,rson));
	}
	void add(int L,int R,int l,int r,ll val,int k=1)
	{
		if(l==L&&r==R)
		{
			tree[k]+=val;
			return;
		}
		push_down(k);
		int mid=l+r>>1;
		if(R<=mid)add(L,R,l,mid,val,lson);
		else if(L>mid)add(L,R,mid+1,r,val,rson);
		else
		{
			add(L,mid,l,mid,val,lson);
			add(mid+1,R,mid+1,r,val,rson);
		}
		push_up(k);
	}
}
smt;

int main()
{
	int n,m;
	rd(n),rd(m);
	rep(i,1,n+1)rd(arr[i]);
	rep(i,1,m+1)rd(val[i]);
	per(i,1,n+1)
	{
		nxt[i]=pos[arr[i]];
		if(!nxt[i])nxt[i]=n+1;
		pos[arr[i]]=i;
	}
	ll ans=0;
	rep(i,1,n+1)
	{
		org[i]=org[i-1];
		if(++cnt[arr[i]]==1)org[i]+=val[arr[i]];
		else if(cnt[arr[i]]==2)org[i]-=val[arr[i]];
		Max(ans,org[i]);
	}
	smt.cons(1,n);
	rep(i,2,n+1)
	{
		if(nxt[i-1]!=i)smt.add(i,nxt[i-1]-1,1,n,-val[arr[i-1]]);
		if(nxt[i-1]<=n)smt.add(nxt[i-1],nxt[nxt[i-1]]-1,1,n,val[arr[i-1]]);
		Max(ans,smt.query(i,n,1,n));
	}
	ptn(ans);
	return 0;
}

/*
	
	Oct.25.16
	
	Tags:data structure,segment tree
	Submissions:2
	
	Memory 91544KB
	Time 3768ms
	Code Length 3914B
	
*/

