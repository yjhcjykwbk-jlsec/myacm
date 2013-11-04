#include <iostream>
#include <assert.h>
using namespace std;
#define MAXN 0xFFFFFF

int Min;
int tx;
float ty;
float k=ty/tx;
//搜索剪枝
void search(int a,float b,int n,bool tag){
  cout<<a<<":"<<b<<endl;
  if(a>tx||(tx-a)+n>Min) {cout<<"no"<<endl;return; }
  if((b/a)>=(ty/tx)){
    if((int)((b/a)*tx)==ty){
      int m=(tx-a)+n;
      Min=Min>m?m:Min;
    }
    return;
  }
  //+?
  float t=(ty/tx)*a;
  float s=t-b;
  assert(s>0);
  if(tag){
    for(int i=(int)(s+1);i>=(int)(s-1)&&i>0;i--)//优先加b,然后乘
      search(a,b+i,n+i,false);
  }
  search(a+1,b+b/a,n+1,true);
}
int main(){
  int a=1;float b=1;int n=0;
  while(cin>>tx>>ty){
  Min=MAXN;
  search(a,b,n,true);
  cout<<Min<<endl;
  }
  return 0;
}

