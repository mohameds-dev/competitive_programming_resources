#include <bits/stdc++.h>
using namespace std;

// Type alias for numeric type used in computations
// Use 'double' for general geometry or 'long double' for higher precision
typedef double T;

// Tolerance value for comparing floating-point numbers
const T EPS = 1e-9;

/* ================================================================
   Function: solve2x2
   ---------------------------------------------------------------
   Solves a 2x2 linear system:
       a1*x + b1*y = c1
       a2*x + b2*y = c2
   using Cramer's rule (determinant method).

   Returns:
     - pair<bool, pair<T,T>>
       -> bool = true if there’s a unique solution
       -> (x, y) = the computed solution
       -> if bool = false, lines are parallel or coincident.

   Time Complexity:
     O(1) — constant number of arithmetic operations.
================================================================ */
pair<bool, pair<T,T>> solve2x2(T a1, T b1, T c1,
                               T a2, T b2, T c2) {
    T det = a1*b2 - a2*b1; // determinant of coefficient matrix
    if (fabs(det) < EPS) { // near-zero determinant → no unique solution
        return {false, {0,0}};
    }
    // Cramer's rule formulas for x and y
    T x = (c1*b2 - c2*b1) / det;
    T y = (a1*c2 - a2*c1) / det;
    return {true, {x, y}};
}

/* ================================================================
   Function: gauss
   ---------------------------------------------------------------
   Solves a general linear system:
       A * x = b
   using Gaussian elimination (with partial pivoting).

   Input:
     - A: n×m coefficient matrix (modified in-place)
     - b: right-hand side vector of length n

   Output:
     - vector<T> of size m containing one valid solution
     - empty vector => no solution exists

   Notes:
     - Works for both square and rectangular systems
     - Can be extended to detect infinite solutions (free variables)
     - Uses floating-point arithmetic; consider modular/integer variant if needed

   Time Complexity:
     O(n * m^2) for a general rectangular system
     O(n^3) for square systems (n ≈ m)

================================================================ */
vector<T> gauss(vector<vector<T>>& A, vector<T>& b) {
    int n = A.size();                      // number of equations
    int m = (n > 0 ? A[0].size() : 0);     // number of variables
    vector<int> where(m, -1);               // which row defines each variable

    // Iterate over columns (variables)
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        // === Find pivot (largest absolute value in column) ===
        int sel = row;
        for (int i = row; i < n; ++i) {
            if (fabs(A[i][col]) > fabs(A[sel][col])) {
                sel = i;
            }
        }

        // If pivot is effectively zero, skip this column (no pivot here)
        if (fabs(A[sel][col]) < EPS) {
            continue;
        }

        // Swap current row with pivot row
        swap(A[sel], A[row]);
        swap(b[sel], b[row]);
        where[col] = row;

        // === Normalize pivot row ===
        T inv = 1.0 / A[row][col];
        for (int j = col; j < m; ++j) {
            A[row][j] *= inv;              // make pivot = 1
        }
        b[row] *= inv;

        // === Eliminate this variable from all other rows ===
        for (int i = 0; i < n; ++i) {
            if (i != row) {
                T factor = A[i][col];
                for (int j = col; j < m; ++j) {
                    A[i][j] -= factor * A[row][j];
                }
                b[i] -= factor * b[row];
            }
        }
        ++row;
    }

    // === Back-substitution / solution extraction ===
    vector<T> ans(m, 0);
    for (int i = 0; i < m; ++i) {
        if (where[i] != -1) {
            ans[i] = b[where[i]];
        }
    }

    

    // === Consistency check ===
    // Ensures the found solution actually satisfies all equations
    for (int i = 0; i < n; ++i) {
        T sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += A[i][j] * ans[j];
        }
        if (fabs(sum - b[i]) > EPS) {
            // No valid solution
            return vector<T>();
        }
    }

    return ans;
}



int binary_search_lte(const vector<int>&arr, int value){
   auto it = upper_bound(arr.begin(), arr.end(), value);
   return it == arr.begin() ? -1 : int(it - arr.begin() - 1);
}

