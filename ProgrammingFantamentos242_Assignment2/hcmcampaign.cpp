#include "hcmcampaign.h"

// UNIT

Unit::Unit(int quantity, int weight, Position pos)
    : quantity(quantity), weight(weight), pos(pos)
{
    this->weight = max(1, this->weight);
    this->quantity = max(1, this->quantity);
}
Unit::~Unit()
{}
Position Unit::getCurrentPosition() const
{
    return pos;
}

void Unit::setWeight(int weight) {
    this->weight = weight;
}

void Unit::setQuantity(int quantity) {
    this->quantity = quantity;
}

int Unit::getQuantity() const {return this->quantity;}
int Unit::getWeight() const {return this->weight;}
void Unit::setAttackScore(int value) {this->attackScore = value;}
int Unit::getStaticAttackScore() const {return attackScore;}

void Unit::setPos(Position pos) {this->pos = pos;}

Vehicle::Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType)
    : Unit(quantity, weight, pos), vehicleType(vehicleType)
{
}

int Vehicle::getAttackScore()
{
    attackScore = ceil(((static_cast<int>(vehicleType) * 304) + (quantity * weight))/30.0);
    return attackScore;
}

// VEHICLE

string Vehicle::str() const
{
    // TODO: Implement
    stringstream ss;
    ss << "Vehicle[vehicleType=" << getStringVehicleType()
    << ",quantity=" << quantity 
    << ",weight=" << weight  
    << ",position=" << pos.str() << ']' ;
    return ss.str();
}

string Vehicle::getStringVehicleType() const {
    switch(vehicleType) {
        case TRUCK: return "TRUCK";
        case MORTAR: return "MORTAR";
        case ANTIAIRCRAFT: return "ANTIAIRCRAFT";
        case ARMOREDCAR: return "ARMOREDCAR";
        case APC: return "APC";
        case ARTILLERY: return "ARTILLERY";
        case TANK: return "TANK";
        default: return "INVALID";
    }
}


VehicleType Vehicle::getVehicleType() {
    return this->vehicleType;
}

void Vehicle::setVehicleType(VehicleType vehicleType) {
    this->vehicleType = vehicleType;
}

Unit* Vehicle::copy() const {
    return new Vehicle(*this);
}

// INFANTRY

const int Infantry::BATTLE_YEAR = 1975;

bool Infantry::isPerfectSquare(int n) {
    if (n < 0) {return false;}
    int sqrt_n = sqrt(n);
    return (sqrt_n) * (sqrt_n) == n;
}

int Infantry::sumDigits(int n) {
    // TODO: implement
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int Infantry::computeSingleDigit(int score, int year) {
    // TODO: implement
    int personalNumber = sumDigits(score) + sumDigits(year);
    while (personalNumber/10 != 0) {
        personalNumber = sumDigits(personalNumber);
    }
    return personalNumber;
}

int Infantry::myCeil(double value) {
    return ceil(value - 1e-7);
}

Infantry::Infantry(int quantity, int weight, Position pos, InfantryType infantryType)
    : Unit(quantity, weight, pos), infantryType(infantryType)
{
}

int Infantry::getAttackScore() {
    // TODO: implement
    attackScore = static_cast<int>(infantryType) * 56 + quantity * weight;
    if (infantryType == SPECIALFORCES && isPerfectSquare(weight)) {attackScore += 75;}
    
    int personalNumber = computeSingleDigit(attackScore, BATTLE_YEAR);

    if ((personalNumber <= 7 && personalNumber >= 3) && (infantryType == SPECIALFORCES && isPerfectSquare(weight))) {
        attackScore -=75;
    }

    if (personalNumber > 7) {
        quantity = myCeil(1.2 * quantity);    
        attackScore = static_cast<int>(infantryType) * 56 + quantity * weight;
    }
    else if (personalNumber < 3) {
        quantity = myCeil(0.9 * quantity);
        attackScore = static_cast<int>(infantryType) * 56 + quantity * weight;
    }
    return attackScore;
}

string Infantry::str() const {
    stringstream ss;
    ss << "Infantry[infantryType=" << getStringInfantryType()
    << ",quantity=" << quantity
    << ",weight=" << weight
    << ",position=" << pos.str() << ']';
    return ss.str();
}

string Infantry::getStringInfantryType() const {
    switch(infantryType) {
        case SNIPER: return "SNIPER";
        case ANTIAIRCRAFTSQUAD: return "ANTIAIRCRAFTSQUAD";
        case MORTARSQUAD: return "MORTARSQUAD";
        case ENGINEER: return "ENGINEER";
        case SPECIALFORCES: return "SPECIALFORCES";
        case REGULARINFANTRY: return "REGULARINFANTRY";
        default: return "INVALID";
    }
}


InfantryType Infantry::getInfantryType() {return this->infantryType;}

Unit* Infantry::copy() const {
    return new Infantry(*this);
}

// ARMY

Army::Army(Unit **unitArray, int size, string name, BattleField* battleField) : name(name), battleField(battleField)
{
    // TODO: Implement
    LF = EXP = 0;
    for (int i = 0; i < size; i++) {
        if (Vehicle* vehicle = dynamic_cast<Vehicle*>(unitArray[i])) {
            LF += vehicle->getAttackScore();
            LF = max(0, min(1000, LF));
        }
        else if (Infantry* infantry = dynamic_cast<Infantry*>(unitArray[i])) {
            EXP += infantry->getAttackScore();
            EXP = max(0, min(500, EXP));
        }
    }
    unitList = new UnitList(LF + EXP);
    for (int i = 0; i < size; i++) {
        unitList->insert(unitArray[i]);
    }
}

Army::~Army() {
    delete unitList;
}

int Army::getLF() const {return LF;}
int Army::getEXP() const {return EXP;}
string Army::getName() const {return name;}
BattleField* Army::getBattleField() const {
    return battleField;
}

void Army::setLF(int LF) {
    this->LF = min(1000, max(0, LF));
}
void Army::setEXP(int EXP) {
    this->EXP = min(500, max(0, EXP));
}

UnitList* Army::getUnitList() const {return unitList;}
void Army::reloadScore() {
    this->LF = 0;
    this->EXP = 0;
    Node* cursor = unitList->getHead();
    while(cursor != nullptr) {
        if (Vehicle* vehicle = dynamic_cast<Vehicle*>(cursor->unit)) {
            LF += vehicle->getAttackScore();
            LF = ceil(max(0, min(1000, LF)));           
        }
        else if (Infantry* infantry = dynamic_cast<Infantry*>(cursor->unit)) {
            EXP += infantry->getAttackScore();
            EXP = ceil(max(0, min(500, EXP)));
        }
        cursor = cursor->next;
    }
}

// LIBERATION ARMY

LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name, BattleField* battleField)
                                                : Army(unitArray,size,name, battleField) {}

