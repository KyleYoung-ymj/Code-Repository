#include<cstdio>
#include<algorithm>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
const int N=105;
int pos[N];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int main(){
	freopen("angry.in","r",stdin);
	freopen("angry.out","w",stdout);
	int n,ans=1;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",&pos[i]);
	sort(pos,pos+n);
	for(int i=0;i<n;++i){
		int cnt=1;
		for(int d=1,L=i;;++d){
			int l=L;
			while(l&&pos[l-1]>=pos[L]-d){
				--l;
				++cnt;
			}
			if(l==L)break;
			L=l;
		}
		for(int d=1,R=i;;++d){
			int r=R;
			while(r<n-1&&pos[r+1]<=pos[R]+d){
				++r;
				++cnt;
			}
			if(r==R)break;
			R=r;
		}
		Max(ans,cnt);
	}
	printf("%d\n",ans);
	return 0;
}
