bool deleteRow(int**& matrix, int r, int c, int row) {
    // TODO
    if (!(row >= 0 && row < r)) return false;
    if (r == 1) {
        delete[] matrix[0];
        delete[] matrix;
        matrix = nullptr;
        return true;
    }
    int** newMatrix = new int*[r - 1];
    for (int i = 0; i < row; i++) {
        newMatrix[i] = new int[c];
        for (int j = 0; j < c; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for (int i = row + 1; i < r; i++) {
        newMatrix[i-1] = new int[c];
        for (int j = 0; j < c; j++) {
            newMatrix[i-1][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < r; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = newMatrix;
    return true;
}