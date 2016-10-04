#include<cstdio>
#include<cassert>
#include<map>
#include<string>
#include<iostream>
#include<algorithm>
#define x first
#define y second
using namespace std;
typedef pair<int,int> Point;
const int N=205;
int n,mi[N];
Point point[N];
map<string,int>cnt;
inline int get_pre(int cur){
	return cur==1?n:cur-1;
}
inline int get_nxt(int cur){
	return cur==n?1:cur+1;
}
string calc_angle(int cur){
	int pre=get_pre(cur),
		nxt=get_nxt(cur);
	if(point[pre].y<point[cur].y&&point[cur].x>point[nxt].x)return "L";
	if(point[pre].x<point[cur].x&&point[cur].y<point[nxt].y)return "L";
	if(point[pre].y>point[cur].y&&point[cur].x<point[nxt].x)return "L";
	if(point[pre].x>point[cur].x&&point[cur].y>point[nxt].y)return "L";
	return "R";
}
string convert(int x){
	string res="";
	while(x){
		string tmp="1";
		tmp[0]=x%10+'0';
		res=tmp+res;
		x/=10;
	}
	return res;
}
int dist(int id){
	int nxt=get_nxt(id);
	return abs(point[nxt].x-point[id].x)+abs(point[nxt].y-point[id].y);
}
void calc(int cur){
	string str=calc_angle(cur);
	++cnt[str];
	for(;cur^1;cur=get_nxt(cur),++cnt[str]){
		str+=convert(dist(cur));
		str+=calc_angle(get_nxt(cur));
	}
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int solve(int cur){
	string str=calc_angle(cur);
	if(cnt[str]==1)return mi[cur];
	for(int sum=0;;){
		str+=convert(dist(cur));
		sum+=dist(cur);
		cur=get_nxt(cur);
		str+=calc_angle(cur);
		if(cur==1||cnt[str]==1){
			return sum+mi[cur];
		}
	}
}
int main(){
	freopen("lightsout.in","r",stdin);
	freopen("lightsout.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&point[i].x,&point[i].y);
	}
	cnt.clear();
	for(int i=2;i<=n;++i){
		calc(i);
	}
	int sum=0;
	for(int i=1;i<=n;++i)
		sum+=dist(i);
	for(int i=2,cur_sum=0;i^1;i=get_nxt(i)){
		cur_sum+=dist(get_pre(i));
		mi[i]=min(cur_sum,sum-cur_sum);
	}
	mi[1]=0;
	int ans=0;
	for(int i=2;i<=n;++i){
		Max(ans,solve(i)-mi[i]);
	}
	printf("%d\n",ans);
	return 0;
}
