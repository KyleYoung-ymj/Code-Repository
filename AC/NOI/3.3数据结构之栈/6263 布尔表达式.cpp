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


const int LEN=(int)1e3+5;

int tp_ope,tp;
char str[LEN],stk_ope[LEN];
bool stk[LEN];

int priority(char c)
{
	switch(c)
	{
		case '!':return 3;
		case '&':return 2;
		case '|':return 1;
		default:return 0;// ')','$'
	}
}

inline bool calc(bool a,bool b,char c)
{
	return c=='&'?a&b:a|b;
}

void consider(char c)
{
	if(c=='('||c=='!')
	{
		stk_ope[tp_ope++]=c;
		return;
	}
	for(;tp_ope&&priority(stk_ope[tp_ope-1])>=priority(c);--tp_ope)
	{
		if(stk_ope[tp_ope-1]=='!')stk[tp-1]^=1;
		else if(stk_ope[tp_ope-1]!='(')
		{
			stk[tp-2]=calc(stk[tp-2],stk[tp-1],stk_ope[tp_ope-1]);
			--tp;
		}
		else if(stk_ope[tp_ope-1]=='(')
		{
			--tp_ope;
			break;
		}
	}
	if(c!=')')stk_ope[tp_ope++]=c;
}

void solve()
{
	tp_ope=0,tp=0;
	rep(i,0,strlen(str))
	{
		if(isspace(str[i]))continue;
		if(isalpha(str[i]))stk[tp++]=str[i]=='V';
		else consider(str[i]);
	}
	consider('$');
	puts(stk[0]?"V":"F");
}

int main()
{
	while(gets(str))solve();
	return 0;
}

/*
	
	Oct.28.16
	
	Tags:expression parsing,stack
	Submissions:1
	
	Memory 136KB
	Time 0ms
	Code Length 2537B
	
*/

