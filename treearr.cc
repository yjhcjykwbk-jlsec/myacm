//1011 1000 -> [ 1011 0001 ~ 1011 1000 ] = [1011 0001~ 1011 0100] + [1011 0101~ 1011 1000]
//                                                                 =[1011 0101~ 1011 0110] + [1011 0111 ~ ]+ [1011 1000]
#include "test.h"
int N;
int A[MAXN],C[MAXN];//C[]存储树状数组
int getLast0s(int n){
  int m=~n+1;
  return n&m;
}
//计算C[n]
int getValue(int n){                                                              
  cout<<"n:"<<n<<endl;
  int s=getLast0s(n),t=n-s;
  int r=0;
  int d=s>>1,e=t;
  while(d>0){
    e+=d;
    cout<<"d:"<<d<<"\te:"<<e<<endl;
    r+=C[e];
    d>>=1;
  } 
  r+=A[n];
  return r;
}
int request(int n){
  int s,r=0;
  while(n>0){
  r+=C[n];
  s=getLast0s(n);
  n-=s;
  }
  return r;
}
    
int main(){
  int m;
  cin>>N>>m;
  rep(i,1,N) {
    cin>>A[i];
    C[i]=getValue(i);
  }
  rep(i,1,m){
    int a,b;
    cin>>a>>b;
    cout<<request(b)-request(a)+A[a]<<endl;
  }
  return 0;
}
