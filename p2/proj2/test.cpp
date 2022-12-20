//
// Created by junsi on 2021/10/26.
//

#include <forward_list>
#include <iostream>
using namespace std;

int main()
{
    // declaration of forward list container
    forward_list<int> myflist{ 1,2 ,3};

    // using end() to print forward list
//    for (auto it = myflist.begin(); it != myflist.end(); ++it)
//        cout << ' ' << *it;
    auto it=myflist.end();
    cout<<*(it)<<endl;
    return 0;
}