/*************************************************
 * ADS Praktikum 2.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;
////////////////////////////////////
// Ihr Code hier:
Tree::Tree() {
	anker = 0;
	currentNodeChronologicalID = 0;
}

Tree::~Tree() {
	/////
	//
	//
	/////
}



bool Tree::addNode(string N, int Alt, double in, int PC) {
	TreeNode* nData = new TreeNode(Alt + in + PC, currentNodeChronologicalID, N, Alt, in, PC);
	if (anker == 0) {
		anker = nData;
		anker->setRed(0);
		currentNodeChronologicalID++;
	}
	else {
		currentNodeChronologicalID++;
		TreeNode* ptr = anker;
		TreeNode* prnt = 0;
		do {
			split4Node(ptr);
			prnt = ptr;
			if (nData->getNodeOrderID() >= ptr->getNodeOrderID())
				ptr = ptr->getRight();
			else
				ptr = ptr->getLeft();
		} while (ptr != 0);
		nData->setParent(prnt);
		if (nData->getNodeOrderID() < prnt->getNodeOrderID())
			prnt->setLeft(nData);
		else
			prnt->setRight(nData);
	}
	
	TreeNode* ptr1 = nData;
	int Red = 0;
	while (ptr1 != 0) {
		if (!ptr1->getRed())
			Red = 0;
		else
			Red++;
		if (Red == 2) {//2 Rote-Knoten nacheinander.
			balance(ptr1);
		}
		ptr1 = ptr1->getParent();
	}
	return 1;
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
bool Tree::searcht(TreeNode* head, std::string nm) {
	if (head == 0)
		return 0;
	if (head->getName() == nm) {
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
	cout << left << setw(7) << "| OrderID";
	cout << left << setw(7) << "| Red\n";


	cout << right << setfill('-');
	cout << setw(5) << "+";
	cout << setw(19) << "+";
	cout << setw(8) << "+";
	cout << setw(12) << "+";
	cout << setw(11) << "+";
	cout << setw(8) << "+";
	cout << setw(7) << "-" << endl;
	preOrder(anker);
}

void Tree::preOrder(TreeNode* ptr) {
	if (ptr == 0) {
		cout << "Baum ist Leer." << endl;
		return;
	}
	cout << setfill(' ');
	cout << setw(4) << ptr->getNodeChronologicalID() << "|";
	cout << setw(18) << ptr->getName() << "|";
	cout << setw(7) << ptr->getAge() << "|";
	cout << setw(11) << ptr->getIncome() << "|";
	cout << setw(10) << ptr->getPostCode() << "|";
	cout << setw(8) << ptr->getNodeOrderID() << "|";
	cout << setw(6) << ptr->getRed() << endl;
	if (ptr->getRight() != 0)
		preOrder(ptr->getRight());
	if (ptr->getLeft() != 0)
		preOrder(ptr->getLeft());
}
void Tree::printLvlOrder() {
	cout << left << setw(4) << " ID";
	cout << left << setw(19) << "| Name";
	cout << left << setw(8) << "| Age";
	cout << left << setw(12) << "| Income";
	cout << left << setw(11) << "| PostCode";
	cout << left << setw(7) << "| OrderID";
	cout << left << setw(7) << "| Red\n";


	cout << right << setfill('-');
	cout << setw(5) << "+";
	cout << setw(19) << "+";
	cout << setw(8) << "+";
	cout << setw(12) << "+";
	cout << setw(11) << "+";
	cout << setw(8) << "+";
	cout << setw(7) << "-" << endl;
	levelOrder(anker);
}
void Tree::levelOrder(TreeNode* ptr) {
	queue<TreeNode*> q;
	if (ptr == 0) {
		cout << "Baum ist Leer." << endl;
		return;
	}
	q.push(ptr);
	TreeNode* tmp = ptr;
	while (!q.empty()) {
		int count = q.size();
		while (count > 0) {
			tmp = q.front();
			cout << setfill(' ');
			cout << setw(4) << tmp->getNodeChronologicalID() << "|";
			cout << setw(18) << tmp->getName() << "|";
			cout << setw(7) << tmp->getAge() << "|";
			cout << setw(11) << tmp->getIncome() << "|";
			cout << setw(10) << tmp->getPostCode() << "|";
			cout << setw(8) << tmp->getNodeOrderID() << "|";
			cout << setw(6) << tmp->getRed() << endl;
			if (tmp->getLeft())
				q.push(tmp->getLeft());
			if (tmp->getRight())
				q.push(tmp->getRight());
			
			q.pop();
			count--;
		}
	}
}


/////Praktiku-03

void Tree::printLevelOrder() {
	queue<TreeNode*> q;
	int niv = 0;

	if (anker == 0) {
		cout << "Baum ist Leer." << endl;
		return;
	}
	q.push(anker);
	TreeNode* Ptr = anker;
	while (!q.empty()) {
		int count = q.size();
		cout << "Niveau " << niv << ": ";
		while (count > 0) {
			Ptr = q.front();
			if (Ptr->getLeft()) {
				if (!Ptr->getLeft()->getRed()) {
					q.push(Ptr->getLeft());
					cout << "(";
				}
				else {
					if (Ptr->getLeft()->getLeft()) 
						q.push(Ptr->getLeft()->getLeft());
					
					if (Ptr->getLeft()->getRight()) 
						q.push(Ptr->getLeft()->getRight());
					
					cout << "(" << Ptr->getLeft()->getNodeOrderID() << ", ";
				}
			}
			else {
				cout << "(";
			}

			cout << Ptr->getNodeOrderID();

			if (Ptr->getRight()) {
				if (!Ptr->getRight()->getRed()) {
					q.push(Ptr->getRight());
					cout << ")";
				}
				else {
					if (Ptr->getRight()->getLeft())
						q.push(Ptr->getRight()->getLeft());

					if (Ptr->getRight()->getRight())
						q.push(Ptr->getRight()->getRight());

					cout << ", " << Ptr->getRight()->getNodeOrderID() << ")";
				}
			}else
				cout << ")";
			q.pop();
			count--;
		}
		niv++;
		cout << endl;
	}
}

void Tree::printLevelOrder(int lvl) {
	queue<TreeNode*> q;
	int niv = 0;

	if (anker == 0) {
		cout << "Baum ist Leer." << endl;
		return;
	}
	q.push(anker);
	TreeNode* Ptr = anker;
	while (!q.empty()) {
		int count = q.size();
		if (niv == lvl)
			cout << "Niveau " << niv << ": ";
		while (count > 0) {
			Ptr = q.front();
			if (Ptr->getLeft()) {
				if (!Ptr->getLeft()->getRed()) {
					q.push(Ptr->getLeft());
					if (niv == lvl)
						cout << "(";
				}
				else {
					if (Ptr->getLeft()->getLeft())
						q.push(Ptr->getLeft()->getLeft());

					if (Ptr->getLeft()->getRight())
						q.push(Ptr->getLeft()->getRight());
					if (niv == lvl)
						cout << "(" << Ptr->getLeft()->getNodeOrderID() << ", ";
				}
			}
			else {
				if (niv == lvl)
					cout << "(";
			}
			if (niv == lvl)
				cout << Ptr->getNodeOrderID();
			if (Ptr->getRight()) {
				if (!Ptr->getRight()->getRed()) {
					q.push(Ptr->getRight());
					if (niv == lvl)
						cout << ")";
				}
				else {
					if (Ptr->getRight()->getLeft())
						q.push(Ptr->getRight()->getLeft());

					if (Ptr->getRight()->getRight())
						q.push(Ptr->getRight()->getRight());
					if (niv == lvl)
						cout << ", " << Ptr->getRight()->getNodeOrderID() << ")";
				}
			}
			else
				if (niv == lvl)
					cout << ")";
			q.pop();
			count--;
		}
		niv++;
		cout << endl;
	}
}

bool Tree::split4Node(TreeNode* p) {
	

	if (p->getRed()) {                    //wenn Knoten rot ist
		return 0;
	}
	if (p->getLeft() != 0 && p->getRight() != 0) {          //rechter und linker knoten existieren

		if (p->getLeft()->getRed() && p->getRight()->getRed()) {           //beide sind rot

			if (anker != p) {
				p->setRed(1);
			}
			p->getLeft()->setRed(0);      //Knoten schwarz setzten
			p->getRight()->setRed(0);       //Knoten schwarz setzten
			return 1;

		}

	}
	return 0;
}

void Tree::balance(TreeNode* ptr) {
	//fall 2 : 4-Knoten hängt am 3-Knoten
	//fall 2b)
	if (ptr->getParent() != 0 && ptr->getRight() != 0) {
		if (ptr->getNodeOrderID() < ptr->getParent()->getNodeOrderID() && ptr->getRight()->getRed()) {
			//Links-Rechts-Knicks
			rotateTreeLeft(ptr, ptr->getRight());
			rotateTreeRight(ptr->getParent()->getParent(), ptr->getParent());
			ptr->getParent()->setRed(0);
			ptr->getParent()->getRight()->setRed(1);
			return;
		}
	}
	if (ptr->getParent() != 0 && ptr->getLeft() != 0) {
		if (ptr->getNodeOrderID() > ptr->getParent()->getNodeOrderID() && ptr->getLeft()->getRed()) {
			//Rechts-Links-Knicks
			rotateTreeRight(ptr, ptr->getLeft());
			rotateTreeLeft(ptr->getParent()->getParent(), ptr->getParent());
			ptr->getParent()->setRed(0);
			ptr->getParent()->getLeft()->setRed(1);
			return;
		}
	}
	if (ptr->getParent() != 0 && ptr->getRight() != 0) {
		if (ptr->getNodeOrderID() > ptr->getParent()->getNodeOrderID() && ptr->getRight()->getRed()) {
			//fall 2c) : Ist das das rechte äußere Kind des 3-Knoten
			rotateTreeLeft(ptr->getParent(), ptr);
			ptr->setRed(0);
			ptr->getLeft()->setRed(1);
			return;
		}
	}
	if (ptr->getParent() != 0 && ptr->getLeft() != 0) {
		if (ptr->getNodeOrderID() < ptr->getParent()->getNodeOrderID() && ptr->getLeft()->getRed()) {
			//fall 2a):Ist das linke äußere Kind des 3-Knoten
			rotateTreeRight(ptr->getParent(), ptr);
			ptr->setRed(0);
			ptr->getRight()->setRed(1);
			return;
		}
	}
	
}

int Tree::proofRBCriterion(TreeNode* p) {
	int l = 0, r = 0; //Hohe linke Knote, Hohe rechte Knote
	if (p == 0)
		return -1;
	else {
		if (p->getRight() == 0 && p->getLeft() == 0)
			return 0;
		if (p->getLeft() != 0)
			l = proofRBCriterion(p->getLeft());
		if (p->getRight() != 0)
			r = proofRBCriterion(p->getRight());
		
		if (p->getRight() != 0 && p->getLeft() != 0) {//beide Nachfolger existiert
			if (p->getRight()->getRed() == 1 && p->getLeft()->getRed() == 1) {//beide rot
				if (l == r)
					return l;
				else
					return -1;
			}
			else if (p->getRight()->getRed() == 0 && p->getLeft()->getRed() == 1) {//rechts schwarz, links rot 
				if (r + 1 == l)
					return l;
				else
					return -1;
			}
			else if (p->getRight()->getRed() == 1 && p->getLeft()->getRed() == 0) {//rechts rot, links schwarz
				if (l + 1 == r)
					return r;
				else
					return -1;
			}
			else if (p->getRight()->getRed() == 0 && p->getLeft()->getRed() == 0) {//beide schwarz
				if (r == l)
					return r;
				else
					return -1;
			}
		}
		if (p->getRight() == 0 && p->getLeft() != 0) {//nur linke Nachfolger existiert
			if (p->getLeft()->getRed())//linke Nachfolger = rot;
				return l;
			else
				return l + 1;
		}
		if (p->getRight() == 0 && p->getLeft() != 0) {//nur rechte Nachfolger existier
			if (p->getRight()->getRed())//rechte Nachfolger = rot
				return r;
			else
				return r + 1;
		}
	}
}

bool Tree::rotateTreeRight(TreeNode* p1, TreeNode* p2) {
	if (p1 == anker){
		anker = p2;
		p2->setParent(0);
	}
	else {
		TreeNode* prnt = p1->getParent();
		if (prnt->getNodeOrderID() > p2->getNodeOrderID()) {
			prnt->setLeft(p2);
			p2->setParent(prnt);
		}
		else {
			prnt->setRight(p2);
			p2->setParent(prnt);
		}
	}
	p1->setParent(p2);
	p1->setLeft(p2->getRight());
	if (p1->getLeft() != 0)
		p1->getLeft()->setParent(p1);
	p2->setRight(p1);
	return 1;
}

bool Tree::rotateTreeLeft(TreeNode* p1, TreeNode* p2) {
	if (p1 == anker) {
		anker = p2;
		p2->setParent(0);
	}
	else {
		TreeNode* prnt = p1->getParent();
		if (prnt->getNodeOrderID() > p2->getNodeOrderID()) {
			prnt->setLeft(p2);
			p2->setParent(prnt);
		}
		else {
			prnt->setRight(p2);
			p2->setParent(prnt);
		}
	}
	p1->setParent(p2);
	p1->setRight(p2->getLeft());
	if (p1->getRight() != 0)
		p1->getRight()->setParent(p1);
	p2->setLeft(p1);
	return 1;
}


//
////////////////////////////////////