#include "sort.hpp"
#include <iostream>
#include <vector>
using namespace std;

void print_v(const vector<int> &v)
{
    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << "\n";
}

void gen_v(vector<int> &v)
{
    vector<int> vec;
    vec.push_back(9);
    vec.push_back(18);
    vec.push_back(27);
    vec.push_back(36);
    vec.push_back(45);


    v = vec;
}

int main()
{
    vector<int> vector;

    gen_v(vector);
    cout << "bubble: ";
    bubble_sort(vector, std::less<int>());
    print_v(vector);

    gen_v(vector);
    cout << "insertion: ";
    insertion_sort(vector, std::less<int>());
    print_v(vector);

    gen_v(vector);
    cout << "selection: ";
    selection_sort(vector, std::less<int>());
    print_v(vector);

    gen_v(vector);
    cout << "merge: ";
    merge_sort(vector, std::less<int>());
    print_v(vector);

//    gen_v(vector);
//    cout << "qs_ext: ";
//    quick_sort_extra(vector, std::less<int>());
//    print_v(vector);

    gen_v(vector);
    cout << "qs_inp: ";
    quick_sort_inplace(vector, std::less<int>());
    print_v(vector);
}