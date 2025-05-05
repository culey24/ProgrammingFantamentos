int getSize(char* str) {
    int count = 0;
    while (str[count] != '\0') count++;
    return count;
}

char* concatStr(char* str1, char* str2) {
    // TODO
    int size1 = getSize(str1);
    int size2 = getSize(str2);
    char* result = new char[size1 + size2];
    for (int i = 0; i < size1; i++) {
        result[i] = str1[i];
    }
    for (int i = 0; i < size2; i++) {
        result[size1 + i] = str2[i];
    }
    result[size1 + size2] = '\0';
    return result;
}