void LiberationArmy::fight(Army *enemy, bool defense){
    // TODO: Implement
    if (!defense) {
        LF = ceil(1.5 * LF);
        LF = max(0, min(1000, LF));   
        EXP = ceil(1.5 * EXP);
        EXP = max(0, min(500, EXP));

        UnitSubset A = minUnitSubset(unitList->getHead(), enemy->getEXP(), true); // isInfantry = true
        int sizeA = A.unitSet.size();
        UnitSubset B = minUnitSubset(unitList->getHead(), enemy->getLF(), false); // isInfantry = false, which is isVehicle = true
        int sizeB = B.unitSet.size();

        bool victory = false;

        if (A.totalScore != -1 && B.totalScore != -1) {
            victory = true;

            for (int i = 0; i < sizeA; i++) {
                A.unitSet[i]->selfDestruct(unitList->getHead());
                unitList->setInfantryCount(unitList->getInfantryCount() - 1);
            }
            for (int i = 0; i < sizeB; i++) {
                B.unitSet[i]->selfDestruct(unitList->getHead());
                unitList->setVehicleCount(unitList->getVehicleCount() - 1);
            }
        }

        else if (!(A.totalScore == -1 && B.totalScore == -1)) {
            if (A.totalScore == -1) {
                if (EXP > enemy->getEXP()) {
                    victory = true;
                    Node* cursor = unitList->getHead();
                    while (cursor != nullptr) {
                        Node* nextCursor = cursor->next;
                        if (dynamic_cast<Infantry*>(cursor->unit)) {
                            cursor->selfDestruct(unitList->getHead());
                            unitList->setInfantryCount(unitList->getInfantryCount() - 1);
                        }
                        cursor = nextCursor;
                    }
                    for (int i = 0; i < sizeB; i++) {
                        B.unitSet[i]->selfDestruct(unitList->getHead());
                        unitList->setVehicleCount(unitList->getVehicleCount() - 1);
                    }
                }
            }
            else if (B.totalScore == -1) {
                if (LF > enemy->getLF()) {
                    victory = true;
                    Node* cursor = unitList->getHead();
                    while (cursor != nullptr) {
                        Node* nextCursor = cursor->next;
                        if (dynamic_cast<Vehicle*>(cursor->unit)) {
                            cursor->selfDestruct(unitList->getHead());
                            unitList->setVehicleCount(unitList->getVehicleCount() - 1);
                        }
                        cursor = nextCursor;
                    }
                    for (int i = 0; i < sizeA; i++) {
                        A.unitSet[i]->selfDestruct(unitList->getHead());
                        unitList->setInfantryCount(unitList->getInfantryCount() - 1);
                    }
                }  
            }
        }
        if (victory) {
            UnitList* reversedCopy = enemy->getUnitList()->shallowReverseCopy();
            Node* cursor = reversedCopy->getHead();
            while (cursor != nullptr) {
                Node* nextCursor = cursor->next;
                if (unitList->insert(cursor->unit)) {
                    if (Vehicle* vehicle = dynamic_cast<Vehicle*>(cursor->unit)) {
                        enemy->getUnitList()->deleteVehicle(vehicle->getVehicleType());
                        enemy->getUnitList()->setVehicleCount(enemy->getUnitList()->getVehicleCount() - 1);
                        enemy->getUnitList()->updateSize();
                    }
                    else if (Infantry* infantry = dynamic_cast<Infantry*>(cursor->unit)) {
                        enemy->getUnitList()->deleteInfantry(infantry->getInfantryType());
                        enemy->getUnitList()->setInfantryCount(enemy->getUnitList()->getInfantryCount() - 1);
                        enemy->getUnitList()->updateSize();
                    }
                }
                cursor = nextCursor;
            }
            cursor = enemy->getUnitList()->getHead();
            while (cursor != nullptr) {
                Node* nextCursor = cursor->next;
                if (Vehicle* vehicle = dynamic_cast<Vehicle*>(cursor->unit)) {
                    if (this->getUnitList()->isContain(vehicle->getVehicleType())) {
                        enemy->getUnitList()->deleteVehicle(vehicle->getVehicleType());
                        enemy->getUnitList()->setVehicleCount(enemy->getUnitList()->getVehicleCount() - 1);
                        enemy->getUnitList()->updateSize();
                    }
                }
                else if (Infantry* infantry = dynamic_cast<Infantry*>(cursor->unit)) {
                    if (this->unitList->isContain(infantry->getInfantryType())) {
                        enemy->getUnitList()->deleteInfantry(infantry->getInfantryType());
                        enemy->getUnitList()->setInfantryCount(enemy->getUnitList()->getInfantryCount() - 1);
                        enemy->getUnitList()->updateSize();
                    }
                }
                cursor = nextCursor;
            }
            delete reversedCopy;
            enemy->getUnitList()->reduceWeight(0.2);
            enemy->reloadScore();
            this->reloadScore();
        }
        else {
            unitList->reduceWeight(0.1);    
            this->reloadScore();
        }
    }
    else {
        bool victory = false;
        LF = ceil(1.3 * LF);
        LF = max(0, min(1000, LF));   
        EXP = ceil(1.3 * EXP);
        EXP = max(0, min(500, EXP));
        while (!victory) {  
            if (LF >= enemy->getLF() && EXP >= enemy->getEXP()) {
                victory = true;
            }
            else if (!(LF < enemy->getLF() && EXP < enemy->getEXP())) {
                unitList->reduceQuantity(0.1);
                this->reloadScore();
                victory = true;
            }
            else {
                Node* cursor = unitList->getHead();
                while (cursor != nullptr) {
                    cursor->unit->setQuantity(ceilFibonacci(cursor->unit->getQuantity()));
                    cursor = cursor->next;
                }
                this->reloadScore();
            }
        }
    }
}

