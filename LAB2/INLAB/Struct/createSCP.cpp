SCP createSCP(int id, int objClass, string speConProcedures, string description, string* addendums, int numAddendums) {
    // Student answer
    SCP scp;
    scp.id = id;
    scp.objClass = objClass;
    scp.speConProcedures = speConProcedures;
    scp.description = description;
    scp.addendums = addendums;
    scp.numAddendums = numAddendums;
    return scp;
}