#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;
ll n;
map<ll,bool>SG;
map<ll,bool>vis;
bool calc_SG(ll x){
	if(x>=n)return 0;
	if(vis[x])return SG[x];
	vis[x]=true;
	for(int i=2;i<=9;++i){
		if(!calc_SG(x*i))return SG[x]=1;
	}
	return SG[x]=0;
}
int main(){
	while(~scanf("%I64d",&n)){
		SG.clear();
		vis.clear();
		puts(calc_SG(1)?"Stan wins.":"Ollie wins.");
	}
	return 0;
}
/*
	
	May.19.16
	
	Tags:Game Theory
	Submissions:1
	
	Exe.Time 15MS
	Exe.Memory 1856K
	Code Len. 447B
	
*/
