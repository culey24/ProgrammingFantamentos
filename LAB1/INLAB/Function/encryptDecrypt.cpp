bool isUpper(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

bool isLower(char ch) {
    return ch >= 'a' && ch <= 'z';
}

int getlength(const char* text) {
    int i = 0;
    while (text[i] != '\0') {
         i++;
    }
    return i;
}

void encrypt(char* text, int shift) {
    // Write your code 
    int len = getlength(text);
    shift = ((shift % 26) + 26) % 26;
    if (!text) return;
    for (int i = 0; i < len; i++) {
        if (isUpper(text[i])) {
            text[i] = (text[i] + shift - 'A') % 26 + 'A';
        }
        else if (isLower(text[i])) {
            text[i] = (text[i] + shift - 'a') % 26 + 'a';
        }
    }
    return;
}

void decrypt(char* text, int shift) {
    // Write your code 
    int len = getlength(text);
    shift = ((shift % 26) + 26) % 26;
    if (!text) return;
    for (int i = 0; i < len; i++) {
        if (isUpper(text[i])) {
            text[i] = (text[i] - shift - 'A' + 26) % 26 + 'A';
        }
        else if (isLower(text[i])) {
            text[i] = (text[i] - shift - 'a' + 26) % 26 + 'a';
        }
    }
    return;
}