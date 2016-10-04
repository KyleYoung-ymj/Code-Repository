#include<cstdio>
#include<cstring>
#include<algorithm>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
const int M=1e3+5,INF=1e9;
int pre[M<<1][M<<1],rx[100],ry[100];
void init(){
	rx['N']=-1;ry['N']=0;
	rx['S']=1;ry['S']=0;
	rx['W']=0;ry['W']=-1;
	rx['E']=0;ry['E']=1;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int main(){
	freopen("mowing.in","r",stdin);
	freopen("mowing.out","w",stdout);
	int n,ans=INF;
	scanf("%d",&n);
	init();
	memset(pre,-1,sizeof(pre));
	int cur_x=M,cur_y=M,step,cnt=0;
	char str[5];
	pre[cur_x][cur_y]=0;
	while(n--){
		scanf("%s%d",str,&step);
		while(step--){
			++cnt;
			cur_x+=rx[str[0]];
			cur_y+=ry[str[0]];
			if(~pre[cur_x][cur_y]){
				Min(ans,cnt-pre[cur_x][cur_y]);
			}
			pre[cur_x][cur_y]=cnt;
		}
	}
	if(ans==INF)ans=-1;
	printf("%d\n",ans);
	return 0;
}
