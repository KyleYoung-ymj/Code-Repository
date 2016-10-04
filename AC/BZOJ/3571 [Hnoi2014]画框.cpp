#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=75,INF=0x7fffffff,NEG_INF=0x80000000;
int n,ans,Lx[N],Ly[N],adj[N],slack[N],
	A[N][N],B[N][N],val[N][N];
bool usedx[N],usedy[N];
struct Point{
	int x,y;
	Point(int x=0,int y=0):x(x),y(y){}
	inline int mul(){
		return x*y;
	}
	inline bool operator ==(const Point &tmp){
		return x==tmp.x&&y==tmp.y;
	}
};
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
bool Hungary(int u){
	usedx[u]=true;
	for(int v=0;v<n;++v){
		if(usedy[v])continue;
		int delta=Lx[u]+Ly[v]-val[u][v];
		if(!delta){
			usedy[v]=true;
			if(adj[v]==-1||Hungary(adj[v])){
				adj[v]=u;
				return true;
			}
		}
		else Min(slack[v],delta);
	}
	return false;
}
void KM(){
	for(int i=0;i<n;++i){
		adj[i]=-1;
		Ly[i]=0;
		Lx[i]=NEG_INF;
		for(int j=0;j<n;++j)
			Max(Lx[i],val[i][j]);
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j)
			slack[j]=INF;
		while(true){
			for(int j=0;j<n;++j)
				usedx[j]=usedy[j]=false;
			if(Hungary(i))break;
			int delta=INF;
			for(int j=0;j<n;++j){
				if(usedy[j])continue;
				Min(delta,slack[j]);
			}
			for(int j=0;j<n;++j){
				if(usedx[j])Lx[j]-=delta;
				if(usedy[j])Ly[j]+=delta;
				else slack[j]-=delta;
			}
		}
	}
}
void rec(Point L,Point R){
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			val[i][j]=A[i][j]*(R.y-L.y)+B[i][j]*(L.x-R.x);
	/*
		Maximize vector(L,mid) cross vector(L,R)
			-> Maximize mid.x*(R.y-L.y)+mid.y*(L.x-R.x)
	*/
	KM();
	Point mid;
	for(int i=0;i<n;++i){
		mid.x+=A[adj[i]][i];
		mid.y+=B[adj[i]][i];
	}
	if(mid==L||mid==R)return;
	Min(ans,mid.mul());
	rec(L,mid);
	rec(mid,R);
}
void solve(){
	Point L,R;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			val[i][j]=-A[i][j];
	KM();
	for(int i=0;i<n;++i){
		L.x+=A[adj[i]][i];
		L.y+=B[adj[i]][i];
	}
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			val[i][j]=-B[i][j];
	KM();
	for(int i=0;i<n;++i){
		R.x+=A[adj[i]][i];
		R.y+=B[adj[i]][i];
	}
	ans=min(L.mul(),R.mul());
	rec(L,R);
	printf("%d\n",ans);
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--&&~scanf("%d",&n)){
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				scanf("%d",&A[i][j]);
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				scanf("%d",&B[i][j]);
		solve();
	}
	return 0;
}
/*
	
	Mar.03.16
	
	Tags:KM,Mathematics
	Submissions:1
	
	Memory 872kb
	Time 1524ms
	Code Length 2536B
	
*/
