#include<cstdio>
#include<cstring>
const int N=305,INF=0x7fffffff;
int n,numx[N],numy[N],val[N][N],adj[N],slack[N];
bool usedx[N],usedy[N];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
bool Hungary(int cur){
	usedx[cur]=true;
	for(int i=0;i<n;++i){
		if(usedy[i])continue;
		int delta=numx[cur]+numy[i]-val[cur][i];
		if(!delta){
			usedy[i]=true;
			if(adj[i]==-1||Hungary(adj[i])){
				adj[i]=cur;
				return true;
			}
		}
		else Min(slack[i],delta);
	}
	return false;
}
int KM(){
	memset(numy,0,sizeof(numy));
	memset(adj,-1,sizeof(adj));
	for(int i=0;i<n;++i){
		numx[i]=0;
		for(int j=0;j<n;++j)
			Max(numx[i],val[i][j]);
	}
	for(int i=0;i<n;++i){
		memset(slack,127,sizeof(slack));
		while(true){
			memset(usedx,false,sizeof(usedx));
			memset(usedy,false,sizeof(usedy));
			if(Hungary(i))break;
			int delta=INF;
			for(int j=0;j<n;++j){
				if(usedy[j])continue;
				Min(delta,slack[j]);
			}
			for(int j=0;j<n;++j){
				if(usedx[j])numx[j]-=delta;
				if(usedy[j])numy[j]+=delta;
				else slack[j]-=delta;
			}
		}
	}
	int ans=0;
	for(int i=0;i<n;++i)
		ans+=val[adj[i]][i];
	return ans;
}
int main(){
	while(~scanf("%d",&n)){
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				scanf("%d",&val[i][j]);
		printf("%d\n",KM());
	}
	return 0;
}
/*
	
	Mar.02.16
	
	Tags:Hungary,KM,classic
	Submissions:4
	
	Exe.Time 795MS
	Exe.Memory 1776K
	Code Len. 1366B
	
*/
