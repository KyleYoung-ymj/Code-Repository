#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
typedef set<int>::iterator ite;
const int N=1e5+5,M=N<<1;
int num[N],str[M],r[M];
set<int>id;
struct UNIT{
	int val,id;
	inline bool operator <(const UNIT &tmp)const{
		return val<tmp.val;
	}
};
multiset<UNIT>val;
inline void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
void Manacher(int n){
	int mx=0,id=0;
	for(int i=1;i<n;++i){
		r[i]=mx>i?min(r[(id<<1)-i],mx-i):1;
		while(str[i-r[i]]==str[i+r[i]])++r[i];
		if(i+r[i]>mx){
			mx=i+r[i];
			id=i;
		}
	}
}
inline int calc(int L,int R){
	return R-L+1>>1;
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
void solve(){
	int n,m=0;
	rd(n);
	for(int i=1;i<=n;++i)
		rd(num[i]);
	str[m++]=-2;
	for(int i=1;i<=n;++i){
		str[m++]=-1;
		str[m++]=num[i];
	}
	str[m++]=-1;
	str[m]=0;
	Manacher(m);
	int ans=0;
	val.clear();
	id.clear();
	for(int i=1;i<m;++i){
		if(str[i]==-1){
			int mx=i+r[i]-1,mi=i-r[i]+1;
			while(!val.empty()&&(*val.begin()).val<i-1){
				id.erase((*val.begin()).id);
				val.erase(val.begin());
			}
			ite it=id.lower_bound(mi-1);
			if(it!=id.end())Max(ans,3*calc(*it,i-1));
			val.insert((UNIT){mx,i});
			id.insert(i);
		}
	}
	printf("%d\n",ans);
}
int main(){
	int cas,kase=0;
	rd(cas);
	while(cas--){
		printf("Case #%d: ",++kase);
		solve();
	}
	return 0;
}
/*
	
	Jun.28.16
	
	Tags:Manacher,set
	
	Memory(KB) 8240
	Time(ms) 1606
	Length(Bytes) 1378
	
*/
