char str[N];
struct Suffix_Array{
	int n,sa[N],rk[N],height[N],cnt[N];
	void cons(){
		int m='z'+1,*a=rk,*b=height;
		str[(n=strlen(str))++]='#';
		memset(cnt,0,m<<2);
		rep(i,0,n)++cnt[a[i]=str[i]];
		rep(i,1,m)cnt[i]+=cnt[i-1];
		per(i,0,n)sa[--cnt[a[i]]]=i;
		for(int j=1,p=0;p<n;j<<=1,m=p){
			p=0;
			rep(i,n-j,n)b[p++]=i;
			rep(i,0,n)if(sa[i]>=j)b[p++]=sa[i]-j;
			memset(cnt,0,m<<2);
			rep(i,0,n)++cnt[a[b[i]]];
			rep(i,1,m)cnt[i]+=cnt[i-1];
			per(i,0,n)sa[--cnt[a[b[i]]]]=b[i];
			swap(a,b);
			p=1;
			a[sa[0]]=0;
			rep(i,1,n)a[sa[i]]=b[sa[i-1]]==b[sa[i]]&&b[sa[i-1]+j]==b[sa[i]+j]?p-1:p++;
		}
		--n;
		if(a!=rk)rep(i,1,n+1)rk[sa[i]]=i;
		for(int i=0,h=0;i<n;height[rk[i++]]=h){
			if(h)--h;
			for(int j=sa[rk[i]-1];str[i+h]==str[j+h];++h);
		}
	}
}SA;
