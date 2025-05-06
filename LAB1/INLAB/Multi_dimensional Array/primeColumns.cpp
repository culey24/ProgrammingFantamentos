bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int primeColumns(int arr[][1000], int row, int col) {
    int prime_count = 0; 
    for (int j = 0; j < col; j++) {
        int sum_col = 0;
        for (int i = 0; i < row; i++) {
            sum_col += arr[i][j];    
        }
        if (is_prime(sum_col)) {
            prime_count++;
        }
    }
    return prime_count;
}