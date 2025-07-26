// Student may implement another function as need
int getSize(const char* str) {
    int count = 0;
    while (str[count] != 0) count++;
    return count;
}

bool isLowercase(char ch) {return ch >= 'a' && ch <= 'z';}
bool isUppercase(char ch) {return ch >= 'A' && ch <= 'Z';}
bool isAlpha(char ch) {return isLowercase(ch) || isUppercase(ch);}

void process(const char *name, char *outstr) {
    // TODO
    int start_idx = 0;
    int end_idx = getSize(name) - 1;
    
    while (!isAlpha(name[start_idx])) start_idx++;
    while(!isAlpha(name[end_idx])) end_idx--;
    
    int outstrCount = 0;
    bool oneSpace = false;
    
    for (int i = start_idx; i <= end_idx; i++) {
        if (name[i] != ' ' && isAlpha(name[i])) {
            outstr[outstrCount++] = name[i];
            oneSpace = false;
        }
        else {
            if (name[i] != ' ') continue;
            if (!oneSpace) {
                outstr[outstrCount++] = ' ';
                oneSpace = true;
            }
        }
    }
    outstr[outstrCount] = '\0'; 
    
    bool cap = true;
    for (int i = 0; i < outstrCount; i++) {
        if (outstr[i] == ' ') {
            cap = true;
        }
        else {
            if (cap && isLowercase(outstr[i])) outstr[i] = outstr[i] + 'A' - 'a';
            else if (!cap && isUppercase(outstr[i])) outstr[i] = outstr[i] + 'a' - 'A';
            cap = false;
        }
    }
}