#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix naiveMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

Matrix add(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subtract(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}
// Splits matrix M into 4 quadrants
void splitMatrix(const Matrix& M, Matrix& A11, Matrix& A12, Matrix& A21, Matrix& A22) {
    int n = M.size() / 2;
    A11 = Matrix(n, vector<int>(n));
    A12 = Matrix(n, vector<int>(n));
    A21 = Matrix(n, vector<int>(n));
    A22 = Matrix(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A11[i][j] = M[i][j];
            A12[i][j] = M[i][j + n];
            A21[i][j] = M[i + n][j];
            A22[i][j] = M[i + n][j + n];
        }
    }
}
// Combines 4 quadrants back into one matrix
Matrix combineMatrix(const Matrix& C11, const Matrix& C12, const Matrix& C21, const Matrix& C22) {
    int n = C11.size();
    Matrix C(2 * n, vector<int>(2 * n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = C11[i][j];
            C[i][j + n] = C12[i][j];
            C[i + n][j] = C21[i][j];
            C[i + n][j + n] = C22[i][j];
        }
    }
    return C;
}
// Strassen's algorithm 
Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();

    
    if (n == 1) {
        Matrix C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    Matrix A11, A12, A21, A22, B11, B12, B21, B22;
    splitMatrix(A, A11, A12, A21, A22);
    splitMatrix(B, B11, B12, B21, B22);

    Matrix M1 = strassenMultiply(add(A11, A22), add(B11, B22));
    Matrix M2 = strassenMultiply(add(A21, A22), B11);
    Matrix M3 = strassenMultiply(A11, subtract(B12, B22));
    Matrix M4 = strassenMultiply(A22, subtract(B21, B11));
    Matrix M5 = strassenMultiply(add(A11, A12), B22);
    Matrix M6 = strassenMultiply(subtract(A21, A11), add(B11, B12));
    Matrix M7 = strassenMultiply(subtract(A12, A22), add(B21, B22));

    Matrix C11 = add(subtract(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(subtract(add(M1, M3), M2), M6);

    return combineMatrix(C11, C12, C21, C22);
}

void printMatrix(const Matrix& M) {
    for (const auto& row : M) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
}

bool matricesEqual(const Matrix& A, const Matrix& B) {
    return A == B;
}

Matrix randomMatrix(int n, int maxVal = 10) {
    Matrix M(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = rand() % maxVal;
    return M;
}

int main() {
    srand(time(0));

    cout << "Test 1: 2x2 matrix multiplication" << endl;
    Matrix A2 = {{1, 2}, {3, 4}};
    Matrix B2 = {{5, 6}, {7, 8}};
    Matrix resultStrassen2 = strassenMultiply(A2, B2);
    Matrix resultNaive2 = naiveMultiply(A2, B2);
    cout << "Strassen result:" << endl;
    printMatrix(resultStrassen2);
    cout << "Match with naive: " << (matricesEqual(resultStrassen2, resultNaive2) ? "PASS" : "FAIL") << endl << endl;

  
    cout << "Test 2: 4x4 matrix multiplication" << endl;
    Matrix A4 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    Matrix B4 = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    Matrix resultStrassen4 = strassenMultiply(A4, B4);
    Matrix resultNaive4 = naiveMultiply(A4, B4);
    cout << "Strassen result:" << endl;
    printMatrix(resultStrassen4);
    cout << "Match with naive: " << (matricesEqual(resultStrassen4, resultNaive4) ? "PASS" : "FAIL") << endl << endl;

    // Test 3: Random values compared with naive multiplication (8x8)
    cout << "Test 3: Random 8x8 matrices compared with naive" << endl;
    Matrix randA = randomMatrix(8);
    Matrix randB = randomMatrix(8);
    Matrix resultStrassenR = strassenMultiply(randA, randB);
    Matrix resultNaiveR = naiveMultiply(randA, randB);
    cout << "Match with naive: " << (matricesEqual(resultStrassenR, resultNaiveR) ? "PASS" : "FAIL") << endl;

    return 0;
}