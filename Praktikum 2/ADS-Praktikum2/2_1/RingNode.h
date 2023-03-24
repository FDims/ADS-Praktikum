/*************************************************
* ADS Praktikum 2.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>

class RingNode{
	
private:
	// Ihr Code hier:
	int age;
	std::string desc, data;
	RingNode* next;
	//	
public:
	// Ihr Code hier:
	RingNode();
	RingNode(int alt, std::string dsc, std::string neu);
	int getAge();
	void setAge(int alt);
	std::string getDescription();
	void setDescription(std::string dsc);
	std::string getData();
	void setData(std::string neu);
	RingNode* getNext();
	void setNext(RingNode* nxt);

	//
};
