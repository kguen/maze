#include <iostream>
#include <unistd.h>

using namespace std;

int main(void) {
  char buf[255];
  getcwd(buf, sizeof(buf));
  cout << "Current working directory is " << buf << endl;
  return 0;
}