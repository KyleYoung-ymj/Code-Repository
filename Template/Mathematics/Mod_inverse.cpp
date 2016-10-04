#include<cstdio>
void extgcd(int a,int b,int &x,int &y){
	if(b){
		extgcd(b,a%b,y,x);
		y-=a/b*x;
	}
	else{
		x=1;
		y=0;
	}
}
int mod_inverse(int a,int b){
	int x,y;
	extgcd(a,b,x,y);
	return (b+x%b)%b;
}
