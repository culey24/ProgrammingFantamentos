int diagonalProduct(int arr[][1000], int row, int col) {
    if (row != col) {
        return 0;
    }
    int product = 1;
    for (int i = 0; i < row; i++) {
        product *= arr[i][i];
    }
    return product;
} 

