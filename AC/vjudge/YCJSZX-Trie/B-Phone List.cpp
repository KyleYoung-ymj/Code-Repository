#include<cstdio>
#include<cstring>
const int N=1e5+5;
int allc,pre[N][10];
bool en[N];
char str[15];
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		int n;
		bool flag=false;
		scanf("%d",&n);
		allc=0;
		memset(pre,0,sizeof(pre));
		memset(en,false,sizeof(en));
		while(n--){
			scanf("%s",str);
			if(flag)continue;
			int len=strlen(str),cur=0;
			for(int i=0;i<len-1;++i){
				if(!pre[cur][str[i]^48])
					pre[cur][str[i]^48]=++allc;
				cur=pre[cur][str[i]^48];
				if(en[cur]){
					flag=true;
					break;
				}
			}
			if(pre[cur][str[len-1]^48])flag=true;
			cur=pre[cur][str[len-1]^48]=++allc;
			en[cur]=true;
		}
		puts(flag?"NO":"YES");
	}
	return 0;
}
/*
	
	Nov.19.15
	Submit:3
	
	Memory 5416KB
	Time 140ms
	Code Length 675B
	
*/
