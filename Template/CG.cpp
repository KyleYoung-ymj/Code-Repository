#include <cstdio>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb push_back
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
#define lson (k<<1)
#define rson (k<<1|1)
#define Debug(x) cout<<endl<<#x<<"="<<x<<"!!!!!"<<endl<<endl
#define rep(i,s,t) for(int i=s,_t=t;i<t;++i)
#define per(i,s,t) for(int i=t-1,_s=s;i>=_s;--i)
#pragma comment(linker, "/STaCK:1024000000,1024000000")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
typedef complex<db> com;
const int mod=(int)1e9+7,inf=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const ll INF=1ll<<60;
const double pi=acos(-1.0),eps=1e-6;
template<class T>void rd(T &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_print(T x){
	if(!x)return;
	rec_print(x/10);
	putchar(x%10^48);
}
template<class T>void print(T x){
	if(!x)putchar('0');
	else rec_print(x);
}
template<class T>inline void Max(T &a,T b){
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b){
	if(b<a)a=b;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}
int dcmp(db x){
	if(fabs(x)<eps)return 0;
	return x<0?-1:1;
}
struct Point{
	db x,y;
	Point(db x=0,db y=0):x(x),y(y){}
	bool operator <(Point &a)const{
		if(x!=a.x)return x<a.x;
		return y<a.y;
	}
	inline bool operator ==(Point a){
		return !dcmp(x-a.x)&&!dcmp(y-a.y);
	}
};
typedef Point Vec;
inline Vec operator +(const Vec &a,const Vec &b){
	return Vec(a.x+b.x,a.y+b.y);
}
inline Vec operator -(const Vec &a,const Vec &b){
	return Vec(a.x-b.x,a.y-b.y);
}
inline Vec operator *(const Vec &a,db p){
	return Vec(a.x*p,a.y*p);
}
inline Vec operator /(const Vec &a,db p){
	return Vec(a.x/p,a.y/p);
}
inline void operator /=(Vec a,db p){
	a=a/p;
}
inline db Dot(const Vec &a,const Vec &b){
	return a.x*b.x+a.y*b.y;
}
inline db Length(const Vec &a){
	return sqrt(Dot(a,a));
}
inline db angle(const Vec &a,const Vec &b){
	return acos(Dot(a,b)/Length(a)/Length(b));
}
inline db Cross(const Vec &a,const Vec &b){
	return a.x*b.y-a.y*b.x;
}
inline db area2(const Point &a,const Point &b,const Point &C){
	return Cross(b-a,C-a);
}
Vec Rotate(const Vec &a,db rad){
	db s=sin(rad),c=cos(rad);
	return Vec(a.x*c-a.y*s,a.x*s+a.y*c);
}
Vec Normal(const Vec &a){
	db L=Length(a);
	return (-a.y/L,a.x/L);
}
struct Point3{
	db x,y,z;
	Point3(db x=0,db y=0,db z=0):x(x),y(y),z(z){}
};
typedef Point3 Vec3;
inline Vec3 operator +(Vec3 a,Vec3 b){
	return Vec3(a.x+b.x,a.y+b.y,a.z+b.z);
}
inline Vec3 operator -(Vec3 a,Vec3 b){
	return Vec3(a.x-b.x,a.y-b.y,a.z-b.z);
}
inline Vec3 operator *(Vec3 a,db p){
	return Vec3(a.x*p,a.y*p,a.z*p);
}
inline Vec3 operator /(Vec3 a,db p){
	return Vec3(a.x/p,a.y/p,a.z/p);
}
inline void operator /=(Vec3 a,db p){
	a=a/p;
}
inline db Dot3(Vec3 a,Vec3 b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}
inline db Length3(Vec3 a){
	return sqrt(Dot3(a,a));
}
inline db Angle3(Vec3 a,Vec3 b){
	return acos(Dot3(a,b)/Length3(a)/Length3(b));
}
Vec3 Cross(Vec3 a,Vec3 b){
	return Vec3(a.y*b.z-b.y*a.z,
				a.z*b.x-b.z*a.x,
				a.x*b.y-b.x*a.y);
}
struct Plane{
	Point3 p0;
	Vec3 n;
	Plane(Point3 pp0,Vec3 nn){
		p0=pp0;
		n=nn/Length3(nn);
	}
	Plane(Point3 a,Point3 b,Point3 c){
		n=Cross(b-a,c-a);
		n/=Length3(n);
		p0=a;
	}
};
int main(){

}
