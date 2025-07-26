bool isUpper(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

bool isLower(char ch) {
    return ch >= 'a' && ch <= 'z';
}

void to_lowercase(char &ch) {
    if (isUpper(ch)) {
        ch -= 'A' - 'a';
    }   
    return;
}

void to_uppercase(char &ch) {
    if (isLower(ch)) {
        ch += 'A' - 'a';
    }   
    return;
}

void recover(char signal[]) {
    // TODO
    if (!signal) {
        return;
    }
    int signal_len = strlen(signal);
    for (int i = 0; i < signal_len; i++) {
        if (isUpper(signal[i])) {
            to_lowercase(signal[i]); 
        }
        else if (isLower(signal[i])) {
            to_uppercase(signal[i]);
        }
    }
    return;
}