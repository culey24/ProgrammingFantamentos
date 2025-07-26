// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_HCM_CAMPAIGN_H_
#define _H_HCM_CAMPAIGN_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class Unit;
class UnitList;
class Army;
class TerrainElement;

class Vehicle;
class Infantry;

class LiberationArmy;
class ARVN;

class Position;

class Road;
class Mountain;
class River;
class Urban;
class Fortification;
class SpecialZone;

class BattleField;

class HCMCampaign;
class Configuration;

enum VehicleType
{
    TRUCK,//0
    MORTAR,//1
    ANTIAIRCRAFT,//2
    ARMOREDCAR,//3
    APC,//4
    ARTILLERY,//5
    TANK//6
};
// 304
enum InfantryType
{
    SNIPER,//0
    ANTIAIRCRAFTSQUAD,//1
    MORTARSQUAD,//2
    ENGINEER,//3
    SPECIALFORCES,//4
    REGULARINFANTRY//5
};
//56
enum TerrainType
{
    ROAD,
    FOREST,
    RIVER,
    FORTIFICATION,
    URBAN,
    SPECIAL_ZONE
};

struct Node {
    Unit* unit;
    Node* next;
    Node(Unit* unit=nullptr, Node* next=nullptr) : unit(unit), next(next) {}
    void selfDestruct(Node*& head);
};

struct UnitSubset {
    int totalScore;
    vector<Node*> unitSet;
};

// POSITION

class Position
{
private:
    int r, c;

public:
    Position(int r = 0, int c = 0);
    Position(const string &str_pos);
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const;
};

// UNIT

class Unit
{
protected:
    int quantity, weight;
    Position pos;
    int attackScore;

public:
    Unit(int quantity, int weight, Position pos);
    virtual ~Unit();
    virtual int getAttackScore() = 0;
    Position getCurrentPosition() const;
    virtual string str() const = 0;

    
    int getQuantity() const;
    int getWeight() const;

    void setQuantity(int value);
    void setWeight(int value);

    virtual Unit* copy() const = 0;
    int getStaticAttackScore() const;
    void setAttackScore(int value);
    void setPos(Position pos);

    int myCeil(double value);
};

// INFANTRY

class Infantry : public Unit
{
protected:
    InfantryType infantryType;
    static const int BATTLE_YEAR;
public:
    Infantry(int quantity, int weight, Position pos, InfantryType infantryType);
    int getAttackScore() override;
    string str() const override;

    InfantryType getInfantryType();
    void setInfantryType(InfantryType infantryType);

    Unit* copy() const override;
    string getStringInfantryType() const;
    bool isPerfectSquare(int n);
    int sumDigits(int n);
    int computeSingleDigit(int score, int year);
};

// VEHICLE

class Vehicle : public Unit
{
protected:
    VehicleType vehicleType;  
public:
    Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType);
    int getAttackScore() override;
    string str() const override;
    VehicleType getVehicleType();
    void setVehicleType(VehicleType vehicleType);

    Unit* copy() const override;
    string getStringVehicleType() const;
};

// UNITLIST

class UnitList {
private:
    int capacity;
    Node* head;
    int vehicleCount, infantryCount;
    int size;

public:
    UnitList(int capacity);
    ~UnitList();
    bool insert(Unit *unit);
    bool isContain(VehicleType vehicleType);
    bool isContain(InfantryType infantryType);
    string str() const;

    int myCeil(double value);

    UnitList* shallowReverseCopy() const;

    void frontInsert(Unit* unit);
    Node*& getHead();
    void reduceWeight(double percentage);
    int getCapacity() const;
    void setCapacity(int capacity);

    int getVehicleCount() const;
    int getInfantryCount() const;

    void setVehicleCount(int vehicleCount);
    void setInfantryCount(int infantryCount);
    void updateSize();

    void reduceQuantity(double percentage);

    void deleteInfantry(InfantryType infantryType);
    void deleteVehicle(VehicleType vehicleType);

    UnitList(const UnitList& other);
};

// ARMY

class Army {
protected:
    int LF;        
    int EXP;       
    string name;
    BattleField* battleField;
    UnitList *unitList;
public:
    Army(Unit **unitArray, int size, string name, BattleField* battleField);
    virtual ~Army();
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;

