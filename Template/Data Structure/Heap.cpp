#include<cstdio>
#include<cstring>
const int N=20005;
struct heap{
	int num[N];
	heap(){
		memset(num,0,sizeof(num));
	}
	bool cmp(int a,int b){
		return a<b;
	}
	void up(int k){
		int par,key=num[k];
		while(par=k>>1){
			if(!cmp(key,num[par]))break;
			num[k]=num[par];
			k=par;
		}
		num[k]=key;
	}
	void down(int k){
		int son,key=num[k];
		while((son=k<<1)<=num[0]){
			if(son<num[0]&&cmp(num[son+1],num[son]))++son;
			if(!cmp(num[son],key))break;
			num[k]=num[son];
			k=son;
		}
		num[k]=key;
	}
	void push(int x){
		num[++num[0]]=x;
		up(num[0]);
	}
	int top(){
		return num[1];
	}
	void pop(){
		num[1]=num[num[0]--];
		down(1);
	}
	bool empty(){
		return !num[0];
	}
}hp;
int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		int tmp;
		scanf("%d",&tmp);
		hp.push(tmp);
	}
	while(!hp.empty()){
		printf("%d ",hp.top());
		hp.pop();
	}
	puts("");
	return 0;
}
