int diagonalDiff(int arr[][1000], int row, int col, int x, int y) {
    int sum_diagonal_1 = 0;
    int sum_diagonal_2 = 0;
    if (!arr) {
        return -1;
    }
    
    // diagonal 1 sum
    for (int i = x, j = y; i >= 0 && j >= 0; --i, --j) {
        sum_diagonal_1 += arr[i][j];
    }
    for (int i = x + 1, j = y + 1; i < row && j < col; ++i, ++j) {
        sum_diagonal_1 += arr[i][j];
    }
    
    // diagonal 2 sum
    for (int i = x, j = y; i >= 0 && j < col; --i, ++j) {
        sum_diagonal_2 += arr[i][j];
    }
    for (int i = x + 1, j = y - 1; i < row && j >= 0; ++i, --j) {
        sum_diagonal_2 += arr[i][j];
    }
    
    return abs(sum_diagonal_1 - sum_diagonal_2);
}