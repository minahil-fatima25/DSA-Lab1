#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int findMode(const vector<int>& arr, bool& found) {
    if (arr.empty()) {
        found = false;
        return -1; 
    }

    unordered_map<int, int> freq;
    for (int num : arr) {
        freq[num]++;
    }

    int maxFreq = 0;
    int mode = arr[0];
    for (auto& pair : freq) {
        if (pair.second > maxFreq || (pair.second == maxFreq && pair.first < mode)) {
            maxFreq = pair.second;
            mode = pair.first;
        }
    }

    found = true;
    return mode;
}

int main() {
    bool found;

    vector<int> arr1 = {1, 2, 2, 3, 4};
    int mode1 = findMode(arr1, found);
    cout << "Test 1 (unique mode): " << (found ? to_string(mode1) : "N/A")
         << " (expected 2)" << endl;

    vector<int> arr2 = {1, 1, 2, 2, 3};
    int mode2 = findMode(arr2, found);
    cout << "Test 2 (multiple modes, tie broken by smallest value): "
         << (found ? to_string(mode2) : "N/A") << " (expected 1)" << endl;

    vector<int> arr3 = {};
    int mode3 = findMode(arr3, found);
    cout << "Test 3 (empty array): " << (found ? to_string(mode3) : "No mode (array empty)") << endl;

    return 0;
}