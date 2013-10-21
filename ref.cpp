#include <iostream>
using namespace std;
int a=10;

int & geta(){return a;}
int main(){
  int &b=geta();
  cout<<b<<endl;//10
  b=11;
  cout<<a<<endl;//11
  cout<<&a<<" "<<&b; //0x402000 0x402000
  return 0;
}
