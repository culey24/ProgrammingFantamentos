int compareObjectClass(const SCP &objA, const SCP &objB) {
    if (objA.objClass > objB.objClass) return 1;
    else if (objA.objClass == objB.objClass) return 0;
    else return -1;
}