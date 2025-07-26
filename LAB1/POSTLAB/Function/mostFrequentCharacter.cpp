void mostFrequentCharacter(char* str, char& res, int& freq) {
    // Write your code 
    int count[26] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        count[tolower(str[i]) - 'a']++;
    }

    freq = 0;
    res = 'z';

    for (int i = 0; i < 26; i++) {
        if (count[i] > freq) {
            freq = count[i];
            res = 'a' + i;
        } else if (count[i] == freq && ('a' + i) < res) {
            res = 'a' + i;
        }
    }
}