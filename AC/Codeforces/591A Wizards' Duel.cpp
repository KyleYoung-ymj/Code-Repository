#include<cstdio>
int main(){
    int l,p,q;
    scanf("%d %d %d",&l,&p,&q);
    double t=3.0*l/(p+q),t1=1.0*l/(p+q);
    double len=t*p;
    double ans=len-t1*p*2;
    printf("%lf\n",ans);
    return 0;
}
/*
	
	Oct.25.15
	Submit:1
	
	Time 15ms
	Memory 0KB
	
*/