string LiberationArmy::str() const {
    if (battleField) {
        stringstream ss;
        ss<<"LiberationArmy["
        <<"LF="<<LF
        <<",EXP="<<EXP
        <<",unitList="<<unitList->str()
        <<",battleField="<<battleField->str()
        <<']';
        return ss.str();
    }
    else {
        stringstream ss;
        ss<<"LiberationArmy["
        <<"LF="<<LF
        <<",EXP="<<EXP
        <<",unitList="<<unitList->str()
        <<",battleField="
        <<']';
        return ss.str();
    }
}

int LiberationArmy::ceilFibonacci(int value) {
    if (value < 0) return 1;
    int a = 0, b = 1;
    while (b <= value) {
        int temp = b;
        b = a + b;
        a = temp;
    }
    return b;
}

void LiberationArmy::findMinUnitSubset(Node* cursor, int threshold, int currentSum, vector<Node*> currentSet, UnitSubset& bestSubset, bool isInfantry) {
    if (currentSum > threshold && (bestSubset.totalScore == -1 || currentSum < bestSubset.totalScore)) {
        bestSubset.totalScore = currentSum;
        bestSubset.unitSet = currentSet;
    }

    while (cursor != nullptr) {
        Unit* unit = cursor->unit;
        bool condition = ((isInfantry && dynamic_cast<Infantry*>(unit) || !isInfantry && dynamic_cast<Vehicle*>(unit)) && cursor->unit->getStaticAttackScore() > 0);
        if (condition) {
            currentSet.push_back(cursor);
            findMinUnitSubset(cursor->next, threshold, currentSum + unit->getStaticAttackScore(), currentSet, bestSubset, isInfantry);
            currentSet.pop_back();
        }
        cursor = cursor->next;
    }
}      

UnitSubset LiberationArmy::minUnitSubset(Node* head, int threshold, bool isInfantry) {
    UnitSubset newSet;
    newSet.totalScore = -1;
    vector<Node*> tempSet;
    findMinUnitSubset(head, threshold, 0, tempSet, newSet, isInfantry);
    return newSet;
}

// ARVN

ARVN::ARVN(Unit** unitArray, int size, string name, BattleField* battleField)
    : Army(unitArray, size, name, battleField) {
}

void ARVN::fight(Army* enemy, bool defense) {
    if (!defense) {
        this->unitList->reduceQuantity(0.2);
        this->reloadScore();
        Node* cursor = this->unitList->getHead();
        while (cursor != nullptr) {
            Node* nextCursor = cursor->next;
            if (cursor->unit->getQuantity() == 1) {
                if (dynamic_cast<Infantry*>(cursor->unit)) unitList->setInfantryCount(unitList->getInfantryCount() - 1);
                else if (dynamic_cast<Vehicle*>(cursor->unit)) unitList->setVehicleCount(unitList->getVehicleCount() - 1);
                cursor->selfDestruct(this->unitList->getHead());
                this->reloadScore(); // KEEPME
            }
            cursor = nextCursor;
        }
    }
}

string ARVN::str() const {
    if (battleField) {
        stringstream ss;
        ss<<"ARVN["
        <<"LF="<<LF
        <<",EXP="<<EXP
        <<",unitList="<<unitList->str()
        <<",battleField="<<battleField->str()
        <<']';
        return ss.str();
    }
    else {
        stringstream ss;
        ss<<"ARVN["
        <<"LF="<<LF
        <<",EXP="<<EXP
        <<",unitList="<<unitList->str()
        <<",battleField="
        <<']';
        return ss.str();
    }
}

// UNITLIST

bool UnitList::isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool UnitList::isSpecialNumber(int n, int k) {
    if (n <= 0) return false;
    while (n > 0) {
        int remainder = n % k;
        if (remainder > 1) {
            return false;
        }
        n /= k;  
    }
    return true;
}

UnitList::UnitList(const UnitList& other) { 
    this->infantryCount = 0;
    this->vehicleCount = 0;
    this->head = nullptr;
    this->capacity = other.capacity;
    Node* cursor = other.head;
    while (cursor != nullptr) {
        this->insert(cursor->unit);
        cursor = cursor->next;
    }
}

UnitList::UnitList(int S) : infantryCount(0), vehicleCount(0)
{
    head = nullptr;
    this->S = S;
    size = 0;
    bool isSpecial = false;
    for (int i = 3; i < 10; i += 2) {
        if (isPrime(i) && isSpecialNumber(S, i)) {
            isSpecial = true;
        }
    }
    if (isSpecial) capacity = 12;
    else capacity = 8;
}

