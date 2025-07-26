bool deleteCol(int**& matrix, int r, int c, int col) {
    // TODO
    if (!(col >= 0 && col < c)) return false;
    if (c == 1) {
        delete[] matrix[0];
        delete[] matrix;
        matrix = nullptr;
        return true;
    }
    int** newMatrix = new int*[r];
    for (int i = 0; i < r; i++) {
        newMatrix[i] = new int[c - 1];
        for (int j = 0; j < col; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = col + 1; j < c; j++) {
            newMatrix[i][j - 1] = matrix[i][j];
        }
    }
    for (int i = 0; i < r; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = newMatrix;
    return true;
}