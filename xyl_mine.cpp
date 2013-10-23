//poj 1469
#include <iostream>
#include <string.h>
#include <set>
using namespace std;
#define MAXN 400
int S=0,T,L,R;
set<int> Edges[MAXN];
bool Vis[MAXN];
void update(int s,int t){
  //该边不能够再走
  Edges[s].erase(t);
  if(t!=T)
    //将反向边加进来
    Edges[t].insert(s);
}
bool dfs(int s){
  if(s==T)
    return true;
  Vis[s]=true;//标记在访问中
  for(set<int>::iterator it=Edges[s].begin();it!=Edges[s].end();it++){
    int t=*it;
    if(!Vis[t]) 
      if(dfs(t)) {
        update(s,t);
        return true;
      }
  }
  //@error Vis[s]=false;//准备回溯
  return false;
} 
//写这种用到容器的程序
//调试非常痛苦，不如写个print
void print(){
  for(int i=0;i<=L;i++){
    cout<<i<<":";
    for(set<int>::iterator it=Edges[i].begin();it!=Edges[i].end();it++)
      cout<<""<<*it<<", ";cout<<endl;
  }
}

void findPath(){
  int num=0;
  for(int i=1;i<=L;i++){
    memset(Vis,0,sizeof(Vis));//@error: sizeof(int)*MAXN is wrong
    if(!dfs(i)) break;
    num++;
  }
  //print();
  if(num==L) cout<<"YES"<<endl;
  else cout<<"NO"<<endl;
}

void init(){
  int n;cin>>L>>R;//(1~L为左边，L+1~L+R为右边）
  T=L+R+1;
  int a,b;
  for(int i=1;i<=T;i++){
    Edges[i].clear();//clear! not empty or so
  }
//  for(int i=1;i<=L;i++) 
//    Edges[S].insert(i);
  for(int i=1;i<=R;i++) 
    Edges[L+i].insert(T);
  for(int i=1;i<=L;i++){
    cin>>n; 
    while(n-->0){
      cin>>a;
      Edges[i].insert(L+a);//people a choose course L+i
    }
  }
}
int main(){
  int cases;cin>>cases;
  while(cases-->0){
    init();
    findPath();
  }
  return 0;
}
