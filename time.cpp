#include "windef.h"
#include <iostream>
#include <gl/glut.h>
using namespace std;
int main(){
  int time0=time(0);
  cout<<"helloworld"<<endl;
  cout<<glutGet(GLUT_ELAPSED_TIME)<<endl;
  return 0;
  }
