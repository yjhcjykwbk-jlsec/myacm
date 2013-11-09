#include "../test.h"
#define pb push_back
#define FAR 0Xffffff
int N,M;
int cap[MAXN][MAXN];
int price[MAXN][MAXN];
int D[MAXN];
int Pre[MAXN];
bool Flag[MAXN];
int S,T;

//find the least price path
int spfa(){
  queue<int> que;
  std::fill_n(D,MAXN,FAR);
  memset(Flag,0,sizeof(Flag)); 
  D[S]=0;Pre[S]=-1;
  que.push(S);Flag[S]=true;
  while(!que.empty()){
    int u=que.front();que.pop();
    Flag[u]=false;
    rep(v,1,N){
      if(cap[u][v]>0)//u,v
      if(D[u]+price[u][v]<D[v]){
        D[v]=D[u]+price[u][v];
        Pre[v]=u;
        if(!Flag[v]) {que.push(v);Flag[v]=true;}
      }
    }
  }
  return D[T];
}

int extend(){
  int cost=0;
  while(true){
    int s=spfa();
    if(s==FAR) break;
    int a=Pre[T],b=T,min=FAR;
    cout<<b;
    while(a!=-1){
      cout<<"<-"<<a;
      if(min>cap[a][b]) min=cap[a][b];
      b=a,a=Pre[a];
    }
    cout<<endl;
    cost+=min*s;
    cout<<min<<":"<<s<<endl;
    a=Pre[T],b=T;
    while(a!=-1){
      cap[a][b]-=min;
      cap[b][a]+=min;
      b=a,a=Pre[a];
    }
  }
  return cost;
}
void init(){
  cin>>N>>M;
  memset(cap,0,sizeof(cap));
  memset(price,0,sizeof(price));
  rep(i,1,M){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    cap[a][b]=c,cap[b][a]=0;
    price[a][b]=d,price[b][a]=-d;
  }
  S=0,T=N;
}
int main(){
  init();
  cout<<extend()<<endl;
  return 0;
}
      
