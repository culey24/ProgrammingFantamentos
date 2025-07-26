int findMaxColumn(int arr[][1000], int row, int col) {
    int max_sum = INT_MIN;
    int max_column = -1;
    for (int col_idx = 0; col_idx < col; col_idx++) {
        int temp_sum = 0;
        for (int row_idx = 0; row_idx < row; row_idx++) {
            temp_sum += arr[row_idx][col_idx];
        }
        if (temp_sum > max_sum) {
            max_sum = temp_sum;
            max_column = col_idx;
        }
        else if ((temp_sum == max_sum) && (max_column < col_idx)) {
            max_column = col_idx;
        }
    }
    return max_column;
}