#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5e4+5;
int n,m,S,col[N],cnt[N]={0};
struct Query{
	int id,L,R;
	inline bool operator <(const Query &tmp)const{
		int a=L/S,b=tmp.L/S;
		if(a!=b)return a<b;
		return R<tmp.R;
	}
	inline void rd(){
		scanf("%d%d",&L,&R);
	}
}query[N];
struct Ans{
	ll a,b;
	ll gcd(ll a,ll b){
		return b?gcd(b,a%b):a;
	}
	void reduce(){
		ll d=gcd(a,b);
		a/=d;
		b/=d;
	}
	void print(){
		reduce();
		printf("%lld/%lld\n",a,b);
	}
}ans[N];
inline ll sqr(int x){
	return 1ll*x*x;
}
void solve(){
	int L=1,R=0;
	ll res=0;
	for(int i=0;i<m;++i){
		while(L<query[i].L){
			res-=sqr(cnt[col[L]]);
			--cnt[col[L]];
			res+=sqr(cnt[col[L]]);
			++L;
		}
		while(L>query[i].L){
			--L;
			res-=sqr(cnt[col[L]]);
			++cnt[col[L]];
			res+=sqr(cnt[col[L]]);
		}
		while(R<query[i].R){
			++R;
			res-=sqr(cnt[col[R]]);
			++cnt[col[R]];
			res+=sqr(cnt[col[R]]);
		}
		while(R>query[i].R){
			res-=sqr(cnt[col[R]]);
			--cnt[col[R]];
			res+=sqr(cnt[col[R]]);
			--R;
		}
		ans[query[i].id].a=res-(R-L+1);
		ans[query[i].id].b=1ll*(R-L+1)*(R-L);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	S=(int)sqrt(n)+0.5;
	for(int i=1;i<=n;++i)
		scanf("%d",&col[i]);
	for(int i=0;i<m;++i){
		query[i].id=i;
		query[i].rd();
	}
	sort(query,query+m);
	solve();
	for(int i=0;i<m;++i)
		ans[i].print();
	return 0;
}
/*
	
	Mar.25.16
	
	Tags:"Modui Algorithm"
	Submissions:1
	
	Memory 2580kb
	Time 1320ms
	Code Length 1632B
	
*/
