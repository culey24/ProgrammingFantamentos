bool isSymmetric(int arr[][1000], int row, int col) {
    if (row != col) {
        return false;
    }
    bool symmetric_property = true;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] != arr[j][i]) {
                symmetric_property = false;  
                break;
            }
        }
    }
    return symmetric_property;
}