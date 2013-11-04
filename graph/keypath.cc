//有向图
//关键路径
//拓扑排序，求time[i] 即完成任务i的最短时间
#include <iostream>
#include <Queue>
#include <set>
using namespace std;
#define MAXN 100
#define SET  set<pair<int,int> >
#define rep(i,m,n) for(int i=m;i<=n;i++)

int N;
int Time[MAXN];
int degree[MAXN];
queue<int> Queue;
SET edges[MAXN];
int calc(){
  rep(i,1,N)
    if(degree[i]==0) Queue.push(i);
  while(!Queue.empty()){
    int u=Queue.front();Queue.pop();
    //for every next reachable point v
    for(SET::iterator it=edges[u].begin();it!=edges[u].end();it++){
      int v=(*it).first;
      degree[v]--;
      //update the time of v using u
      Time[v]=Time[v]<Time[u]+(*it).second?Time[u]+(*it).second:Time[v];
      //check if can put v into the queue
      if(degree[v]==0) Queue.push(v);
    }
  }
  int maxTime=0;
  for(int i=1;i<=N;i++) maxTime=maxTime<Time[i]?Time[i]:maxTime;
  return maxTime;
}
int main(){
  int m;cin>>N>>m;
  rep(i,1,N) Time[i]=0,degree[i]=0;
  while(m-->0){
    int a,b,l;cin>>a>>b>>l;
    cout<<a<<" "<<b<<" "<<l<<endl;
    edges[a].insert(pair<int,int>(b,l));
    degree[b]++;
  }
  int s=calc();
  rep(i,1,N) cout<<i<<":"<<Time[i]<<" ";cout<<endl;
  cout<<s<<endl;
  return 0;
}
