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
#define debug(x) cout<<#x<<"="<<(x)<<endl
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
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
inline void mod_minus(int &a,int b){
	if((a-=b)<0)a+=mod;
}
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)res=(ll)res*a%mod;
	return res;
}
inline int calc_inv(int x){
	return fast_mod_pow(x,mod-2);
}


const int N=(int)1e3+5;

db pr[26];

class SquareScores {
public:
	db calcexpectation(veci p, string str) {
		rep(i,0,siz(p))pr[i]=p[i]/100.0;
		rep(i,siz(p),26)pr[i]=0;
		int n=siz(str);
		db ans=0;
		rep(i,0,n){
			int cnt=0;
			char c='?';
			bool flag=false;
			rep(j,i,n){
				if(str[j]=='?')++cnt;
				else{
					if(c=='?')c=str[j];
					else if(c!=str[j])flag=true;
				}
				if(flag)break;
				if(!cnt)++ans;
				else if(c=='?'){
					rep(k,0,26)ans+=pow(pr[k],cnt);
				}
				else{
					ans+=pow(pr[c-'a'],cnt);
				}
			}
		}
		return ans;
	}
};

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <int> p0, string p1, bool hasAnswer, double p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << "\"" << p1 << "\"";
	cout << "]" << endl;
	SquareScores *obj;
	double answer;
	obj = new SquareScores();
	clock_t startTime = clock();
	answer = obj->calcexpectation(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p2 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = fabs(p2 - answer) <= 1e-9 * max(1.0, fabs(p2));
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
	
	vector <int> p0;
	string p1;
	double p2;
	
	{
	// ----- test 0 -----
	int t0[] = {1,99};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "aaaba";
	p2 = 8.0;
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	int t0[] = {10,20,70};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "aa?bbbb";
	p2 = 15.0;
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	int t0[] = {10,20,30,40};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "a?" "?c?dc?b";
	p2 = 11.117;
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	int t0[] = {25,25,21,2,2,25};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "a?" "?b?" "?" "?" "?" "?" "?" "?ff?" "?e";
	p2 = 21.68512690712425;
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	int t0[] = {4,4,4,3,4,4,4,4,4,4,3,4,4,4,3,4,4,4,4,4,4,4,3,4,4,4};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?";
	p2 = 31.16931963781721;
	all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	int t0[] = {4,3,4,3,8,2,4,3,4,4,3,2,4,4,3,4,2,4,7,6,4,4,3,4,4,3};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "makigotapresentfromniko";
	p2 = 23.0;
	all_right = KawigiEdit_RunTest(5, p0, p1, true, p2) && all_right;
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
	
	Aug.24.16

	Tags:Probability
	
*/