bool UnitList::insert(Unit *unit)
{
    if (unit == nullptr) return false;
    if (head == nullptr) {
        head = new Node(unit);
        size++;
        if (Infantry* infantry = dynamic_cast<Infantry*>(unit)) infantryCount++;
        else if (Vehicle* vehicle = dynamic_cast<Vehicle*>(unit)) vehicleCount++;
        return true;
    }

    if (Infantry* infantry = dynamic_cast<Infantry*>(unit)) {
        if (isContain(infantry->getInfantryType())) {
            Node* cursor = head;
            while (cursor != nullptr) {
                Infantry* temp = dynamic_cast<Infantry*>(cursor->unit);
                if (temp && temp->getInfantryType() == infantry->getInfantryType()) {
                    if (temp == unit) return false;
                    temp->setWeight(max(infantry->getWeight(), temp->getWeight()));
                    temp->setQuantity(infantry->getQuantity() + temp->getQuantity());
                    temp->getAttackScore();
                    return false;
                }
                cursor = cursor->next;
            }
        }
        else {
            if (size >= capacity) {
                return false;
            }
            Node* newNode = new Node(infantry, head);
            head = newNode;
            size++;
            infantryCount++;
            return true;
        }
    }
    else if (Vehicle* vehicle = dynamic_cast<Vehicle*>(unit)) {
        if (isContain(vehicle->getVehicleType())) {
            Node* cursor = head;
            while (cursor != nullptr) {
                Vehicle* temp = dynamic_cast<Vehicle*>(cursor->unit);
                if (temp && temp->getVehicleType() == vehicle->getVehicleType()) {
                    if (temp == unit) return false;
                    temp->setWeight(max(vehicle->getWeight(), temp->getWeight()));
                    temp->setQuantity(vehicle->getQuantity() + temp->getQuantity());
                    temp->getAttackScore();
                    return false;
                }
                cursor = cursor->next;
            }
        }
        else {
            if (size >= capacity) {return false;}
            Node* cursor = head;
            while (cursor->next != nullptr) {
                cursor = cursor->next;
            }
            cursor->next = new Node(vehicle);
            size++;
            vehicleCount++;
            return true;
        }
    }
    return false;
}

bool UnitList::isContain(VehicleType vehicleType)
{
    Node* cursor = head;
    while (cursor != nullptr) {
        if (Vehicle* vehicle = dynamic_cast<Vehicle*>(cursor->unit)) {
            if (vehicle->getVehicleType() == vehicleType) {
                return true;
            }
        }
        cursor = cursor->next;
    }
    return false;
}

bool UnitList::isContain(InfantryType infantryType)
{
    Node* cursor = head;
    while (cursor != nullptr) {
        if (Infantry* infantry = dynamic_cast<Infantry*>(cursor->unit)) {
            if (infantry->getInfantryType() == infantryType) {
                return true;
            }
        }
        cursor = cursor->next;
    }
    return false;
}

string UnitList::str() const
{
    stringstream ss;
    ss<<"UnitList[count_vehicle="<<vehicleCount
    <<";count_infantry="<<infantryCount;
    
    if (head == nullptr) {
        ss<<']';
        return ss.str();
    }
    else {
        ss<<";";
        Node* cursor = head;
        while (cursor != nullptr) {
            if (Vehicle* vehicle = dynamic_cast<Vehicle*>(cursor->unit)) {
                ss<<vehicle->str()<<',';
            }
            else if (Infantry* infantry = dynamic_cast<Infantry*>(cursor->unit)) {
                ss<<infantry->str()<<',';
            }
            cursor = cursor->next;
        }
        string result = ss.str();
        if (result[result.length()-1] == ',') {
            result = result.substr(0, result.length()-1);
        }
        result += ']';
        return result;
    }    
}

void UnitList::frontInsert(Unit* unit) {
    Node* newNode = new Node(unit);
    newNode->next = head;
    head = newNode;
    if (dynamic_cast<Vehicle*>(unit)) vehicleCount++;
    else if (dynamic_cast<Infantry*>(unit)) infantryCount++;
    updateSize();
}

UnitList* UnitList::shallowReverseCopy() const {
    UnitList* newUnitList = new UnitList(S);
    Node* cursor = head;
    while (cursor != nullptr) {
        newUnitList->frontInsert(cursor->unit);
        cursor = cursor->next;
    }
    return newUnitList;
}


Node *&UnitList::getHead() {return head;}

void UnitList::reduceWeight(double percentage) {
    Node* cursor = head;
    while (cursor != nullptr) {
        cursor->unit->setWeight(ceil(cursor->unit->getWeight() * (1 - percentage)));
        cursor = cursor->next;
    }
}


void UnitList::setVehicleCount(int vehicleCount) {
    this->vehicleCount = vehicleCount;
    this->updateSize();
}
void UnitList::setInfantryCount(int infantryCount) {
    this->infantryCount = infantryCount;
    this->updateSize();
}
int UnitList::getVehicleCount() const {return vehicleCount;}
int UnitList::getInfantryCount() const {return infantryCount;}
void UnitList::updateSize() {size = vehicleCount + infantryCount;}
void UnitList::reduceQuantity(double percentage) {
    Node* cursor = head;
    while (cursor != nullptr) {
        cursor->unit->setQuantity(ceil(cursor->unit->getQuantity() * (1 - percentage)));
        cursor = cursor->next;
    }
}

int UnitList::getCapacity() const {return capacity;}
void UnitList::setCapacity(int capacity) {this->capacity = capacity;}


void Node::selfDestruct(Node*& head) {
    if (head == nullptr) return;
    if (head == this) {
        head = head->next;
        delete this;
        return;
    }
    
    Node* cursor = head;
    while (cursor->next != nullptr && cursor->next != this) {
        cursor = cursor->next;
    }
    
    if (cursor->next == this) {
        cursor->next = this->next;
        delete this;
    }
    else {
        throw std::invalid_argument("Node not found in the list");
    }
}

void UnitList::deleteInfantry(InfantryType infantryType) {
    Node* cursor = head;
    while (cursor != nullptr) {
        if (Infantry* infantry = dynamic_cast<Infantry*>(cursor->unit)) {
            if (infantry->getInfantryType() == infantryType) {
                cursor->selfDestruct(head);
                return;
            }
        }
        cursor = cursor->next;
    }
}

void UnitList::deleteVehicle(VehicleType vehicleType) {
    Node* cursor = head;
    while (cursor != nullptr) {
        if (Vehicle* vehicle = dynamic_cast<Vehicle*>(cursor->unit)) {
            if (vehicle->getVehicleType() == vehicleType) {
                cursor->selfDestruct(head);
                return;
            }
        }
        cursor = cursor->next;
    }
}


