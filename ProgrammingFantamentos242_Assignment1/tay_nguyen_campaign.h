/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2025
 * Date: 07.02.2025
 */

#ifndef _TAY_NGUYEN_CAMPAIGN_H_
#define _TAY_NGUYEN_CAMPAIGN_H_

#include "main.h"

bool readFile(
    const string &filename,
    int LF1[], int LF2[],
    int &EXP1, int &EXP2,
    int &T1, int &T2, int &E);

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Task 1: Gather Forces
int gatherForces(int LF1[], int LF2[]);

// Task 2: Deception Strategy
string determineRightTarget(const string &target);
string decodeTarget(const string &message, int EXP1, int EXP2);

// Task 3: Logistics Management
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E);

// Task 4: Attack Planning
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10]);

// Task 5: Resupply
int resupply(int shortfall, int supply[5][5]);

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////

#endif /* _TAY_NGUYEN_CAMPAIGN_H_ */
