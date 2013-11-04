#include <iostream>
#include <vector>
using namespace std;
#define MAXN 1010
int Dis[MAXN];
bool Vis[MAXN];//visited ?
int Edges[MAXN][MAXN];
#define FAR 0xFFFFFF
#define rep(i,n) for(int i=1;i<=n;i++)
int N;
int getMin(){
  int min=FAR,index=-1;
  for(int i=1;i<=N;i++){
   if(!Vis[i]&&Dis[i]<min) 
      index=i,min=Dis[i];
  }
  return index;
} 
void init(){
  int T;
  cin>>T>>N;
  rep(i,N)rep(j,N) Edges[i][j]=FAR;
  for(int i=1;i<=T;i++){
    int a,b,l;
    cin>>a>>b>>l;
    Edges[b][a]=Edges[a][b]=Edges[a][b]<l?Edges[a][b]:l;
  }
  rep(i,N)Dis[i]=FAR,Vis[i]=false;
  Dis[1]=0;
}
int main(){
  init();
  int t=1,s;
  int n=N;
  while(n-->0){
    Vis[t]=true;
    if(t==N) break;
    rep(i,N)
      if(Edges[t][i]<FAR&&Dis[i]>(s=Dis[t]+Edges[t][i]))
        Dis[i]=s;
    t=getMin();
  }
  cout<<Dis[N]<<endl;
  return 0;
}