UnitList::~UnitList() {
    Node* cursor = head;
    while (cursor != nullptr) {
        Node* nextNode = cursor->next;
        cursor->selfDestruct(head);
        cursor = nextNode;
    }
}

// POSITION

Position::Position(int r, int c) : r(r), c(c) {}
Position::Position(const string &str_pos) {
    sscanf(str_pos.c_str(), "(%d, %d)", &r, &c);
}
int Position::getRow() const { return r; }
int Position::getCol() const { return c; }
void Position::setRow(int r) { this->r = r; }
void Position::setCol(int c) { this->c = c; }
string Position::str() const {
    return '(' + to_string(r) + ',' + to_string(c) + ')';
}

// TERRAIN ELEMENT

double TerrainElement::distance(const Position& pos1, const Position& pos2) {
    int rowDiff = pos1.getRow() - pos2.getRow();
    int colDiff = pos1.getCol() - pos2.getCol();
    return (sqrt(double(rowDiff * rowDiff + colDiff * colDiff)));
}
int TerrainElement::myCeil(double value) {
    double diff = abs(value - round(value));
    return (diff < 1e-9) ? round(value) : ceil(value);
}


TerrainElement::TerrainElement(Position pos) : pos(pos)
{}

TerrainElement::~TerrainElement() {
    
}

void Road::getEffect(Army *army) {
    if (!army) return;
}

void Mountain::getEffect(Army *army) {
    if (!army) return;
    if (dynamic_cast<LiberationArmy*>(army)) {
        Node* cursor = army->getUnitList()->getHead();
        while (cursor != nullptr) {
            if (distance(this->pos, cursor->unit->getCurrentPosition()) <= 2 && dynamic_cast<Infantry*>(cursor->unit)) {
                army->setEXP(myCeil(army->getEXP() + cursor->unit->getStaticAttackScore() * 30.0/100.0));
            }
            else if (distance(this->pos, cursor->unit->getCurrentPosition()) <= 2 && dynamic_cast<Vehicle*>(cursor->unit)) {
                army->setLF(myCeil(army->getLF() - cursor->unit->getStaticAttackScore() * 10.0/100.0));
            }
            cursor = cursor->next;
        }
    }
    else if (dynamic_cast<ARVN*>(army)) {
        Node* cursor = army->getUnitList()->getHead();
        while (cursor != nullptr) {
            if (distance(this->pos, cursor->unit->getCurrentPosition()) <= 4 && dynamic_cast<Infantry*>(cursor->unit)) {
                army->setEXP(myCeil(army->getEXP() + cursor->unit->getStaticAttackScore() * 20.0/100.0));
            }
            else if (distance(this->pos, cursor->unit->getCurrentPosition()) <= 4 && dynamic_cast<Vehicle*>(cursor->unit)) {
                army->setLF(myCeil(army->getLF() - cursor->unit->getStaticAttackScore() * 5.0/100.0));
            }
            cursor = cursor->next;
        }
    }
}

void River::getEffect(Army *army) {
    if (!army) return;
    Node* cursor = army->getUnitList()->getHead();
    while (cursor != nullptr) {
        if (distance(this->pos, cursor->unit->getCurrentPosition()) <= 2 && dynamic_cast<Infantry*>(cursor->unit)) {
            cursor->unit->setAttackScore(myCeil(cursor->unit->getStaticAttackScore() * 0.9));
        }
        cursor = cursor->next;
    }
}

void Urban::getEffect(Army *army) {
    if (!army) return;
    if (dynamic_cast<LiberationArmy*>(army)) {
        Node* cursor = army->getUnitList()->getHead();
        while (cursor != nullptr) {
            if (Infantry* infantry = dynamic_cast<Infantry*>(cursor->unit)) {
                double unitDistance = distance(this->pos, infantry->getCurrentPosition());
                if ((unitDistance <= 5 && unitDistance != 0.0) && (infantry->getInfantryType() == SPECIALFORCES || infantry->getInfantryType() == REGULARINFANTRY)) {
                    infantry->setAttackScore(myCeil(infantry->getStaticAttackScore() + infantry->getStaticAttackScore() * 2 / unitDistance));
                }
            }   
            else if (Vehicle* vehicle = dynamic_cast<Vehicle*>(cursor->unit)) {
                double unitDistance = distance(this->pos, vehicle->getCurrentPosition());
                if (unitDistance <= 2 && vehicle->getVehicleType() == ARTILLERY) {
                    vehicle->setAttackScore(myCeil(vehicle->getStaticAttackScore() * 0.5));
                }
            }
            cursor = cursor->next;
        }
    }
    else if (dynamic_cast<ARVN*>(army)) {
        Node* cursor = army->getUnitList()->getHead();
        while (cursor != nullptr) {
            if (Infantry* infantry = dynamic_cast<Infantry*>(cursor->unit)) {
                double unitDistance = distance(this->pos, infantry->getCurrentPosition());
                if ((infantry->getInfantryType() == REGULARINFANTRY) && (unitDistance <= 3 && unitDistance != 0.0)) {
                    infantry->setAttackScore(myCeil(infantry->getStaticAttackScore() + infantry->getStaticAttackScore() * 3.0 / (2.0 * unitDistance)));    
                }
            }
            cursor = cursor->next;
        }
    }
}

void Fortification::getEffect(Army *army) {
    if (!army) return;
    if (dynamic_cast<LiberationArmy*>(army)) {
        Node* cursor = army->getUnitList()->getHead();
        while (cursor != nullptr) {
            if (distance(this->pos, cursor->unit->getCurrentPosition()) <= 2) {
                cursor->unit->setAttackScore(myCeil(cursor->unit->getStaticAttackScore() * 0.8));
            }
            cursor = cursor->next;
        }
    }
    else if (dynamic_cast<ARVN*>(army)) {
        Node* cursor = army->getUnitList()->getHead();
        while (cursor != nullptr) {
            if (distance(this->pos, cursor->unit->getCurrentPosition()) <= 2) {
                cursor->unit->setAttackScore(myCeil(cursor->unit->getStaticAttackScore() * 1.2));
            }
            cursor = cursor->next;
        }
    }
}

