#include<cstdio>
#include<cstring>
const int N=15,NODE=105,P=1e5;
int n,allc,id_DNA[128];
char str[N];
typedef unsigned long long ull;
void pre_pro(){
	id_DNA['A']=0;
	id_DNA['T']=1;
	id_DNA['C']=2;
	id_DNA['G']=3;
}
struct Matrix{
	ull num[NODE][NODE];
	Matrix(){
		memset(num,0,sizeof(num));
	}
	void init(){
		for(int i=0;i<=allc;++i)
			for(int j=0;j<=allc;++j)
				num[i][j]=0;
	}
	void operator =(const int &tmp){
		init();
		for(int i=0;i<=allc;++i)
			num[i][i]=1;
	}
	Matrix operator *(const Matrix &tmp)const{
		Matrix res;
		for(int i=0;i<=allc;++i)
			for(int j=0;j<=allc;++j){
				for(int k=0;k<=allc;++k)
					res.num[i][j]+=num[i][k]*tmp.num[k][j];
				res.num[i][j]%=P;
			}
		return res;
	}
};
struct ACautomaton{
	int trie[NODE][4],fail[NODE],que[NODE];
	bool en[NODE];
	Matrix mat,res;
	ACautomaton(){
		allc=0;
		memset(trie,0,sizeof(trie));
		memset(fail,0,sizeof(fail));
		memset(en,false,sizeof(en));
	}
	void init(){
		mat.init();
		for(int i=0;i<=allc;++i){
			for(int j=0;j<4;++j)
				trie[i][j]=0;
			fail[i]=en[i]=0;
		}
		allc=0;
	}
	void insert(){
		int len=strlen(str),cur=0;
		for(int i=0;i<len;++i){
			int nxt=id_DNA[str[i]];
			if(!trie[cur][nxt])
				trie[cur][nxt]=++allc;
			cur=trie[cur][nxt];
		}
		en[cur]=true;
	}
	void construct(){
		int L=0,R=0;
		for(int i=0;i<4;++i)
			if(trie[0][i])
				que[R++]=trie[0][i];
		while(L<R){
			int cur=que[L++];
			if(en[fail[cur]])en[cur]=true;
			for(int i=0;i<4;++i){
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
			for(int j=0;j<4;++j)
				if(!en[trie[i][j]])
					++mat.num[i][trie[i][j]];
		}
	}
	void solve(){
		res=1;
		while(n){
			if(n&1)res=res*mat;
			mat=mat*mat;
			n>>=1;
		}
		ull ans=0;
		for(int i=0;i<=allc;++i)
			ans+=res.num[0][i];
		printf("%d\n",ans%P);
		init();
	}
}ac;
int main(){
	pre_pro();
	int m;
	while(~scanf("%d%d",&m,&n)){
		while(m--){
			scanf("%s",str);
			ac.insert();
		}
		ac.construct();
		ac.solve();
	}
	return 0;
}
/*
	
	Feb.10.16
	
	Tags:ACautomaton,matrix
	Submissions:1
	
	Memory 524K
	Time 125MS
	Code Length 2093B
	
*/
