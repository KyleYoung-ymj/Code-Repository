#include<cstdio>
#include<cstring>
typedef unsigned long long ull;
const int LEN=10,NODE=35;
int allc;
char str[LEN];
ull n;
struct Matrix{
	ull num[NODE][NODE];
	Matrix(){
		memset(num,0,sizeof(num));
	}
	void operator =(int tmp){
		for(int i=0;i<=allc;++i)
			for(int j=0;j<=allc;++j)
				num[i][j]=tmp*(i==j);
	}
	Matrix operator +(const Matrix &tmp)const{
		Matrix res;
		for(int i=0;i<=allc;++i)
			for(int j=0;j<=allc;++j)
				res.num[i][j]=num[i][j]+tmp.num[i][j];
		return res;
	}
	Matrix operator *(const Matrix &tmp)const{
		Matrix res;
		for(int i=0;i<=allc;++i)
			for(int j=0;j<=allc;++j)
				for(int k=0;k<=allc;++k)
					res.num[i][j]+=num[i][k]*tmp.num[k][j];
		return res;
	}
	Matrix operator ^(ull b)const{
		Matrix a=*this,res;
		res=1;
		while(b){
			if(b&1)res=res*a;
			a=a*a;
			b>>=1;
		}
		return res;
	}
};
struct ACautomaton{
	int trie[NODE][26],fail[NODE],que[NODE];
	bool en[NODE];
	Matrix mat,res;
	ACautomaton(){
		allc=0;
		memset(trie,0,sizeof(trie));
		memset(fail,0,sizeof(fail));
		memset(en,false,sizeof(en));
	}
	void init(){
		for(int i=0;i<=allc;++i){
			for(int j=0;j<26;++j)
				trie[i][j]=0;
			fail[i]=en[i]=0;
		}
		mat=0;
		allc=0;
	}
	void insert(){
		int len=strlen(str),cur=0;
		for(int i=0;i<len;++i){
			int nxt=str[i]-'a';
			if(!trie[cur][nxt])
				trie[cur][nxt]=++allc;
			cur=trie[cur][nxt];
		}
		en[cur]=true;
	}
	void construct(){
		int L=0,R=0;
		for(int i=0;i<26;++i)
			if(trie[0][i])
				que[R++]=trie[0][i];
		while(L<R){
			int cur=que[L++];
			if(en[fail[cur]])en[cur]=true;
			for(int i=0;i<26;++i){
				int nxt=trie[cur][i];
				if(nxt){
					que[R++]=nxt;
					fail[nxt]=trie[fail[cur]][i];
				}
				else trie[cur][i]=trie[fail[cur]][i];
			}
		}
		for(int i=0;i<=allc;++i){
			if(en[i])continue;
			for(int j=0;j<26;++j)
				if(!en[trie[i][j]])
					++mat.num[i][trie[i][j]];
		}
	}
	ull fast_pow_26(ull b){
		ull a=26,res=1;
		while(b){
			if(b&1)res*=a;
			a*=a;
			b>>=1;
		}
		return res;
	}
	ull sum_pow_26(ull b){
		if(b==1)return 26ull;
		ull sum=sum_pow_26(b>>1),num=fast_pow_26(b+1>>1);
		return sum+sum*num+(b&1)*num;
	}
	Matrix sum_pow_mat(ull b){
		if(b==1)return mat;
		Matrix sum=sum_pow_mat(b>>1),num=mat^(b+1>>1);
		if(b&1)return sum+sum*num+num;
		return sum+sum*num;
	}
	void solve(){
		ull tot=sum_pow_26(n);
		res=sum_pow_mat(n);
		for(int i=0;i<=allc;++i)
			tot-=res.num[0][i];
		printf("%I64u\n",tot);
	}
}ac;
int main(){
	int m;
	while(~scanf("%d %I64u",&m,&n)){
		while(m--){
			scanf("%s",str);
			ac.insert();
		}
		ac.construct();
		ac.solve();
		ac.init();
	}
	return 0;
}
/*
	
	Dec.10.15
	
	Origin:HDU 2243
	Tags:String,ACautomaton,dp,Mathematics,Matrix
	Submit:2
	
	Memory 2664KB
	Time 62ms
	Code Length 2572B
	
*/
