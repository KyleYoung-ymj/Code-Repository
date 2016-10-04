#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=2e4+5;
typedef unsigned long long ull;
int n;
ull bit0[N]={0},bit1[N]={0};
struct Cow{
	int pos,vol;
	inline void rd(){
		scanf("%d%d",&vol,&pos);
	}
	inline bool operator <(const Cow &tmp)const{
		return vol<tmp.vol;
	}
}cow[N];
void add(ull *b,int k,int x){
	while(k<N){
		b[k]+=x;
		k+=k&-k;
	}
}
ull sum(ull *b,int k){
	ull res=0;
	while(k){
		res+=b[k];
		k&=k-1;
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		cow[i].rd();
	sort(cow,cow+n);
	ull tot=0,ans=0;
	for(int i=0;i<n;++i){
		int vol=cow[i].vol,pos=cow[i].pos;
		ull pre=sum(bit1,pos),dist_pre=sum(bit0,pos);
		ans+=vol*(pos*pre-dist_pre);
		ans+=vol*(sum(bit0,N-1)-dist_pre-pos*(i-pre));
		add(bit0,pos,pos);
		add(bit1,pos,1);
	}
	printf("%I64u\n",ans);
	return 0;
}
/*
	
	Dec.14.15
	
	Tags:Data Structure,BIT,Sort
	Submissions:1
	
	Memory 1160K
	Time 63MS
	Code Length 845B
	
*/
