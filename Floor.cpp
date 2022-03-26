/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;


int Floor::tick(int currentTime) {
	int count = 0;
	int indicesToRemove[MAX_PEOPLE_PER_FLOOR] = { 0 };
	for (int i = 0; i < numPeople; ++i) {
		if (people[i].tick(currentTime)) {
			indicesToRemove[count] = i;
			count++;
		}
	}
	removePeople(indicesToRemove, count);

    return count;
}

void Floor::addPerson(Person newPerson, int request) {
	if (numPeople < MAX_PEOPLE_PER_FLOOR) {
		people[numPeople] = newPerson;
		numPeople++;
	}
	if (request > 0) {
		hasUpRequest = true;
	}
	else {
		hasDownRequest = true;
	}
	return;
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
	/*int newIndices = 0;
	int countIndices = numPeople - 1;
	Person holdPerson;
	for (int i = 0; i < numPeople; ++i) {
		for (int j = 0; j < numPeopleToRemove; ++j) {
			if (i == indicesToRemove[j]) {
				for (int k = i; k < numPeople - 1; ++k) {
					people[k] = people[k + 1];
				}
				people[countIndices] = holdPerson;
				for (int k = 0; k < MAX_PEOPLE_PER_FLOOR; ++k) {
					indicesToRemove[k]--;
				}

				
			}
		}
		
	}
	numPeople -= numPeopleToRemove;
	resetRequests();*/
	for (int i = 0; i < numPeople; ++i) {
		for (int j = 0; j < numPeopleToRemove; ++j) {
			if (i == indicesToRemove[j]) {
				for (int k = i; k < numPeople; ++k) {
					people[k] = people[k + 1];
				}
				for (int k = 0; k < numPeopleToRemove; ++k) {
					indicesToRemove[k]--;
				}
			}
		}

	}
	numPeople = numPeople - numPeopleToRemove;
	resetRequests();
	
}

void Floor::resetRequests() {
	hasUpRequest = false;
	hasDownRequest = false;
    for (int i = 0; i < numPeople; ++i){
		if (people[i].getCurrentFloor() > people[i].getTargetFloor()) {
			hasDownRequest = true;
		}
	}
	for (int i = 0; i < numPeople; ++i) {
		if (people[i].getCurrentFloor() < people[i].getTargetFloor()) {
			hasUpRequest = true;
		}
	}
} 

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
