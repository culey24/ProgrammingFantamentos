void manage(string library, string book, string author) {
    // TODO
    string userInput;
    getline(cin, userInput);
    int spaceFind = userInput.find(' ');
    if (spaceFind == string::npos) return;

    string userInputLibrary = userInput.substr(0, spaceFind);
    string userInputAuthor = userInput.substr(spaceFind + 1);

    ifstream libraryFile(library), authorFile(author);
    if (!libraryFile || !authorFile) return;

    int N;
    libraryFile >> N;
    string libraryNames[N];
    int libraryData[N][5];

    int libraryIndex = -1;
    for (int i = 0; i < N; i++) {
        libraryFile >> libraryNames[i];
        for (int j = 0; j < 5; j++) {
            libraryFile >> libraryData[i][j];
        }
        if (libraryNames[i] == userInputLibrary) {
            libraryIndex = i;
        }
    }
    libraryFile.close();

    if (libraryIndex == -1) {
        cout << "False";
        return;
    }

    int P;
    authorFile >> P;
    authorFile.ignore();

    string line, tempAuthor, tempID;
    while (getline(authorFile, line)) {
        int space = line.find(' ');
        if (space == string::npos) continue;

        tempAuthor = line.substr(0, space);
        if (tempAuthor != userInputAuthor) continue;

        line = line.substr(space + 1);
        while ((space = line.find(' ')) != string::npos) {
            tempID = line.substr(0, space);
            line = line.substr(space + 1);
            int id = stoi(tempID);
            for (int k = 0; k < 5; k++) {
                if (id == libraryData[libraryIndex][k]) {
                    cout << "True";
                    return;
                }
            }
        }
        if (!line.empty()) {
            int id = stoi(line);
            for (int k = 0; k < 5; k++) {
                if (id == libraryData[libraryIndex][k]) {
                    cout << "True";
                    return;
                }
            }
        }
    }
    cout << "False";
}