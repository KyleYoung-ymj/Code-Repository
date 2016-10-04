#include<cstdio>
#include<cmath>
#include<ctime>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<cassert>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#define fi first
#define se second
#define lowbit(x) (x&-x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
const int N=25;
int n,m,tot,dp[N],tmp[N];
bool cat[N][N];
struct Matrix{
	int num[N][N];
	void operator =(bool x){
		for(int i=1;i<=tot;++i)
			for(int j=1;j<=tot;++j)
				num[i][j]=(i==j)*x;
	}
	Matrix operator *(const Matrix &tmp)const{
		Matrix res;
		for(int i=1;i<=tot;++i)
			for(int j=1;j<=tot;++j){
				res.num[i][j]=0;
				for(int k=1;k<=tot;++k)
					res.num[i][j]=(res.num[i][j]+1ll*num[i][k]*tmp.num[k][j])%mod;
			}
		return res;
	}
	inline void operator *=(const Matrix &tmp){
		*this=*this*tmp;
	}
	Matrix operator ^(int b)const{
		Matrix res,mat=*this;
		res=1;
		for(;b;b>>=1,mat*=mat)
			if(b&1)res*=mat;
		return res;
	}
}mat,Mat;
inline bool in(int x,int y){
	return x&&x<=n&&y&&y<=m;
}
inline int id(int x,int y){
	return (x-1)*m+y;
}
int main(){
	int K;
	rd(n);rd(m);rd(K);
	tot=n*m;
	int cur=1,
		ope,x,y,t;
	dp[id(1,1)]=1;
	mat=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			int cur_id=id(i,j);
			mat.num[cur_id][cur_id]=1;
			for(int dir=0;dir<4;++dir){
				int dx=i+rx[dir],dy=j+ry[dir];
				if(!in(dx,dy))continue;
				mat.num[cur_id][id(dx,dy)]=1;
			}
		}
	while(K--){
		rd(ope);rd(x);rd(y);rd(t);
		int cur_id=id(x,y);
		Mat=mat^t-cur;
		for(int i=1;i<=tot;++i){
			tmp[i]=0;
			for(int j=1;j<=tot;++j){
				tmp[i]=(tmp[i]+1ll*Mat.num[j][i]*dp[j])%mod;
			}
		}
		memcpy(dp,tmp,tot+1<<2);
		switch(ope){
			case 1:
				printf("%d\n",dp[id(x,y)]);
				break;
			case 2:
				mat.num[cur_id][cur_id]=0;
				for(int dir=0;dir<4;++dir){
					int dx=x+rx[dir],dy=y+ry[dir];
					if(!in(dx,dy))continue;
					mat.num[cur_id][id(dx,dy)]=mat.num[id(dx,dy)][cur_id]=0;
				}
				cat[x][y]=true;
				break;
			case 3:
				mat.num[cur_id][cur_id]=1;
				for(int dir=0;dir<4;++dir){
					int dx=x+rx[dir],dy=y+ry[dir];
					if(!in(dx,dy)||cat[dx][dy])continue;
					mat.num[cur_id][id(dx,dy)]=mat.num[id(dx,dy)][cur_id]=1;
				}
				cat[x][y]=false;
				break;
		}
		cur=t;
	}
	return 0;
}
/*
	
	Jul.11.16

	Tags:matrix,dp
	Submissions:2

	Time 1934ms
	Memory 0KB
*/
