/*************************************************
 * ADS Praktikum 2.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iomanip>
#include <iostream>

using namespace std;
////////////////////////////////////
// Ihr Code hier:
Tree::Tree() {
	anker = 0;
	currentNodeChronologicalID = 0;
}

Tree::~Tree() {
	//
}



void Tree::addNode(string N, int Alt, double in, int PC) {
	TreeNode* nData = new TreeNode(Alt + in + PC, currentNodeChronologicalID, N, Alt, in, PC);
	if (anker == 0) {
		anker = nData;
		currentNodeChronologicalID++;
	}
	else {
		currentNodeChronologicalID++;
		TreeNode* ptr = anker;
		TreeNode* prnt = 0;
		do {
			prnt = ptr;
			if (nData->getNodeOrderID() >= ptr->getNodeOrderID())
				ptr = ptr->getRight();
			else
				ptr = ptr->getLeft();
		} while (ptr != 0);
		if (nData->getNodeOrderID() < prnt->getNodeOrderID())
			prnt->setLeft(nData);
		else
			prnt->setRight(nData);
	}
}
bool Tree::deleteNode(int NID) {
	if (anker == 0)//leerer Baum
		return 0;
	if (anker->getNodeOrderID() == NID) {//zu löschende Node ist Würzel
		if (anker->getLeft() == 0 && anker->getRight() == 0) {//Würzel hat keinen Nachfolger
			delete anker;
			anker = 0;
		}
		else if ((anker->getRight() != 0 && anker->getLeft() == 0) || (anker->getRight() == 0 && anker->getLeft() != 0)) {
			//Würzel hat genau einen Nachfolger
			if (anker->getRight() != 0)
				anker = anker->getRight();
			else
				anker = anker->getLeft();
		}
		else if (anker->getRight() != 0 && anker->getLeft() != 0) {//Würzel hat 2 Nachfolgern
			TreeNode* ptr = anker->getRight(), * parent = 0;
			while (ptr->getLeft() != 0) {//Minimalrechts suchen
				parent = ptr;
				ptr = ptr->getLeft();
			}
			if (parent == 0) {//direkt in Rechtenseite des zu löschenden Node
				ptr->setLeft(anker->getLeft());
				delete anker;
				anker = ptr;
			}
			else {
				parent->setLeft(ptr->getRight());
				ptr->setRight(anker->getRight());
				ptr->setLeft(anker->getLeft());
				delete anker;
				anker = ptr;
			}
			return 1;
		}
	}
	else {//kein Würzel
		TreeNode* ptr = anker, * parent = 0;
		while (ptr != 0) {//zu löschende Node suchen
			if (ptr->getNodeOrderID() == NID)
				break;
			parent = ptr;
			if (NID > ptr->getNodeOrderID())
				ptr = ptr->getRight();
			else
				ptr = ptr->getLeft();
		}
		if (ptr == 0)//nicht gefunden
			return 0;
		else {
			if (ptr->getLeft() == 0 && ptr->getRight() == 0) {//hat keinen Nachfolger
				if (ptr == parent->getRight())//lieg rechts Node des Parents
					parent->setRight(0);
				else                //Nachfolger im Links
					parent->setLeft(0);
				delete ptr;
				ptr = 0;
			}
			else if ((ptr->getRight() != 0 && ptr->getLeft() == 0) || (ptr->getRight() == 0 && ptr->getLeft() != 0)) {
				//hat genau einen Nachfolger
				if (ptr == parent->getRight()) {//lieg rechts Node des Parents
					if (ptr->getRight() != 0)//Nachfolger im Rechts
						parent->setRight(ptr->getRight());
					else   //Nachfolger im Links
						parent->setRight(ptr->getLeft());
				}
				else {   //liegt Links Node des Parents
					if (ptr->getRight() != 0)//Nachfolger im Rechts
						parent->setLeft(ptr->getRight());
					else    //Nachfolger im Links
						parent->setLeft(ptr->getLeft());
				}
				delete ptr;
				ptr = 0;
			}
			else if (ptr->getRight() != 0 && ptr->getLeft() != 0) {//hat 2 Nachfolgern
				TreeNode* ptr2 = ptr->getRight(), * parent2 = 0;
				while (ptr2->getLeft() != 0) {//Minimalrecht suchen
					parent2 = ptr2;
					ptr2 = ptr2->getLeft();
				}
				if (ptr == parent->getRight()) {//Liegt recht des parents
					if (parent2 == 0) {//hat
						parent->setRight(ptr2);
						ptr2->setLeft(ptr->getLeft());
						delete ptr;
						ptr = 0;
					}
					else {
						parent2->setLeft(ptr2->getRight());
						parent->setRight(ptr2);
						ptr2->setRight(ptr->getRight());
						ptr2->setLeft(ptr->getLeft());
						delete ptr;
						ptr = 0;
					}
				}
				else {
					if (parent2 == 0) {
						parent->setLeft(ptr2);
						ptr2->setLeft(ptr->getLeft());
						delete ptr;
						ptr = 0;
					}
					else {
						parent2->setLeft(ptr2->getRight());
						parent->setLeft(ptr2);
						ptr2->setRight(ptr->getRight());
						ptr2->setLeft(ptr->getLeft());
						delete ptr;
						ptr = 0;
					}
				}
				return 1;
			}
		}
	}
	
}


bool Tree::searchNode(string Nm) {
	cout << "+Fundstellen: \n";
	if (searcht(anker, Nm))
	return 1;
	
	else {
	cout << "konnte nicht gefunden.\n";
	return 0;
	}
}
bool Tree::searcht(TreeNode* head,std::string nm) {
	if (head == 0)
		return 0;
	if (head->getName() == nm){
		head->print();
		return true;
	}
	return searcht(head->getLeft(), nm) | searcht(head->getRight(), nm);
}
void Tree::printAll() {
	cout << left << setw(4) << " ID";
	cout << left << setw(19) << "| Name";
	cout << left << setw(8) << "| Age";
	cout << left << setw(12) << "| Income";
	cout << left << setw(11) << "| PostCode";
	cout << left << setw(7) << "| OrderID\n";
	

	cout << right << setfill('-');
	cout << setw(5) << "+";
	cout << setw(19) << "+";
	cout << setw(8) << "+";
	cout << setw(12) << "+";
	cout << setw(11) << "+";
	cout << setw(7) << "-"<<endl;
	printing(anker);
}
void Tree::printing(TreeNode* ptr) {
	if (ptr == 0) {
		cout << "Leerer Baum." << endl;
		return;
	}
	cout << setfill(' ');
	cout << setw(4) << ptr->getNodeChronologicalID() << "|";
	cout << setw(18) << ptr->getName() << "|";
	cout << setw(7) << ptr->getAge() << "|";
	cout << setw(11) << ptr->getIncome() << "|";
	cout << setw(10) << ptr->getPostCode() << "|";
	cout << setw(6) << ptr->getNodeOrderID() << endl;
	if (ptr->getRight() != 0)
		printing(ptr->getRight());
	if (ptr->getLeft() != 0)
		printing(ptr->getLeft());
}
void Tree::levelOrder() {
	int maxtief = 10;
	cout << left << setw(4) << " ID";
	cout << left << setw(19) << "| Name";
	cout << left << setw(8) << "| Age";
	cout << left << setw(12) << "| Income";
	cout << left << setw(11) << "| PostCode";
	cout << left << setw(7) << "| OrderID";
	cout << left << setw(6) << "| Level\n";

	cout <<right << setfill('-');
	cout << setw(5) << "+";
	cout << setw(19) << "+";
	cout << setw(8) << "+";
	cout << setw(12) << "+";
	cout << setw(11) << "+";
	cout << setw(9) << "+";
	cout << setw(6) <<"-"<< endl;

	for (int i = 1; i <= 10; i++) {
		LOprint(anker, i, i);
	}
}
void Tree::LOprint(TreeNode* ptr, int lvl,int ind) {
	if (ptr == 0) {
		cout << "Leerer Baum." << endl;
		return;
	}
	else {
		if (ind == 1) {
			cout << setfill(' ');
			cout << setw(4) << ptr->getNodeChronologicalID() << "|";
			cout << setw(18) << ptr->getName() << "|";
			cout << setw(7) << ptr->getAge() << "|";
			cout << setw(11) << ptr->getIncome() << "|";
			cout << setw(10) << ptr->getPostCode() << "|";
			cout << setw(8) << ptr->getNodeOrderID() << "|";
			cout << setw(5) << lvl << endl;
		}
		else if (ind > 1) {
			if (ptr->getLeft() != 0)
				LOprint(ptr->getLeft(), lvl, ind - 1);
			if (ptr->getRight() != 0)
				LOprint(ptr->getRight(), lvl, ind - 1);
		}
	}
}


//
////////////////////////////////////