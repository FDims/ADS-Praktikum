#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size, double threshold,int methode) 
{
	collisionCount = 0;
	kollisionsstrategie = methode;
	elements = 0;
	hashTable = new vector<int>;
	hashTable->resize(size, -1);
	this->size = size;
	this->threshold_rehashing = threshold;
}

HashTable::~HashTable()
{
	delete hashTable;
}

// Berechnung des Hashwertes mit quadr. Sondieren
int HashTable::hashValue(int item) 
{
	int index = -1;
	int i = 0;
	if (kollisionsstrategie == 1) {
		// Lineares Sondieren
		while (hashTable->at((item + i) % size) != -1) {
			i++;
			collisionCount++;
		}
		index = (item + i) % size;
	}
	else if (kollisionsstrategie == 2) {
		// Quadratisches Sondieren (standardmäßig)
		while (hashTable->at(((item + i * i) % size)) != -1) {
			i++;
			collisionCount++;
		}

		index = ((item + i * i) % size);
	}
	else if (kollisionsstrategie == 3) {
		// Doppeltes Hashing
		int R = size - 1;
		bool prime = 0;
		while (!prime && R > 1) {
			for (int i = 2; i < R / 2; i++) {
				if (R % i == 0) {
					prime = 0;
					break;
				}
				else
					prime = 1;
			}
			R--;
		}
		while (hashTable->at((item + (i * (R - (item % R)))) % size) != -1) {
			i++;
			collisionCount++;
		}
		index = (item + (i * (R - (item % R)))) % size; 
	}
	
	return index;
}
	

void HashTable::rehashing()
{
	int M_neu = get_next_Prime(2 * size), oldsize = size;
	size = M_neu;
	collisionCount = 0;
	elements = 0;
	vector<int> tmp(oldsize,-1);
	for (int i = 0; i < oldsize; i++) {
		tmp.at(i) = hashTable->at(i);
	}
	delete hashTable;
	hashTable = new vector<int>;
	hashTable->resize(M_neu, -1);
	
	for (int i = 0; i < oldsize; i++) {
		if (tmp.at(i) != -1)
			insert(tmp.at(i));
	}
}

int HashTable::insert(int item)
{
	hashTable->at(hashValue(item)) = item;
	elements++;
	if (double(elements / double(size)) >= threshold_rehashing) {
		rehashing();
	}

	
	return 0;
}


int HashTable::at(int i) 
{
	return hashTable->at(i);
}

int HashTable::getCollisionCount() 
{
	return this->collisionCount;
}

int HashTable::getSize() 
{
	return this->size;
}

int HashTable::getElements() 
{
	return this->elements;
}

int get_next_Prime(int x)
{
	x = x + 1;
	bool found = true;
	while (true)
	{
		found = true;
		for (int i = 2; i <= sqrt(x); i++)
		{
			if (x % i == 0)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return x;
		}
		x += 1;
	}
}

