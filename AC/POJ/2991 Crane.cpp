#include<cstdio>
#include<cmath>
const int N=1e4+5;
const double Pi=acos(-1.0);
int len[N];
double pre_ang[N];
struct Segment_Tree{
	struct Node{
		int L,R;
		double x,y,ang;
	}tree[N<<2];
	void construct(int L,int R,int k){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].x=tree[k].ang=0;
		if(L==R){
			tree[k].y=len[L];
			return;
		}
		int mid=L+R>>1;
		construct(L,mid,k<<1);
		construct(mid+1,R,k<<1|1);
		tree[k].y=tree[k<<1].y+tree[k<<1|1].y;
	}
	void update(int k,int tar,double ang){
		if(tar<tree[k].L||tar>=tree[k].R)return;//TLE:did not return properly
		int mid=tree[k].L+tree[k].R>>1;
		update(k<<1,tar,ang);
		update(k<<1|1,tar,ang);
		if(tar<=mid)tree[k].ang+=ang;
		double s=sin(tree[k].ang),c=cos(tree[k].ang);
		tree[k].x=tree[k<<1].x+tree[k<<1|1].x*c-tree[k<<1|1].y*s;
		tree[k].y=tree[k<<1].y+tree[k<<1|1].x*s+tree[k<<1|1].y*c;
	}
	inline void output(){
		printf("%.2f %.2f\n",tree[1].x,tree[1].y);
	}
}T;
int main(){
	int n,m,tar,tmp;
	bool first=true;
	while(~scanf("%d%d",&n,&m)){
		if(first)first=false;
		else putchar('\n');
		for(int i=1;i<=n;++i){
			scanf("%d",&len[i]);
			pre_ang[i]=Pi;
		}
		T.construct(1,n,1);
		while(m--){
			scanf("%d%d",&tar,&tmp);
			double ang=tmp*Pi/180;
			T.update(1,tar,ang-pre_ang[tar]);
			pre_ang[tar]=ang;
			T.output();
		}
	}
	return 0;
}
/*
	
	Jan.09.16
	
	Tags:Geometry,Data Structure,Segment Tree
	Submissions:9
	WA:using float instead of double
	
	Memory 1344K
	Time 610MS
	Code Length 1268B
	
*/
