/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Person.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;
const int ASCII_INT_VAL = 48;
const int ASCII_TENS_INT_VAL = 39;

Person::Person(string inputString) : Person() {
    int length = inputString.length();
    if (length == 7) {
        turn = inputString[0] - ASCII_INT_VAL;
        currentFloor = inputString[2] - ASCII_INT_VAL;
        targetFloor = inputString[4] - ASCII_INT_VAL;
        angerLevel = inputString[6] - ASCII_INT_VAL;
    }
    else {
        turn = inputString[0] - ASCII_TENS_INT_VAL + inputString[1] - ASCII_INT_VAL;
        currentFloor = inputString[3] - ASCII_INT_VAL;
        targetFloor = inputString[5] - ASCII_INT_VAL;
        angerLevel = inputString[7] - ASCII_INT_VAL;
    }
    

}

bool Person::tick(int currentTime) {
    if ((currentTime % TICKS_PER_ANGER_INCREASE) == 0) {
        angerLevel++;
    }
    if (angerLevel == MAX_ANGER) {
        return true;
    }
    else {
        return false;
    }
}

void Person::print(ostream &outs) {    
    //TODO: Implement print
    outs << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {    
    return currentFloor;
}

int Person::getTargetFloor() const {    
    return targetFloor;
}

int Person::getAngerLevel() const {    
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
