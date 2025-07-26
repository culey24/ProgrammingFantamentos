int ascendingRows(int arr[][1000], int row, int col) {
    if (!arr) return -1;
    int HN1_count = 0;
    for (int i = 0; i < row; i++) { 
        bool isHN1 = true;
        int temp = arr[i][0]; 
        for (int j = 1; j < col; j++) {
            if (arr[i][j] <= temp) {
                isHN1 = false;
            } 
            else {
                temp = arr[i][j];
            }
        }
        if (isHN1) {
            HN1_count++;    
        }
    }
    return HN1_count;
}