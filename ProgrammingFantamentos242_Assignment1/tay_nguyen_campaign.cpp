#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;         
const int MAX_LINE_LENGTH = 100;

// Defined function, i put the detailed code at the end
int myCeil(double num);
bool isNum(char ch);
bool isLower(char ch);
bool isUpper(char ch);
string lowercase(string str);
string decodeValidChecker(string str);


// Task 0: Read input file
bool readFile(
  const string &filename,
  int LF1[], int LF2[],
  int &EXP1, int &EXP2,
  int &T1, int &T2, int &E)
{
  char data[MAX_LINES][MAX_LINE_LENGTH];
  int numLines = 0;

  ifstream ifs(filename);
  if (!ifs.is_open())
  {
      return false;
  }

  while (numLines < MAX_LINES && ifs.getline(data[numLines], MAX_LINE_LENGTH))
  {
      numLines++;
  }
  ifs.close();

  if (numLines < MAX_LINES)
  {
      return false;
  }

  // TODO: Extract values from the `data` array and store them in respective variables
  for (int row = 0; row < MAX_LINES; row++) {
      int i = 0;
      string temp;
      int count = 0;
      while (data[row][i] != '\0') {
          if (isNum(data[row][i]) || data[row][i] == '-') {
              temp += data[row][i];
          }
          else if (!temp.empty()) {
              switch (row) {
                  case 0:
                      LF1[count] = stoi(temp);
                      LF1[count] = max(0,min(1000,LF1[count]));
                      count++;
                      temp.clear();
                      break;
                  case 1:
                      LF2[count] = stoi(temp);
                      LF2[count] = max(0,min(1000,LF2[count]));
                      count++;
                      temp.clear();
                      break;
                  case 2:
                      if (count == 0) {
                          EXP1 = stoi(temp);
                          EXP1 = max(0,min(600,EXP1));
                      } 

                      else if (count == 1) {
                          EXP2 = stoi(temp);
                          EXP2 = max(0,min(600,EXP2));
                      }
                      count++;
                      temp.clear();
                      break;
                  case 3:
                      if (count == 0) {
                          T1 = stoi(temp);
                          T1 = max(0,min(T1,3000));
                      } 
                      
                      else if (count == 1) {
                          T2 = stoi(temp);
                          T2 = max(0,min(T2,3000));
                      }
                      count++;
                      temp.clear();
                      break;
                  case 4:
                      E = stoi(temp);
                      E = max(0,min(99,E));
                      count++;
                      temp.clear();
                      break;
              }
          }
          i++;
      }
      if (!temp.empty()) {
          switch (row) {
              case 0:
                  LF1[count] = stoi(temp);
                  LF1[count] = max(0,min(1000,LF1[count]));
                  break;
              case 1:
                  LF2[count] = stoi(temp);
                  LF2[count] = max(0,min(1000,LF2[count]));
                  break;
              case 2:
                  if (count == 0) {
                      EXP1 = stoi(temp);
                      EXP1 = max(0,min(600,EXP1));
                  } else if (count == 1) {
                      EXP2 = stoi(temp);
                      EXP2 = max(0,min(600,EXP2));
                  }
                  break;
              case 3:
                  if (count == 0) {
                      T1 = max(0,min(stoi(temp),3000));
                  } else if (count == 1) {
                      T2 = max(0,min(stoi(temp),3000));
                  }
                  break;
              case 4:
                  E = stoi(temp);
                  E = max(0,min(99,E));
                  break;
          }
      }
  }
  return true;
}

// Task 1
int gatherForces(int LF1[], int LF2[]) {
  // TODO: Implement this function
  int LF1_sum = 0;
  int LF2_sum = 0;
  int weight[17] = {1,2,3,4,5,7,8,9,10,12,15,18,20,30,40,50,70} ;
  for (int i = 0; i < 17; i++) { 
    LF1[i] = max(0,min(1000,LF1[i]));
    LF2[i] = max(0,min(1000,LF2[i])); 
    LF1_sum += LF1[i]*weight[i];
    LF2_sum += LF2[i]*weight[i];
  }
  return LF1_sum + LF2_sum;
}

// Task 2
string determineRightTarget(const string &target) {
  const int NUMBER_OF_TARGET = 8;
  const string target_array[NUMBER_OF_TARGET] = {"Kon Tum",
                                                  "Pleiku",
                                                  "Gia Lai",
                                                  "Buon Ma Thuot",
                                                  "Duc Lap",
                                                  "Dak Lak",
                                                  "National Route 21",
                                                  "National Route 14"};

  int number_array[4];
  string temp;
  int count = 0;
  for (int i = 0; i < target.length(); i++) {
    if (isNum(target[i])) {
      temp += target[i];
    }
    if (i == target.length() - 1 || !isNum(target[i]) ) {
      if (!temp.empty()) {
        number_array[count] = stoi(temp);
        count++;
      }
      temp.clear();
    }
    if (count > 3) {
      return "INVALID";
    }
  }

  if (count == 0) {
    return "INVALID";
  }

  int ID;

  switch (count) {
    case 1:
      ID = number_array[0];
      if (ID >= 3 && ID <= 7) {
        return target_array[ID];
      }
      else if (ID >= 0 && ID <= 2) {
        return "DECOY";
      }
      else {
        return "INVALID";
      }
      break;

    case 2:
      ID = (number_array[0] + number_array[1]) % 5 + 3;
      return target_array[ID];
      break;

    case 3:
      ID = max(number_array[0], max(number_array[1], number_array[2])) % 5 + 3;
      return target_array[ID];
      break;

    default:
      return "INVALID";
      break;
  }
}

