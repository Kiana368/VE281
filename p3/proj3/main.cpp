#include <tuple>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include "kdtree.hpp"
using namespace std;

int main()
{

    vector<pair<tuple<int, int, int>, int>> v{};
    KDTree<tuple<int, int, int>, int> tree{v};
    // auto &x = const_cast<tuple<int, int, int> &>(tree.root->key());
    // x = {1, 2, 3};
    // auto &y = tree.root->key();
    // cout << get<0>(y) << ' ' << get<1>(y) << ' ' << get<2>(y) << endl;
    tree.insert({0,0,0},3);
    tree.insert({10, 20, 30}, 2);
    tree.insert({30, 20, 30}, 3);
    tree.insert({10, 10, 30}, 4);
    tree.insert({10, 30, 30}, 5);
    tree.insert({30, 10, 30}, 6);
    tree.insert({30, 30, 30}, 7);
    tree.erase({10, 20, 30});
    tree.erase({20, 30, 40});
    for (auto &item : tree)
    {
        cout << item.second << "\n";
    }
    cout << "-----------------------" << endl;
    cout << tree.find({0, 0, 0})->second << endl;
    cout << (tree.find({30, 20, 30}) == tree.end()) << endl;
    // cout << tree.find({30, 10, 30})->second << endl;
    //cout << tree.root->value() << endl;
}
