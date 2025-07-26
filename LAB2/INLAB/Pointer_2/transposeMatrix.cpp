int** transposeMatrix(int** matrix, int r, int c) {
    // TODO
    if (r == 0 || c == 0) return nullptr;
    int** result = new int*[c];
    for (int j = 0; j < c; j++) {
        result[j] = new int[r];
        for (int i = 0; i < r; i++) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}