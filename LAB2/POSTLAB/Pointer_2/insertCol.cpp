int** insertCol(int**& matrix, int r, int c, int* colArr, int col) {
    // TODO
    int** newArr = new int*[r];
    for (int i = 0; i < r; i++) {
        newArr[i] = new int[c + 1];
        for (int j = 0; j < col; j++) {
            newArr[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < r; i++) {
        newArr[i][col] = colArr[i];
    }
    for (int i = 0; i < r; i++) {
        for (int j = col; j < c; j++) {
            newArr[i][j + 1] = matrix[i][j];
        }
    }
    for (int i = 0; i < r; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = newArr;
    return matrix;
}