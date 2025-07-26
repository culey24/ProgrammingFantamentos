bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int specialCells(int arr[][1000], int row, int col) {
    int HN3_count = 0;
    int rowSum[row] = {0};
    int colSum[col] = {0};
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            rowSum[i] += arr[i][j];
            colSum[j] += arr[i][j];
        }
    }
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (isPrime(rowSum[i]) && isPrime(colSum[j])) {
                HN3_count++;
            }
        }
    }
    return HN3_count;
}