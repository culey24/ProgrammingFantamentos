void calMoney(string price, string buy) {
    //TODO
    ifstream priceFile(price);
    ifstream buyFile(buy);
    
    if (!priceFile || !buyFile) {
        return;
    }
    
    string line;
    getline(priceFile, line);
    int N = stoi(line);
    
    string priceData[20][2];
    for (int i = 0; i < N; i++) {
        priceFile >> priceData[i][0] >> priceData[i][1];
    }
    priceFile.close();
    
    getline(buyFile, line);
    int M = stoi(line);
    
    for (int i = 0; i < M; i++) {
        if (!getline(buyFile, line)) continue; 
        
        size_t pos = 0;
        string customer;
        if ((pos = line.find(' ')) != string::npos) {
            customer = line.substr(0, pos);
            line = line.substr(pos + 1);
        } else {
            continue;
        }
        
        int totalCost = 0;
        while (!line.empty()) {
            size_t space1 = line.find(' ');
            if (space1 == string::npos) break;
            string productId = line.substr(0, space1);
            line = line.substr(space1 + 1);
            
            size_t space2 = line.find(' ');
            string quantity = (space2 == string::npos) ? line : line.substr(0, space2);
            line = (space2 == string::npos) ? "" : line.substr(space2 + 1);
            
            for (int j = 0; j < N; j++) {
                if (priceData[j][0] == productId) {
                    totalCost += stoi(priceData[j][1]) * stoi(quantity);
                    break;
                }
            }
        }
        cout << customer << " " << totalCost << endl;
    }
    buyFile.close();
}