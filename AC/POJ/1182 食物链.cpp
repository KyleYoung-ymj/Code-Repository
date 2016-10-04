#include<cstdio>
const int N=5e4+5;
int par[N*3];
int get_root(int x){
	return par[x]==x?x:par[x]=get_root(par[x]);
}
inline bool same(int a,int b){
	return get_root(a)==get_root(b);
}
inline void unite(int a,int b){
	par[get_root(a)]=get_root(b);
}
int main(){
	int n,m,ope,x,y;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		par[i]=i;
		par[i+n]=i+n;
		par[i+(n<<1)]=i+(n<<1);
	}
	int ans=0;
	while(m--){
		scanf("%d%d%d",&ope,&x,&y);
		if(x<1||x>n||y<1||y>n){
			++ans;
			continue;
		}
		if(ope==1){
			if(same(x,y+n)||same(x,y+(n<<1)))++ans;
			else{
				unite(x,y);
				unite(x+n,y+n);
				unite(x+(n<<1),y+(n<<1));
			}
		}
		else{
			if(same(x,y)||same(x,y+(n<<1)))++ans;
			else{
				unite(x,y+n);
				unite(x+n,y+(n<<1));
				unite(x+(n<<1),y);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*
	
	Jan.04.16
	
	Tags:Union Find,classic
	Submissions:2
	WA:while(~scanf(...
	
	Memory 748K
	Time 266MS
	Code Length 801B
	
*/
