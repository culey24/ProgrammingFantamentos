string objClassToString(int objClass) {
    if (objClass == 0) {
        return "Safe";
    }
    else if (objClass == 1) {
        return "Euclid";
    }
    else if (objClass == 2) {
        return "Keter";
    }
    else throw std::invalid_argument("INVALID OBJCLASS");
}

string idToString(int id) {
    string idStr = to_string(id);
    int size = idStr.size();
    while (size < 3) {
        idStr = '0' + idStr;
        size++;
    }
    return idStr;
}

string convertToString(SCP obj) {
    // Student answer
    stringstream ss;
    ss<<"Item #: SCP-"<<idToString(obj.id)<<'\n'
    <<"Object Class: "<<objClassToString(obj.objClass)<<'\n'
    <<"Special Containment Procedures: "<< obj.speConProcedures<<'\n'
    <<"Description: "<<obj.description<<'\n';
    for (int i = 0; i < obj.numAddendums; i++) {
        ss<<obj.addendums[i]<<'\n';
    }
    char ch;
    ss>>ch;
    return ss.str();
}