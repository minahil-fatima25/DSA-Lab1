#include <iostream>
#include <vector>
using namespace std;

vector<int> findAllIndices(const vector<int>& arr, int key) {
    vector<int> indices;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == key) {
            indices.push_back(i);
        }
    }
    return indices;
}

int main() {
    vector<int> arr1 = {1, 2, 3, 2, 4, 2, 5};
    vector<int> result1 = findAllIndices(arr1, 2);
    cout << "Test 1 (multiple occurrences of 2): ";
    for (int idx : result1) cout << idx << " ";
    cout << endl;

    vector<int> arr2 = {1, 2, 3, 4, 5};
    vector<int> result2 = findAllIndices(arr2, 10);
    cout << "Test 2 (key not present): ";
    if (result2.empty()) cout << "No indices found";
    cout << endl;

    vector<int> arr3 = {};
    vector<int> result3 = findAllIndices(arr3, 1);
    cout << "Test 3 (empty array): ";
    if (result3.empty()) cout << "No indices found";
    cout << endl;

    return 0;
}