string decodeTarget(const string &message, int EXP1, int EXP2) {
  // we dont want invalid value
  EXP1 = max(0,min(EXP1, 600));
  EXP2 = max(0,min(EXP2, 600));
  
  string result;

  int len = message.length();
  if (EXP1 >= 300 && EXP2 >= 300) {
    //Ceasar cipher metthod
    int shift = (EXP1 + EXP2) % 26;

    for (int i = 0; i < len; i++) {
      if (!isUpper(message[i]) && !isLower(message[i]) && !isNum(message[i]) && (message[i] != ' ')) {
        return "INVALID";
      }

      else if (isLower(message[i])) {
        result += (message[i] - 'a' + shift) % 26 + 'a';
      }

      else if (isUpper(message[i])) {
        result += (message[i] - 'A' + shift) % 26 + 'A';
      }

      else {
        result += message[i]; // this case apply when message[i] == '<spacebar>' or numbers
      }
    }
  }
  else {
    // string reverse method
    for (int i = 0; i < len; i++) {
      result += message[len - 1 - i];
    }
  }
  return decodeValidChecker(result);
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E) {
  // avoid invalid values
  T1 = max(0,min(3000,T1));
  T2 = max(0,min(3000,T2));

  E = max(0,min(99,E));

  LF1 = max(0,LF1);
  LF2 = max(0,LF2);

  EXP1 = max(0,min(EXP1, 600));
  EXP2 = max(0,min(EXP2, 600));

  if (E == 0) {
    double deltaT1 = (double(LF1)/(LF1 + LF2) * (T1 + T2)) * (1 + (EXP1 - EXP2)/100.0);
    double deltaT2 = (T1 + T2) - deltaT1;

    T1 = myCeil(T1 + deltaT1);
    T2 = myCeil(T2 + deltaT2);

    T1 = max(0,min(3000,T1));
    T2 = max(0,min(3000,T2));
  }

  else if (E >= 1 && E <= 9) {
    int temp = myCeil(T1 - (E * 0.01) * T1);
    T1 = max(0,min(3000, temp));
    temp = myCeil(T2 - (E * 0.005) * T2);
    T2 = max(0,min(3000, temp));
  }

  else if (E >= 10 && E <= 29) {
    T1 += E*50;
    T2 += E*50;
    T1 = max(0,min(T1,3000));
    T2 = max(0,min(T2,3000));
  }

  else if (E >= 30 && E <= 59) {
    int temp = myCeil(T1 + (E * 0.005) * T1);
    T1 = min(3000, temp);
    temp = myCeil(T2 + (E * 0.002) * T2);
    T2 = min(3000, temp);
  }

  else if (E >= 60 && E <= 99); //nothing happened 
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10]) {
  //make sure no invalid value
  T1 = max(0,min(3000,T1));
  T2 = max(0,min(3000,T2));
  EXP1 = max(0,min(EXP1,600));
  EXP2 = max(0,min(EXP2,600));
  LF1 = max(0,LF1);
  LF2 = max(0,LF2);

  double S = (LF1 + LF2) + (EXP1 + EXP2) * 5 + (T1 + T2) * 2;
  
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i % 2 != 0) {
        S = S - (battleField[i][j] * 3.0)/2;
      }
      else {
        S = S - (battleField[i][j] * 2.0)/3;
      }
    }
  }
  return myCeil(S);
}

// Task 5
void swap(int &x, int &y) {
  int temp = x;
  x = y;
  y = temp;
}

void sort(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int n = i + 1; n < size; n++) {
      if (arr[i] > arr[n]) {
        swap(arr[i], arr[n]);
      }
    }
  }
}

int resupply(int shortfall, int supply[5][5]) {
  int arr1D[25];
  int idx = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      arr1D[idx] = supply[i][j];
      idx++;
    }
  }
  sort(arr1D,25);
  int minOfSums = INT_MAX;
  for (int idx1 = 0; idx1 < 21; idx1++) {
    for (int idx2 = idx1 + 1; idx2 < 22; idx2++) {
      for (int idx3 = idx2 + 1; idx3 < 23; idx3++) {
        for (int idx4 = idx3 + 1; idx4 < 24; idx4++) {
          for (int idx5 = idx4 + 1; idx5 < 25; idx5++) {
            int current_sum = arr1D[idx1] + arr1D[idx2] + arr1D[idx3] + arr1D[idx4] + arr1D[idx5];
            if (current_sum < minOfSums && current_sum >= shortfall) {
              minOfSums = current_sum;
            }
          }
        }
      }
    }
  }
  if (minOfSums < shortfall) {
    return -1; // avoid case where shortfall is somehow invalid
  }
  else {
    return minOfSums;
  }
}

// Defined function detail
int myCeil(double num) {
  return ceil(num - 1e-7);
}
// since ceil() function sometimes returns some weird value D:

bool isNum(char ch) {
  return ch >= '0' and ch <= '9';
}

bool isUpper(char ch) {
  return (ch >= 'A' && ch <= 'Z');
}

bool isLower(char ch) {
  return (ch >= 'a' && ch <= 'z');
}

string lowercase(string str) {
  for (int i = 0; i < str.length(); i++) {
    if (isUpper(str[i])) {
      str[i] = str[i] - ('A' - 'a');
    }
  }
  return str;
} 

string decodeValidChecker(string str) {
  const int NUMBER_OF_TARGET = 8;
  const string target_array[NUMBER_OF_TARGET] = {"Kon Tum",
                                                  "Pleiku",
                                                  "Gia Lai",
                                                  "Buon Ma Thuot",
                                                  "Duc Lap",
                                                  "Dak Lak",
                                                  "National Route 21",
                                                  "National Route 14"};
  for (int i = 0; i < 8; i++) {
    if (lowercase(str) == lowercase(target_array[i])) {
      return target_array[i];
    }
  }
  return "INVALID";
}



////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////