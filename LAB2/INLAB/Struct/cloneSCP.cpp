SCP* cloneSCP(SCP* original) {
    // Student answer
    SCP* scp = new SCP();
    scp->id = original->id;
    scp->objClass = original->objClass;
    scp->speConProcedures = original->speConProcedures;
    scp->description = original->description;
    scp->numAddendums = original->numAddendums;
    scp->addendums = new string[scp->numAddendums];
    for (int i = 0; i < scp->numAddendums; i++) {
        scp->addendums[i] = original->addendums[i];
    }
    return scp;
}