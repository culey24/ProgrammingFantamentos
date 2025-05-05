int* flatten(int** matrix, int r, int c) {
    //TODO
    int* arr = new int[r * c];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            arr[i*c + j] = matrix[i][j];
        }
    }
    return arr;
}