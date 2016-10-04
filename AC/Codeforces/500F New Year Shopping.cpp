#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=4e3+5,INF=1e9;
int n,T,L[N][N]={0},R[N][N]={0};
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
struct Item{
	int cost,val,st;
	inline bool operator <(const Item &tmp)const{
		return st<tmp.st;
	}
	inline void Rd(){
		rd(cost);rd(val);rd(st);
	}
}item[N];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
void init(){
	sort(item,item+n);
	for(int i=0,cur,pre=-1;i<n;++i,pre=cur){
		cur=item[i].st/T;
		if(cur>pre){
			for(int j=item[i].cost;j<N;++j)
				L[i][j]=item[i].val;
		}
		else{
			for(int j=0;j<N;++j){
				L[i][j]=L[i-1][j];
				if(j>=item[i].cost)
					Max(L[i][j],L[i-1][j-item[i].cost]+item[i].val);
			}
		}
	}
	for(int i=n-1,cur,suf=INF;~i;--i,suf=cur){
		cur=item[i].st/T;
		if(cur<suf){
			for(int j=item[i].cost;j<N;++j)
				R[i][j]=item[i].val;
		}
		else{
			for(int j=0;j<N;++j){
				R[i][j]=R[i+1][j];
				if(j>=item[i].cost)
					Max(R[i][j],R[i+1][j-item[i].cost]+item[i].val);
			}
		}
	}
}
int solve(){
	int tar,lim,st=-1,en=-1,ans=0;
	rd(tar);rd(lim);
	for(int i=0,first=true;i<n;++i){
		if(item[i].st>tar-T&&first){
			first=false;
			st=i;
		}
		if(item[i].st<=tar)en=i;
		else break;
	}
	if(st==-1||en==-1||st>en)return 0;
	if(item[st].st/T==item[en].st/T){
		if(item[st].st/T==tar/T)return L[en][lim];
		return R[st][lim];
	}
	for(int i=0;i<=lim;++i)
		Max(ans,R[st][i]+L[en][lim-i]);
	return ans;
}
int main(){
	rd(n);rd(T);
	for(int i=0;i<n;++i)
		item[i].Rd();
	init();
	int m;
	rd(m);
	while(m--)printf("%d\n",solve());
	return 0;
}
/*
	
	Jul.02.16
	
	Tags:dp
	Submissions:3
	
	Time 202ms
	Memory 125400KB
	
*/
