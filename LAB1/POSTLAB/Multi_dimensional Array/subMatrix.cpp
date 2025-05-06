int subMatrix(int arr[][1000], int row, int col) {
    int HN4_count = 0;
    int sum = 0;
    for (int i = 0; i < row - 1; i++) {
        for (int j = 0; j < col - 1; j++) {
            sum = arr[i][j] + arr[i + 1][j] + arr[i][j + 1] + arr[i + 1][j + 1];
            if (sum % 2 != 0) HN4_count++;
        }
    }
    return HN4_count;
}