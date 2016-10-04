#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int N=1e5+5;
priority_queue<int,vector<int>,greater<int> >pque;
typedef long long ll;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
void solve(){
	int n,num;
	rd(n);
	while(!pque.empty())pque.pop();
	ll ans=0;
	while(n--){
		rd(num);
		pque.push(num);
	}
	while(pque.size()>1){
		ll a=pque.top();
		pque.pop();
		ll b=pque.top();
		pque.pop();
		ll c=a+b;
		ans+=c;
		pque.push(c);
	}
	printf("%I64d\n",ans);
}
int main(){
	int cas;
	rd(cas);
	while(cas--)solve();
	return 0;
}
/*
	
	Jun.22.16
	
	Tags:Huffman,pque
	Submissions:1
	
	Memory(KB) 2380
	Time(ms) 639
	Length(Bytes) 636
	
*/
