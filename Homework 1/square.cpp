#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

// REQUIRES: vector A
// EFFECTS: do the square sort asked by the question
// TODO: finish this function
vector<int> square_sort(vector<int> &A)
{
    int n= static_cast<int>(A.size());
    int zero_index;
    for (int i = 0; i <n ; ++i) {
        // square all the elements
        A[i]=A[i]*A[i];
        // find the index of zero
        if(A[i]==0) zero_index=i;
    }
    int p1=zero_index,p2=zero_index-1;
    // use part of the idea of merge sort
    // merge the left part and the right part together
    if(p1==0) return A;
    else{
        vector<int> ans;
        while (p1<n && p2>=0){
            if (A[p1]<A[p2]) {
                ans.emplace_back(A[p1]);
                ++p1;
            }
            else {
                ans.emplace_back(A[p2]);
                --p2;
            }
        }
        while (p1<n){
            ans.emplace_back(A[p1]);
            ++p1;
        }
        while (p2>=0){
            ans.emplace_back(A[p2]);
            --p2;
        }
        return ans;
    }
}

// MAIN
// NOTE: DO NOT MODIFY THIS PART
int main()
{
	vector<int> A;
	string s;
	getline(cin, s);

	stringstream ss(s);
	int temp;
	while (ss >> temp)
		A.emplace_back(temp);

	for (auto item : square_sort(A))
		cout << item << " ";
	cout << "\n";
	return 0;
}
