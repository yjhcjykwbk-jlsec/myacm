#include <iostream>
using namespace std;
int gcd(int x,int y){
  if(!x||!y)return x?y:x;
  //x>y
  int t;//t=x-y*k => y
  while(t=x%y){
    x=y,y=t;
  }
  return y;
}
int main(){
  cout<<gcd(11,11111)<<endl<<gcd(96,24)<<endl<<gcd(14,30)<<endl<<gcd(31,61);
  return 0;
}

