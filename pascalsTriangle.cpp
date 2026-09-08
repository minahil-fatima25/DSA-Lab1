#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> generatePascalsTriangle(int n) {
    vector<vector<int>> triangle;

    for (int i = 0; i < n; i++) {
        vector<int> row(i + 1);
        row[0] = row[i] = 1; 

        for (int j = 1; j < i; j++) {
            row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }

        triangle.push_back(row);
    }
    return triangle;
}
void printTriangle(const vector<vector<int>>& triangle) {
    for (const auto& row : triangle) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << "Test 1 (n = 0):" << endl;
    auto t0 = generatePascalsTriangle(0);
    printTriangle(t0);
    if (t0.empty()) cout << "(empty)" << endl;
    cout << endl;
    cout << "Test 2 (n = 1):" << endl;
    auto t1 = generatePascalsTriangle(1);
    printTriangle(t1);
    cout << endl;
    cout << "Test 3 (n = 5):" << endl;
    auto t5 = generatePascalsTriangle(5);
    printTriangle(t5);
    vector<int> expectedRow5 = {1, 4, 6, 4, 1};
    bool match = (t5[4] == expectedRow5);
    cout << "Row 5 matches {1,4,6,4,1}: " << (match ? "PASS" : "FAIL") << endl;

    return 0;
}