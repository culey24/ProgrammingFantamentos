void insertRow(int**& matrix, int r, int c, int* rowArr, int row) {
    // TODO
    int** newMatrix = new int*[r + 1];
    for (int i = 0; i < row; i++) {
        newMatrix[i] = new int[c];
        for (int j = 0; j < c; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    newMatrix[row] = new int[c];
    for (int i = 0; i < c; i++) {
        newMatrix[row][i] = rowArr[i];
    }
    for (int i = row + 1; i < r + 1; i++) {
        newMatrix[i] = new int[c];
        for (int j = 0; j < c; j++) {
            newMatrix[i][j] = matrix[i-1][j];
        }
    }
    for (int i = 0; i < r; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = newMatrix;
}