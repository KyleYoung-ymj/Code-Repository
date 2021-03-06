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
inline void mod_add(int &a,int b,int m=mod){
	if((a+=b)>=m)a-=m;
}
inline void mod_minus(int &a,int b,int m=mod){
	if((a-=b)<0)a+=m;
}
int fast_mod_pow(int a,int b,int m=mod){
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}
inline int calc_inv(int x,int m=mod){
	return fast_mod_pow(x,m-2);
}


const int N=55;

int col[N];

vector<pii>G[N];

bool paint(int cur,bool c){
	col[cur]=c;
	rep(i,0,siz(G[cur])){
		int to=G[cur][i].fi,cost=G[cur][i].se;
		if(~col[to]){
			if(col[to]!=(c^cost))return false;
		}
		else if(!paint(to,c^cost))return false;
	}
	return true;
}

class OddEvenTreeHard {
public:
	veci getTree(vector <string> str) {
		int n=siz(str);
		memset(col,-1,sizeof col);
		rep(i,0,n)G[i].clear();
		rep(i,0,n)rep(j,0,n){
			if(str[i][j]=='?')continue;
			if(i==j){
				if(str[i][j]=='O')return veci(1,-1);
				continue;
			}
			if(str[i][j]=='E')G[i].pb(pii(j,0)),G[j].pb(pii(i,0));
			else G[i].pb(pii(j,1)),G[j].pb(pii(i,1));
		}
		if(!paint(0,0))return veci(1,-1);
		rep(i,1,n)if(col[i]==-1&&!paint(i,1))return veci(1,-1);
		int odd=-1;
		rep(i,1,n)if(col[i]){
			odd=i;
			break;
		}
		veci ans;
		rep(i,1,n){
			if(col[i])ans.pb(0),ans.pb(i);
			else{
				if(odd==-1)return veci(1,-1);
				ans.pb(odd),ans.pb(i);
			}
		}
		return ans;
	}
};

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <string> p0, bool hasAnswer, vector <int> p1) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	OddEvenTreeHard *obj;
	vector <int> answer;
	obj = new OddEvenTreeHard();
	clock_t startTime = clock();
	answer = obj->getTree(p0);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "{";
		for (int i = 0; int(p1.size()) > i; ++i) {
			if (i > 0) {
				cout << ",";
			}
			cout << p1[i];
		}
		cout << "}" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "{";
	for (int i = 0; int(answer.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << answer[i];
	}
	cout << "}" << endl;
	if (hasAnswer) {
		if (answer.size() != p1.size()) {
			res = false;
		} else {
			for (int i = 0; int(answer.size()) > i; ++i) {
				if (answer[i] != p1[i]) {
					res = false;
				}
			}
		}
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
	
	vector <string> p0;
	vector <int> p1;
	
	{
	// ----- test 0 -----
	string t0[] = {"EOE","OEO","EOE"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,1,2,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	string t0[] = {"?" "?" "?" "?","?" "?" "?" "?","?" "?" "?" "?","?" "?" "?" "?"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,1,0,3,2,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	string t0[] = {"?" "?" "?" "?","?" "?" "?" "?","?" "?O?","?" "?" "?" "?"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {-1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	string t0[] = {"?" "?O?","?" "?" "?" "?","E?" "?" "?","?" "?" "?" "?"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {-1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	string t0[] = {"?O?" "?","?" "?O?","?" "?" "?O","?" "?" "?" "?"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,1,0,3,2,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	string t0[] = {"?E?" "?","?" "?E?","?" "?" "?E","?" "?" "?" "?"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {-1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	all_right = KawigiEdit_RunTest(5, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 6 -----
	string t0[] = {"?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?","?" "?" "?" "?" "?" "?" "?" "?" "?" "?OE?","?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?","?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?","?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?","?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?","?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?","?" "?" "?" "?" "?" "?" "?E?" "?" "?" "?" "?","?" "?" "?" "?" "?" "?" "?E?" "?" "?" "?" "?","?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?","?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?O?","?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?E?","?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?" "?E"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,1,0,3,0,5,0,7,0,8,0,11,0,12,2,1,4,1,6,1,9,1,10,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	all_right = KawigiEdit_RunTest(6, p0, true, p1) && all_right;
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
	
	Aug.28.16

	Tags:bipartite

*/
