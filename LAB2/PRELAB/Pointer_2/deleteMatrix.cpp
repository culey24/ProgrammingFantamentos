void deleteMatrix(int**& matrix, int r) {
    // TODO
    for (int i = 0; i < r; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}