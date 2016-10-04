#include<cstdio>
const int NODE=155e4+5;
int allc=0,pre[NODE][2]={0};
bool bin[31];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int find_mx(){
	int res=0,cur=0;
	for(int i=0;i<31;++i)
		if(pre[cur][bin[i]^1]){
			cur=pre[cur][bin[i]^1];
			res|=1<<30-i;
		}
		else cur=pre[cur][bin[i]];
	return res;
}
int find_mi(){
	int res=0,cur=0;
	for(int i=0;i<31;++i)
		if(pre[cur][bin[i]])
			cur=pre[cur][bin[i]];
		else{
			cur=pre[cur][bin[i]^1];
			res|=1<<30-i;
		}
	return res;
}
int main(){
	int cas;
	scanf("%d",&cas);
	for(int u=1;u<=cas;++u){
		int n,num;
		scanf("%d %d",&n,&num);
		int mx=num,mi=num,sum=num,cur=0;
		for(int i=30;i>=0;--i){
			bool tmp=(bool)(sum&1<<i);
			if(!pre[cur][tmp])
				pre[cur][tmp]=++allc;
			cur=pre[cur][tmp];
		}
		for(int i=1;i<n;++i){
			scanf("%d",&num);
			sum^=num;
			int cur=0;
			for(int j=30;j>=0;--j)
				bin[30-j]=(bool)(sum&1<<j);
			Max(mx,find_mx());
			Max(mx,num);
			Max(mx,sum);
			Min(mi,find_mi());
			Min(mi,num);
			Min(mi,sum);
			for(int j=30;j>=0;--j){
				if(!pre[cur][bin[30-j]])
					pre[cur][bin[30-j]]=++allc;
				cur=pre[cur][bin[30-j]];
			}
		}
		printf("Case %d: %d %d\n",u,mx,mi);
		for(int i=0;i<=allc;++i)
			pre[i][0]=pre[i][1]=0;
		allc=0;
	}
	return 0;
}
/*
	
	Nov.22.15
	Submit:5
	
	Memory 13196KB
	Time 368ms
	Code Length 1277B
	
*/
