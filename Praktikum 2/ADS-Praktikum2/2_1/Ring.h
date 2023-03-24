/*************************************************
* ADS Praktikum 2.1
* Ring.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .h
#pragma once
#include<string>
#include "catch.h"
#include"RingNode.h"

class Ring{
	
	private:
		// Ihr Code hier:	
		int countNodes;
		RingNode* anker;
		//
		////////////////////////////////////
	public:
		// Ihr Code hier:
		Ring();
		void addNewNode( std::string dsc, std::string neu);
		bool search(std::string txt);
		void print();
		int Hilfprint(RingNode* ptr);

		//
		////////////////////////////////////
		// friend Funktionen müssen unangetastet bleiben! 
		friend RingNode * get_anker(Ring& r);
		friend int get_countNodes(Ring& r);
};
