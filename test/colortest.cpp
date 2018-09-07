#include <iostream>
#include <windows.h>
using namespace std;

void setColor(int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

int main() {
    for (int i = 1; i <= 255; ++i) {
        setColor(i);
        cout << i << ":XDXDXDXDXDXDXDXD" << endl;
    }
}