void SpecialZone::getEffect(Army *army) {
    if (!army) return;
    Node* cursor = army->getUnitList()->getHead();
    while (cursor != nullptr) {
        if (distance(this->pos, cursor->unit->getCurrentPosition()) <= 1) {
            cursor->unit->setAttackScore(0);
        }
        cursor = cursor->next;
    }
}

// BATTLEFIELD

BattleField::BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                         const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                         const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone)
    : n_rows(n_rows), n_cols(n_cols)
{
    terrain = new TerrainElement**[n_rows];
    for (int i = 0; i < n_rows; i++) {
        terrain[i] = new TerrainElement*[n_cols];
        for (int j = 0; j < n_cols; j++) {
            terrain[i][j] = nullptr;
        }
    }
    for (int i = 0; i < arrayForest.size(); i++) {
        if (arrayForest[i]->getRow() < 0 || arrayForest[i]->getRow() >= n_rows || arrayForest[i]->getCol() < 0 || arrayForest[i]->getCol() >= n_cols) continue;
        if (terrain[arrayForest[i]->getRow()][arrayForest[i]->getCol()] != nullptr) continue;
        terrain[arrayForest[i]->getRow()][arrayForest[i]->getCol()] = new Mountain(*arrayForest[i]);
    }
    for (int i = 0; i < arrayRiver.size(); i++) {
        if (arrayRiver[i]->getRow() < 0 || arrayRiver[i]->getRow() >= n_rows || arrayRiver[i]->getCol() < 0 || arrayRiver[i]->getCol() >= n_cols) continue;
        if (terrain[arrayRiver[i]->getRow()][arrayRiver[i]->getCol()] != nullptr) continue;
        terrain[arrayRiver[i]->getRow()][arrayRiver[i]->getCol()] = new River(*arrayRiver[i]);
    }
    for (int i = 0; i < arrayFortification.size(); i++) {
        if (arrayFortification[i]->getRow() < 0 || arrayFortification[i]->getRow() >= n_rows || arrayFortification[i]->getCol() < 0 || arrayFortification[i]->getCol() >= n_cols) continue;
        if (terrain[arrayFortification[i]->getRow()][arrayFortification[i]->getCol()] != nullptr) continue;
        terrain[arrayFortification[i]->getRow()][arrayFortification[i]->getCol()] = new Fortification(*arrayFortification[i]);
    }
    for (int i = 0; i < arrayUrban.size(); i++) {
        if (arrayUrban[i]->getRow() < 0 || arrayUrban[i]->getRow() >= n_rows || arrayUrban[i]->getCol() < 0 || arrayUrban[i]->getCol() >= n_cols) continue;
        if (terrain[arrayUrban[i]->getRow()][arrayUrban[i]->getCol()] != nullptr) continue;
        terrain[arrayUrban[i]->getRow()][arrayUrban[i]->getCol()] = new Urban(*arrayUrban[i]);
    }
    for (int i = 0; i < arraySpecialZone.size(); i++) {
        if (arraySpecialZone[i]->getRow() < 0 || arraySpecialZone[i]->getRow() >= n_rows || arraySpecialZone[i]->getCol() < 0 || arraySpecialZone[i]->getCol() >= n_cols) continue;
        if (terrain[arraySpecialZone[i]->getRow()][arraySpecialZone[i]->getCol()] != nullptr) continue;
        terrain[arraySpecialZone[i]->getRow()][arraySpecialZone[i]->getCol()] = new SpecialZone(*arraySpecialZone[i]);
    }
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            if (terrain[i][j] == nullptr) {
                terrain[i][j] = new Road(Position(i, j));
            }
        }
    }
}

BattleField::~BattleField() {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0 ; j < n_cols; j++) {
            delete terrain[i][j];
        }
        delete[] terrain[i];
    }
    delete[] terrain;
}

TerrainElement* BattleField::getElement(int r, int c) const {
    if (!(r >= 0 && r < n_rows)) return nullptr;
    if (!(c >= 0 && c < n_cols)) return nullptr;
    return terrain[r][c];
}

string BattleField::str() const {
    stringstream ss;
    ss<<"BattleField[n_rows="<<n_rows
    <<",n_cols="<<n_cols<<']';
    return ss.str();
}

int BattleField::getRows() const {
    return n_rows;
}

int BattleField::getCols() const {
    return n_cols;
}

// CONFIGURATION

