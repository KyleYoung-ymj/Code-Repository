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
const int mod=(int)1e9+7,inf=0x7fffffff,dxy[]={-1,0,1,0,-1};
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
int qpow(int a,int b,int m=mod){
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}
inline int calc_inv(int x,int m=mod){
	return qpow(x,m-2);
}


const int N=16;

int dp[N+1][N+1][1<<N];

class CampLunch {
public:
	int count(int n, int m, vector <string> str) {
		memset(dp,0,sizeof dp);
		dp[0][0][0]=1;
		rep(i,0,n){
			rep(j,1,m+1)rep(mask,0,1<<m){
				int cur=str[i][j-1]-'A',&res=dp[i][j][mask];
				if(mask&1<<cur)res=dp[i][j-1][mask^1<<cur];
				else{
					res=dp[i][j-1][mask];
					mod_add(res,dp[i][j-1][mask|1<<cur]);
					if(j>=2&&!(mask&1<<str[i][j-2]-'A'))mod_add(res,dp[i][j-2][mask]);
				}
			}
			rep(mask,0,1<<m)dp[i+1][0][mask]=dp[i][m][mask];
		}
		return dp[n][0][0];
	}
};

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, int p1, vector <string> p2, bool hasAnswer, int p3) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << "{";
	for (int i = 0; int(p2.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p2[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	CampLunch *obj;
	int answer;
	obj = new CampLunch();
	clock_t startTime = clock();
	answer = obj->count(p0, p1, p2);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p3 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p3;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	int p0;
	int p1;
	vector <string> p2;
	int p3;
	
	{
	// ----- test 0 -----
	p0 = 2;
	p1 = 2;
	string t2[] = {"AB","AB"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 7;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = 2;
	p1 = 3;
	string t2[] = {"ABC","ABC"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 22;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 2;
	p1 = 3;
	string t2[] = {"ABC","BAC"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 21;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = 1;
	p1 = 1;
	string t2[] = {"A"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 1;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	p0 = 1;
	p1 = 10;
	string t2[] = {"ABDEFHIGJC"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 89;
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	p0 = 16;
	p1 = 16;
	string t2[] = {"ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP","ABCDEFGHIJKLMNOP"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 950052677;
	all_right = KawigiEdit_RunTest(5, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING

/*
	
	Aug.31.16

	Tags:dp
	
*/