    int getLF() const;
    int getEXP() const;
    string getName() const;
    BattleField* getBattleField() const;
    void setLF(int LF);
    void setEXP(int EXP);

    UnitList* getUnitList() const;

    void reloadScore();   
    bool isPrime(int n);
    bool isSpecialNumber(int n, int k);

    int myCeil(double value);
};

// LIBERATIONARMY

class LiberationArmy : public Army
{
public:
    LiberationArmy(Unit **unitArray, int size, string name, BattleField* battleField);
    void fight(Army *enemy, bool defense) override;
    string str() const override;
    void findMinUnitSubset(Node* cursor, int threshold, int currentSum, vector<Node*> currentSet, UnitSubset& bestSubset, bool isInfantry);
    UnitSubset minUnitSubset(Node* head, int threshold, bool isInfantry);
    int ceilFibonacci(int value);
};



//BA QUE

class ARVN : public Army
{
public:
    ARVN(Unit** unitArray, int size, string name, BattleField* battleField);
    void fight(Army* enemy, bool defense=false) override;
    string str() const;
};

//CLASS TerrainElement

class TerrainElement {
protected:
    Position pos;
public:
    TerrainElement(Position);
    virtual ~TerrainElement();
    virtual void getEffect(Army *army) = 0;
    double distance(const Position& pos1, const Position& pos2);
    int myCeil(double value);
};

class Road : public TerrainElement {
public:
    Road(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
};

class Mountain : public TerrainElement {
public:
    Mountain(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
};

class River : public TerrainElement {
public:
    River(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
};

class Urban : public TerrainElement {
public:
    Urban(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
};

class Fortification : public TerrainElement {
public:
    Fortification(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
};

class SpecialZone : public TerrainElement {
public:
    SpecialZone(Position pos) : TerrainElement(pos) {}
    void getEffect(Army *army);
};

// BATTLEFIELD

class BattleField {
private:
    int n_rows, n_cols;
    TerrainElement ***terrain;
public:
    BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone);
    ~BattleField();
    TerrainElement* getElement(int r, int c) const;
    string str() const;

    int getRows() const;
    int getCols() const;
};

// CONFIG

class Configuration {
private:
    int num_rows;
    int num_cols;
    vector<Position*> arrayForest;
    vector<Position*> arrayRiver;
    vector<Position*> arrayFortification;
    vector<Position*> arrayUrban;
    vector<Position*> arraySpecialZone;
    // Các mảng đơn vị quân được để trống (stub) trong phần hiện thực mẫu
    Unit** liberationUnits;
    Unit** ARVNUnits;
    int liberationCount, arvnCount;
    int eventCode;
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
    
    int getNumRows() const { return num_rows; }
    int getNumCols() const { return num_cols; }
    const vector<Position*>& getForestPositions() const { return arrayForest; }
    const vector<Position*>& getRiverPositions() const { return arrayRiver; }
    const vector<Position*>& getFortificationPositions() const { return arrayFortification; }
    const vector<Position*>& getUrbanPositions() const { return arrayUrban; }
    const vector<Position*>& getSpecialZonePositions() const { return arraySpecialZone; }
    int getEventCode() const { return eventCode; }
    Unit**& getLiberationUnits() { return liberationUnits; }
    Unit**& getARVNUnits() { return ARVNUnits; }

    bool isInfantry(string infantryString);

    InfantryType getInfantryType(string infantryString);
    VehicleType getVehicleType(string vehicleString);

    string noSpaceStr(string str);

    int getLiberationCount() const;
    int getARVNCount() const;
};

// HCMCAMPAIGNNNNNNNNNNNNNNNNNNN

class HCMCampaign {
private:
    Configuration* config;
    BattleField* battleField;
    LiberationArmy* liberationArmy;
    ARVN* arvnArmy;
public:
    HCMCampaign(const string & config_file_path);
    ~HCMCampaign();
    void run();
    string printResult();
    void applyTerrainEffects(Army* army);
    void deleteRemains(Army* army, int scoreThreshold);
};
#endif