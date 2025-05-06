void printFirstRepeatedWord(char str[]) {
    // TODO
    const int MAX_WORDS = 1000;
    const int MAX_LENGTH = 100;
    char word_list[MAX_WORDS][MAX_LENGTH];
    char * ptr = strtok(str, " ");
    int list_count = 0;
    while(ptr != NULL) {
      for (int i = 0; i < list_count; i++) {
          if (strcmp(ptr, word_list[i]) == 0) {
              cout<<ptr;
              return;
          }
      }
      
      strcpy(word_list[list_count], ptr);
      list_count++;
      
      ptr = strtok(NULL, " ");
    }
    cout<<"No Repetition";
    return;
}    