Configuration::Configuration(const std::string &filepath) : liberationCount(0), arvnCount(0) {  
    vector<string> data;
    string dataLine;
    ifstream ifs(filepath);
    if (!ifs) {
        return;
    }
    while (getline(ifs, dataLine)) {
        data.push_back(dataLine);
    }
    ifs.close();
    const int DATA_LENGTH = data.size();

    const int MAX_UNIT_SIZE = 100;

    liberationUnits = new Unit*[MAX_UNIT_SIZE];
    ARVNUnits = new Unit*[MAX_UNIT_SIZE];
    
    for (int i = 0; i < DATA_LENGTH; i++) {
        if (data[i].find("NUM_ROWS") != string::npos) {
            string line = noSpaceStr(data[i]);
            size_t equalSignPos = line.find('=');
            if (equalSignPos != string::npos) {
                num_rows = stoi(line.substr(equalSignPos + 1));
            }
        }
        else if (data[i].find("NUM_COLS") != string::npos) {
            string line = noSpaceStr(data[i]);
            size_t equalSignPos = line.find('=');
            if (equalSignPos != string::npos) {
                num_cols = stoi(line.substr(equalSignPos + 1));
            }
        }
        else if (data[i].find("EVENT_CODE") != string::npos) {
            string line = noSpaceStr(data[i]);
            size_t equalSignPos = line.find('=');
            if (equalSignPos != string::npos) {
                string temp = (line.substr(equalSignPos + 1));
                temp = to_string(max(0, stoi(temp)));
                if (temp.size() >= 3) eventCode = max(0, min(99, stoi(temp.substr(temp.size() - 2))));
                else eventCode = max(0, min(99, stoi(temp)));
            }
        }
    }
    for (int i = 0; i < DATA_LENGTH; i++) {
        if (data[i].find("ARRAY_") != string::npos) {
            string line = noSpaceStr(data[i]);
            TerrainType terrainType = ROAD;
            if (line.find("FOREST") != string::npos) terrainType = FOREST;
            else if (line.find("RIVER") != string::npos) terrainType = RIVER;
            else if (line.find("FORTIFICATION") != string::npos) terrainType = FORTIFICATION;
            else if (line.find("URBAN") != string::npos) terrainType = URBAN;
            else if (line.find("SPECIAL_ZONE") != string::npos) terrainType = SPECIAL_ZONE;
            
            int start_value = line.find('[') + 1;
            int end_value = line.find(']');
            string positions = line.substr(start_value, end_value - start_value);
            string coord;
            stringstream ss(positions);
            while (getline(ss, coord, ')')) {
                if (!coord.empty()) {
                    size_t pos = coord.find('(');
                    if (pos != string::npos) {
                        coord = coord.substr(pos + 1);
                    }
                    stringstream pair(coord);
                    int x, y;
                    char ch;
                    pair >> x >> ch >> y;
                    Position* position = new Position(x, y);
                    switch (terrainType) {
                        case FOREST:
                            arrayForest.push_back(position);
                            break;
                        case RIVER:
                            arrayRiver.push_back(position);
                            break;
                        case FORTIFICATION:
                            arrayFortification.push_back(position);
                            break;
                        case URBAN:
                            arrayUrban.push_back(position);
                            break;
                        case SPECIAL_ZONE:
                            arraySpecialZone.push_back(position);
                            break;
                        default: throw "INVALID TYPE";
                    }
                }
            }
        }
        else if (data[i].find("UNIT_LIST=") != string::npos) {
            string line = noSpaceStr(data[i]);
            int start_value = line.find('[') + 1;
            int end_value = line.find(']');
            string units = line.substr(start_value, end_value - start_value);
            stringstream ss(units);
            string token;

            string unitName;
            int quantity, weight;
            int x_pos, y_pos;

            bool booleanExtract = false;

            
            while (getline(ss, token, ')')) {
                if (booleanExtract) {
                    while (!token.empty() && (token[0] == ',' || token[0] == '(' || token[0] == ' ')) {
                        token = token.substr(1);
                    }   

                    bool isARVN = stoi(token);

                    Position pos(x_pos, y_pos);
                    Unit* unit = nullptr;
                    if (isInfantry(unitName)) {
                        unit = new Infantry(quantity, weight, pos, getInfantryType(unitName));
                    }
                    else {
                        unit = new Vehicle(quantity, weight, pos, getVehicleType(unitName));
                    }

                    // FIXME

                    if (isARVN) ARVNUnits[arvnCount++] = unit;
                    else liberationUnits[liberationCount++] = unit;
                    booleanExtract = false;
                }
                else {
                    while (!token.empty() && (token[0] == ',' || token[0] == '(' || token[0] == ' ')) {
                        token = token.substr(1);
                    }
                    int parenStart = token.find('(');
                    if (parenStart == string::npos) continue;
                    unitName = token.substr(0, parenStart);

                    string inside = token.substr(parenStart + 1);
                    stringstream inner(inside);
                    char ch;
                    inner>>quantity>>ch>>weight>>ch>>ch>>x_pos>>ch>>y_pos;
                    booleanExtract = true;
                }
            }
        }
    }
}

Configuration::~Configuration() {
    for (Position* position : arrayForest) {
        delete position;
    }
    
    for (Position* position : arrayRiver) {
        delete position;
    }
    
    for (Position* position : arrayFortification) {
        delete position;
    }
    
    for (Position* position : arrayUrban) {
        delete position;
    }
    
    for (Position* position : arraySpecialZone) {
        delete position;
    }
    
    arrayForest.clear();
    arrayRiver.clear();
    arrayFortification.clear();
    arrayUrban.clear();
    arraySpecialZone.clear();

    for (int i = 0; i < liberationCount; i++) {
        delete liberationUnits[i];
    }

    for (int i = 0; i < arvnCount; i++) {
        delete ARVNUnits[i];
    }

    delete[] liberationUnits;
    delete[] ARVNUnits;
}

string Configuration::str() const {
    stringstream ss;
    ss << "[num_rows=" << num_rows
       << ",num_cols=" << num_cols
       << ",arrayForest=[";

    for (int i = 0; i < arrayForest.size(); i++) {
        ss << arrayForest[i]->str();
        if (i < arrayForest.size() - 1) ss << ",";
    }
    ss << "],arrayRiver=[";

    for (int i = 0; i < arrayRiver.size(); i++) {
        ss << arrayRiver[i]->str();
        if (i < arrayRiver.size() - 1) ss << ",";
    }
    ss << "],arrayFortification=[";

    for (int i = 0; i < arrayFortification.size(); i++) {
        ss << arrayFortification[i]->str();
        if (i < arrayFortification.size() - 1) ss << ",";
    }
    ss << "],arrayUrban=[";

    for (int i = 0; i < arrayUrban.size(); i++) {
        ss << arrayUrban[i]->str();
        if (i < arrayUrban.size() - 1) ss << ",";
    }
    ss << "],arraySpecialZone=[";

    for (int i = 0; i < arraySpecialZone.size(); i++) {
        ss << arraySpecialZone[i]->str();
        if (i < arraySpecialZone.size() - 1) ss << ",";
    }
    ss << "],liberationUnits=[";

    for (int i = 0; i < liberationCount; i++) {
        ss << liberationUnits[i]->str();
        if (i < liberationCount - 1) ss << ",";
    }
    ss << "],ARVNUnits=[";

    for (int i = 0; i < arvnCount; i++) {
        ss << ARVNUnits[i]->str();
        if (i < arvnCount - 1) ss << ",";
    }
    ss << "],eventCode=" << eventCode << ']';

    return ss.str();
}

