#include <iostream>
using std::cout;
using std::endl;
namespace test{
  void helloworld(){cout<<"helloworld"<<endl;}
}
int main(){
  test::helloworld();
  return 0;
} 
