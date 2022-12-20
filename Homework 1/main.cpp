#include <iostream>
using  namespace std;

int main() {
    int n=0;
    for (int i = 0; i <1000 ; i+=32) {
        ++n;
    }
    cout<<n;
    return 0;
}
