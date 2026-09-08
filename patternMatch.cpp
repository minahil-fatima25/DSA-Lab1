#include <iostream>
#include <string>
using namespace std;


int naiveSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) return -1; 

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return i; 
        }
    }
    return -1; 
}

int main() {
    // Test 1:Pattern at the beginning
    cout << "Test 1 (pattern at beginning): "
         << naiveSearch("hello world", "hello") << endl; 
    // Test 2:Pattern at the end
    cout << "Test 2 (pattern at end): "
         << naiveSearch("hello world", "world") << endl; 
    //Test 3:Pattern not present
    cout << "Test 3 (pattern not present): "
         << naiveSearch("hello world", "xyz") << endl; 
    //Test 4:Empty pattern
    cout << "Test 4 (empty pattern): "
         << naiveSearch("hello world", "") << endl; 

    return 0;
}