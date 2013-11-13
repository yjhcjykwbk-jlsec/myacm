#include "../test.h"
#define MAXN 1000000
#define MIN -1
int top[MAXN];
void init(){
  memset(top,MIN,sizeof(top));//top of [l,r] is -1 primarily
}
//a[i]=s
//node[index]<=>[l,r]
void update(int i,int s,int l,int r,int index){
  if(l==r){ top[index]=s; return; }
  int mid=(l+r)>>1;
  if(i<=mid) update(i,s,l,mid,index<<1);
  else update(i,s,mid+1,r,(index<<1)+1);
  top[index]=max(top[index<<1],top[(index<<1)+1]);
}
int query(int a,int b,int l,int r,int index){
  if(a<=l&&b>=r){ return top[index];}
  int mid=(l+r)>>1;
  int tmp=MIN;
  if(a<=mid){tmp=max(tmp,query(a,b,l,mid,index<<1));}
  if(b>mid){ tmp=max(tmp,query(a,b,mid+1,r,(index<<1)+1));}
  return tmp;
}
int main(){
  init();
  int N,a;cin>>N;
  rep(i,1,N){cin>>a;update(i,a,1,N,1);}//node[1] is the root, represent [1,N]
  int M;cin>>M;
  rep(i,1,M){int b;cin>>a>>b;cout<<query(a,b,1,N,1)<<endl;}
  return 0;
}
