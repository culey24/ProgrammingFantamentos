void studentGrading(string fileName)   {
    // TODO
    ifstream file(fileName);
    if (!file.is_open()) {
        return;
    }
    int N;
    file >> N;
    int A_grade_count = 0, B_grade_count = 0, C_grade_count = 0, D_grade_count = 0;
    for (int i = 0; i < N; i++) {
        float nmdt, ktlt, dsa, ppl;
        file>>nmdt>>ktlt>>dsa>>ppl;
        float average = (nmdt + ktlt + dsa + ppl)/4.0;
        bool isBelow5 = (nmdt < 5) || (ktlt < 5) || (dsa < 5) || (ppl < 5);
        if (average >= 8 && !isBelow5) {
            A_grade_count++;
        }
        else if (average < 8 && average >= 6.5 && !isBelow5) {
            B_grade_count++;
        }
        else if (average < 6.5 && average >= 5 && !isBelow5) {
            C_grade_count++;
        }
        else {
            D_grade_count++;
        }
    }
    cout<<"A "<<A_grade_count<<endl;
    cout<<"B "<<B_grade_count<<endl;
    cout<<"C "<<C_grade_count<<endl;
    cout<<"D "<<D_grade_count<<endl;
    file.close();
}