#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e6+5,INF=1e9;
int n,m,dat[N][2];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
bool judge(int len){
	int mi0=-INF,mx0=INF,mi1=-INF,mx1=INF;
	for(int i=0;i<m;++i){
		int L=dat[i][0],R=dat[i][1];
		if(R-L<=len)continue;
		Max(mi0,L+R-len);
		Min(mx0,L+R+len);
		Max(mi1,-L+R-len);
		Min(mx1,-L+R+len);
	}
	return mi0<=mx0&&mi1<=mx1;
}
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
int main(){
	while(~scanf("%d",&n)){
		rd(m);
		for(int i=0;i<m;++i){
			for(int j=0;j<2;++j)
				rd(dat[i][j]);
			if(dat[i][0]>dat[i][1])swap(dat[i][0],dat[i][1]);
		}
		int L=0,R=n,ans;
		while(L<=R){
			int mid=L+R>>1;
			if(judge(mid)){
				ans=mid;
				R=mid-1;
			}
			else L=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
	
	May.24.16
	
	Tags:binary search,Mathematics
	Submissions:3
	
	Exe.Time 2854MS
	Exe.Memory 5336K
	Code Len. 956B
	
*/
