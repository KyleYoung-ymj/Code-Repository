#include<cstdio>
#include<cstring>
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
const int N=1e4+5,M=2e6+5,Q=1e5+5;
char dict[N][25],tmp[25];
int allc=0,pre[M][26]={0},ans[M]={0},id[Q];
set<int>used;
int main(){
	int n,m;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%s",dict[i]);
	scanf("%d",&m);
	for(int i=0;i<m;++i){
		scanf("%s",tmp);
		int len=strlen(tmp),cur=0;
		for(int j=0;j<len;++j){
			if(!pre[cur][tmp[j]-'a'])
				pre[cur][tmp[j]-'a']=++allc;
			cur=pre[cur][tmp[j]-'a'];
		}
		id[i]=cur;
	}
	for(int i=0;i<n;++i){
		int len=strlen(dict[i]);
		used.clear();
		for(int j=0;j<len;++j){
			int cur=0;
			for(int k=j;k<len;++k){
				cur=pre[cur][dict[i][k]-'a'];
				if(!cur)break;
				if(used.find(cur)==used.end()){
					++ans[cur];
					used.insert(cur);
				}
			}
		}
	}
	for(int i=0;i<m;++i)
		printf("%d\n",ans[id[i]]);
	return 0;
}
/*
	
	Nov.20.15
	Submit:5
	
	Memory 25196KB
	Time 187ms
	Code Length 880B
	
*/
