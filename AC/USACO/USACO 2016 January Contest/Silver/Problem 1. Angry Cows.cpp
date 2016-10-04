#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5e4+5;
int n,m,pos[N];
bool judge(int R){
	for(int cur=0,left=m;cur<n;--left){
		if(!left)return false;
		int tar=pos[cur]+R;
		while(cur<n&&pos[cur]<=tar+R)++cur;
	}
	return true;
}
int main(){
	freopen("angry.in","r",stdin);
	freopen("angry.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
		scanf("%d",&pos[i]);
	sort(pos,pos+n);
	int L=0,R=(int)1e9,ans;
	while(L<=R){
		int mid=L+R>>1;
		if(judge(mid)){
			ans=mid;
			R=mid-1;
		}
		else L=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
