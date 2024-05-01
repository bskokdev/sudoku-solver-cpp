#include <bits/stdc++.h>

using namespace std;

#define nl "\n"

bool isValid(vector<vector<int>>& sudoku, int r, int c, int num) {
    // row & col check
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][c] == num || sudoku[r][i] == num) {
            return false;
        }
    }

    // offsets to access the start position of 3x3 subgrids
    int dy = r - r % 3;
    int dx = c - c % 3;

    // check subgrids
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[i + dy][j + dx] == num) {
                return false;
            }
        }
    }
    return true;
}


bool dfs(int r, int c, vector<vector<int>>& sudoku) {
    // we have filled the sudoku -> solution is found
    if (r == 9) {
        return true;
    }

    // we have filled the cells in the current row -> move to the next row
    if (c == 9) {
        return dfs(r+1, 0, sudoku);
    }

    // we don't care about non-zero values
    if (sudoku[r][c] != 0) {
        return dfs(r, c+1, sudoku);
    }


    // Here we choose numbers 1-9 for an empty position
    // If such position is valid (not seen in row, col, or 3x3 subgrid), we keep it
    // If it's not valid, we reset to the empty state (backtrack)
    for (int i = 1; i <= 9; i++) {
        if (isValid(sudoku, r, c, i)) {
            sudoku[r][c] = i;
            if (dfs(r, c+1, sudoku)) {
                return true;
            }
            sudoku[r][c] = 0;
        }
    }
    return false;
}

void solve() {
    int r = 9, c = 9;
    ifstream input_file("sudoku1.txt");
    vector<vector<int>> sudoku(r, vector<int>(c));

    // Read the data from the file into the sudoku grid
    for (int i = 0; i < r; i++) {
        string row;
        input_file >> row;
        for (int j = 0; j < c; j++) {
            sudoku[i][j] = row[j] - '0';
        }
    }

    input_file.close();

    // print the sudoku grid if it has a valid solution
    if (dfs(0, 0, sudoku)) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << sudoku[i][j] << " ";
            }
            cout << nl;
        }
    } else {
        cout << "No solution" << nl;
    }
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}


