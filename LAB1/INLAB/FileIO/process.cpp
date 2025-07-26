void process(string fileName)   {
    // TODO
    const double DOUBLE_MIN = -1 * 4.5036 * 1e307;
    ifstream file(fileName);
    if (!file) {
        return;
    }
    int n, m;
    file>>n>>m;
    double overall_max = DOUBLE_MIN;
    for (int i = 0; i < n; i++) {
        double max = DOUBLE_MIN;
        for (int j = 0; j < m; j++) {
            double temp;
            file>>temp;
            if (max < temp) {
                max = temp;
            }
        }
        cout<<max<<' ';
        if (overall_max < max) {
            overall_max = max;
        }
    }
    cout<<overall_max;
    return;
}