int Configuration::getLiberationCount() const {return liberationCount;}
int Configuration::getARVNCount() const {return arvnCount;}

bool Configuration::isInfantry(string infantryString) {
    if (infantryString == "SNIPER") return true;
    else if (infantryString == "ANTIAIRCRAFTSQUAD") return true;
    else if (infantryString == "MORTARSQUAD") return true;
    else if (infantryString == "ENGINEER") return true;
    else if (infantryString == "SPECIALFORCES") return true;
    else if (infantryString == "REGULARINFANTRY") return true;
    else return false;
}

InfantryType Configuration::getInfantryType(string infantryString) {
    if (infantryString == "SNIPER") return SNIPER;
    else if (infantryString == "ANTIAIRCRAFTSQUAD") return ANTIAIRCRAFTSQUAD;
    else if (infantryString == "MORTARSQUAD") return MORTARSQUAD;
    else if (infantryString == "ENGINEER") return ENGINEER;
    else if (infantryString == "SPECIALFORCES") return SPECIALFORCES;
    else if (infantryString == "REGULARINFANTRY") return REGULARINFANTRY;
    else throw std::invalid_argument("INVALID INFANTRY TYPE");
}

VehicleType Configuration::getVehicleType(string vehicleString) {
    if (vehicleString == "TRUCK") return TRUCK;
    else if (vehicleString == "MORTAR") return MORTAR;
    else if (vehicleString == "ANTIAIRCRAFT") return ANTIAIRCRAFT;
    else if (vehicleString == "ARMOREDCAR") return ARMOREDCAR;
    else if (vehicleString == "APC") return APC;
    else if (vehicleString == "ARTILLERY") return ARTILLERY;
    else if (vehicleString == "TANK") return TANK;
    else throw std::invalid_argument("INVALID INFANTRY TYPE");
}

string Configuration::noSpaceStr(string str) {
    string result;
    int count = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != ' ') {
            result.push_back(str[i]);
        }
    }
    return result;
}

// HCM CAMPAIGN!!!!!!!!!!!!!!!!

HCMCampaign::HCMCampaign(const string& config_file_path) {
    config = new Configuration(config_file_path);
    battleField = new BattleField(config->getNumRows(), config->getNumCols(), config->getForestPositions(), config->getRiverPositions(), config->getFortificationPositions(), config->getUrbanPositions(), config->getSpecialZonePositions());
    liberationArmy = new LiberationArmy(config->getLiberationUnits(), config->getLiberationCount(), "LIBERATION ARMY", battleField);
    arvnArmy = new ARVN(config->getARVNUnits(), config->getARVNCount(), "ARVN ARMY", battleField);
}

HCMCampaign::~HCMCampaign() {
    delete battleField;
    delete liberationArmy;
    delete arvnArmy;
    delete config;
}

void HCMCampaign::applyTerrainEffects(Army* army) {
    for (int i = 0; i < army->getBattleField()->getRows(); i++) {
        for (int j = 0; j < army->getBattleField()->getCols(); j++) {
            TerrainElement* element = battleField->getElement(i, j);
            if (Road* road = dynamic_cast<Road*>(element)) {
                road->getEffect(army);
            }
            else if (Mountain* mountain = dynamic_cast<Mountain*>(element)) {
                mountain->getEffect(army);
            }
            else if (River* river = dynamic_cast<River*>(element)) {
                river->getEffect(army);
            }
            else if (Fortification* fortification = dynamic_cast<Fortification*>(element)) {
                fortification->getEffect(army);
            }
            else if (Urban* urban = dynamic_cast<Urban*>(element)) {
                urban->getEffect(army);
            }
            else if (SpecialZone* specialZone = dynamic_cast<SpecialZone*>(element)) {
                specialZone->getEffect(army);
            }
        }
    }
}

void HCMCampaign::deleteRemains(Army* army, int scoreThreshold) {
    Node* cursor = army->getUnitList()->getHead();
    while (cursor != nullptr) {
        Node* nextCursor = cursor->next;
        if (dynamic_cast<Infantry*>(cursor->unit) && cursor->unit->getStaticAttackScore() <= scoreThreshold) {
            cursor->selfDestruct(army->getUnitList()->getHead());
            army->getUnitList()->setInfantryCount(army->getUnitList()->getInfantryCount() - 1);
        }
        else if (dynamic_cast<Vehicle*>(cursor->unit) && cursor->unit->getStaticAttackScore() <= scoreThreshold) {
            cursor->selfDestruct(army->getUnitList()->getHead());
            army->getUnitList()->setVehicleCount(army->getUnitList()->getVehicleCount() - 1);
        }
        cursor = nextCursor;
    }
    army->reloadScore();
}

void HCMCampaign::run() {
    if (config->getEventCode() < 75) {
        // lib attack
        // arvn denfense
        applyTerrainEffects(liberationArmy);
        applyTerrainEffects(arvnArmy);
        
        liberationArmy->fight(arvnArmy, 0);
        arvnArmy->fight(liberationArmy, 1);

        deleteRemains(liberationArmy, 5);
        deleteRemains(arvnArmy, 5);
    }
    else if (config->getEventCode() >= 75) {
        // arvn attack
        // lib denfense
        // lib counterattack
        applyTerrainEffects(liberationArmy);
        applyTerrainEffects(arvnArmy);

        arvnArmy->fight(liberationArmy, 0);
        liberationArmy->fight(arvnArmy, 1);

        liberationArmy->fight(arvnArmy, 0);
        arvnArmy->fight(liberationArmy, 1);

        deleteRemains(liberationArmy, 5);
        deleteRemains(arvnArmy, 5);
    }
}

string HCMCampaign::printResult() {
    stringstream ss;
    ss<<"LIBERATIONARMY[LF="<<liberationArmy->getLF()
    <<",EXP="<<liberationArmy->getEXP()
    <<"]-ARVN[LF="<<arvnArmy->getLF()
    <<",EXP="<<arvnArmy->getEXP()
    <<']';
    return ss.str();
}