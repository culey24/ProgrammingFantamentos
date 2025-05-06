void calSum(string fileName)   {
    // TODO
    string data;
    ifstream ifs(fileName);
    if (!ifs.is_open()) {
        return; 
    }
    getline(ifs, data);
    ifs.close();
    
    const int DATA_LEN = data.length();
    string temp;
    int sum = 0;
    for (int i = 0; i < DATA_LEN; i++) {
        if (data[i] != ' ') {
            temp += data[i];
        }
        if ((data[i] == ' ') || (i == DATA_LEN - 1)) {
            if (stoi(temp) >= 0) {
                sum += stoi(temp);
            }
            temp.clear();
        }
    }
    cout<<sum;
    return; 
}  