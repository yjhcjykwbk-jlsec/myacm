#include <iostream>
#include <vector>
using namespace std;
#define MAXN 1010
int Dis[MAXN];
bool Vis[MAXN];//visited ?
vector<pair<int,int> > Edges[MAXN];
#define FAR 0xFFFFFF
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
  for(int i=1;i<=T;i++){
    int a,b,l;
    cin>>a>>b>>l;
    for(int i=0;i<Edges[a].size();i++){
      pair<int,int> pair=Edges[a][i],pair_1;
      if(pair.first==b){
        if(pair.second>l)
        {
          Edges[a][i].second=l;
          for(int j=0;j<Edges[b].size();j++){
            pair_1=Edges[b][j];
            if(pair_1.first==a) Edges[b][j].second=l;
          }
        }
        goto read_next;
      }
    }
    Edges[a].push_back(pair<int,int>(b,l));
    Edges[b].push_back(pair<int,int>(a,l));
read_next:;
  }
  for(int i=1;i<=N;i++)
    Dis[i]=FAR,Vis[i]=false;
  Dis[1]=0;
}
int main(){
  init();
  int t=1,s;
  int n=N;
  while(n-->0){
    Vis[t]=true;
    if(t==N) break;
    for(int i=0;i<Edges[t].size();i++){
      pair<int,int> pair=Edges[t][i];
      int j=pair.first,k=pair.second; 
      if(Dis[j]>(s=Dis[t]+k))
        Dis[j]=s;
    }
    t=getMin();
  }
  cout<<Dis[N]<<endl;
  return 0;
}
