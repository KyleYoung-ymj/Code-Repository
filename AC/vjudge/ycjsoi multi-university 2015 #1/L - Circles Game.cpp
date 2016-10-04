#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=2e4+5,INF=1e8;
typedef long long ll;
vector<int>son[N];
struct Circle{
	int x,y,r;
	inline void Rd(){
		scanf("%d%d%d",&x,&y,&r);
	}
	inline bool operator <(const Circle &tmp)const{
		return r>tmp.r;
	}
}circle[N];
inline ll sqr(int x){
	return 1ll*x*x;
}
inline bool contain(int inter,int ext){
	return sqr(circle[inter].x-circle[ext].x)+sqr(circle[inter].y-circle[ext].y)<=sqr(circle[ext].r);
}
void allc(int cur,int par){
	for(int i=0;i<son[par].size();++i){
		if(contain(cur,son[par][i])){
			allc(cur,son[par][i]);
			return;
		}
	}
	son[par].push_back(cur);
}
int calc_SG(int cur){
	int sum=0;
	for(int i=0;i<son[cur].size();++i)
		sum^=calc_SG(son[cur][i])+1;
	return sum;
}
int main(){
	int cas;
	scanf("%d",&cas);
	circle[0]=(Circle){0,0,INF};
	while(cas--){
		int n;
		scanf("%d",&n);
		for(int i=0;i<=n;++i)
			son[i].clear();
		for(int i=1;i<=n;++i)
			circle[i].Rd();
		sort(circle,circle+n+1);
		for(int i=1;i<=n;++i)
			allc(i,0);
		puts(calc_SG(0)?"Alice":"Bob");
	}
	return 0;
}
/*
	
	May.19.16
	
	Tags:Geometry,Game Theory
	Submissions:1
	
	Memory(KB) 2196
	Time(ms) 140
	Length(Bytes) 1082
	
*/
