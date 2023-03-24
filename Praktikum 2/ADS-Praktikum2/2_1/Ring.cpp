/*************************************************
* ADS Praktikum 2.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .cpp
#include "Ring.h"
#include <iostream>

// Ihr Code hier:
Ring::Ring() {
	anker = nullptr;
	anker->setNext(anker);
	countNodes = 0;
}

void Ring::addNewNode(std::string dsc, std::string neu) {
	RingNode* nData = new RingNode(0, dsc, neu);
	if (anker == 0) {
		countNodes = 1;
		anker = nData;
		anker->setNext(anker);
	}
	else {
		if (countNodes < 6) {
			nData->setNext(anker->getNext());
			anker->setNext(nData);
			anker = nData;
			countNodes++;
		}
		else {
			RingNode* ptr = anker->getNext();
			nData->setNext(ptr->getNext());
			anker->setNext(nData);
			anker = nData;
			delete ptr;
		}
		RingNode* ptr = anker->getNext();
		for (int i = 1; i < countNodes; i++) {
			ptr->setAge(ptr->getAge()+1);
			ptr = ptr->getNext();
		}
	}
}
bool Ring::search(std::string txt) {
	if (anker != 0) {
		RingNode* ptr = anker;
		for (int i = 0; i < countNodes; i++) {
			if (ptr->getData() == txt) {
				std::cout << "Gefunden in Backup: Alter " << ptr->getAge()
					<< ", Beschreibung: " << ptr->getDescription() << ", Daten: " << ptr->getData() << "\n\n";
				return 1;
			}
			else {
				ptr = ptr->getNext();
			}
		}
	}
	std::cout << "Datensatz konnte nicht gefunden werden.\n";
	return 0;
}
void Ring::print() {
	if (anker != 0) {
		Hilfprint(anker->getNext());
	}
	else
		std::cout << "Backup ist Leer";
}
int Ring::Hilfprint(RingNode* ptr) {
	int i = 0;
	if (ptr != anker)
		i=Hilfprint(ptr->getNext())+1;
	
		std::cout << "Alter: " << ptr->getAge() << ", Beschreibung: " << ptr->getDescription()
			<< ", Daten: " << ptr->getData() << "\n";
		if(i<5)
			std::cout << "--------------------------\n";
	return i;
}

//
////////////////////////////////////
